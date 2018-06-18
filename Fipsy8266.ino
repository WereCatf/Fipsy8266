#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include "progmemStuff.h"

#include<libFipsy8266.h>

//////////// CHANGE THESE TO YOUR LIKING
char espName[] = "FipsyProgrammer";
//Which GPIO-pin to use as the CS-pin
#define _FIPSY_CS 15
//////////// CHANGE THESE TO YOUR LIKING

fipsy8266Class fipsy(_FIPSY_CS);
ESP8266WebServer webServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);
File uploadFile;
bool spiffsMounted = false;
uint32_t devID = 0xffffffff;
char *tempText = NULL;

//////////// WEBSERVER
void webAbout() {
  webServer.send(200, "text/html", webAboutPage);
}

void webSvg() {
  if (strcmp_P(webServer.uri().c_str(), (PGM_P)F("/logo.svg")) == 0) webServer.send(200, "image/svg+xml", webSvgLogo);
  else if (strcmp_P(webServer.uri().c_str(), (PGM_P)F("/micro.svg")) == 0) webServer.send(200, "image/svg+xml", webSvgMicro);
}

void webRoot() {
  webServer.send(200, "text/html", webRootPage);
}

void webUpload() {
  HTTPUpload& upload = webServer.upload();

  if (!spiffsMounted) {
    webSocket.broadcastTXT("statusMessage=<div class\t\"erreur\">SPIFFS not mounted! (try formatting?)</div>");
    webServer.send(500, "text/html", "");
    return;
  }
  if (!upload.filename.endsWith(".jed") && !upload.filename.endsWith(".JED")) {
    webSocket.broadcastTXT("statusMessage=<div class\t\"erreur\">uploaded file not JEDEC</div>");
    webServer.send(500, "text/html", "");
    return;
  }
  if (upload.totalSize > (1024 * 1024)) {
    webSocket.broadcastTXT("statusMessage=<div class\t\"erreur\">uploaded file too large</div>");
    webServer.send(500, "text/html", "");
    return;
  }
  if (upload.filename.length() > 30) {
    webSocket.broadcastTXT("statusMessage=<div class\t\"erreur\">filename too long (30 chars max!)</div>");
    webServer.send(500, "text/html", "");
    return;
  }
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    uploadFile = SPIFFS.open(filename, "w");
    if (!uploadFile) {
      webSocket.broadcastTXT("statusMessage=<div class\t\"erreur\">error creating the file (SPIFFS full?)</div>");
      webServer.send(500, "text/html", "");
      return;
    }
    webSocket.broadcastTXT("statusMessage=uploading file...");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (uploadFile) {
      uploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (uploadFile) {
      uploadFile.close();
      String fileList = "";
      Dir dir;
      dir = SPIFFS.openDir("/");
      while (dir.next())
        if (dir.fileName().endsWith(".JED") || dir.fileName().endsWith(".jed"))
          if (strcmp(dir.fileName().c_str(), upload.filename.c_str()) == 0)
            fileList += String("<option selected\ttrue value\t\"") + dir.fileName() + String("\">") + dir.fileName() + String("</option>");
          else
            fileList += String("<option value\t\"") + dir.fileName() + String("\">") + dir.fileName() + String("</option>");

      if (fileList.length() < 1)
        snprintf(tempText, 3183, "statusMessage=upload successful\nfileList=empty");
      else
        snprintf(tempText, 3183, "statusMessage=upload successful\nfileList=%s", fileList.c_str());
      webSocket.broadcastTXT(tempText);
    }
    Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
  }
}
//////////// WEBSERVER
//////////// WEBSOCKET
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  String fileList = "";
  Dir dir;
  int formatStatus;

  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      dir = SPIFFS.openDir("/");
      while (dir.next())
        if (dir.fileName().endsWith(".JED") || dir.fileName().endsWith(".jed"))
          fileList += String("<option value\t\"") + dir.fileName() + String("\">") + dir.fileName() + String("</option>");

      if (fileList.length() < 1)
        snprintf(tempText, 3183, "hostname=%s", espName);
      else
        snprintf(tempText, 3183, "hostname=%s\nfileList=%s", espName, fileList.c_str());
      webSocket.sendTXT(num, tempText);
      break;
    case WStype_TEXT:
      if (strncmp_P((const char *)payload, (PGM_P)F("hostname"), length) == 0) {
        snprintf(tempText, 99, "hostname=%s", espName);
        webSocket.sendTXT(num, tempText);
      }

      else if (strncmp_P((const char *)payload, (PGM_P)F("readDID"), length) == 0) {
        devID = fipsy.readID();
        snprintf(tempText, 99, "devID=0x%08x\nstatusMessage=read DID %s", devID, devID != 0xffffffff ? "OK" : "<div class\t\"erreur\">failed</div>");
        webSocket.sendTXT(num, tempText);
      }

      else if (strncmp_P((const char *)payload, (PGM_P)F("erase"), length) == 0) {
        webSocket.sendTXT(num, "statusMessage=check for presence...");
        devID = fipsy.readID();
        if (devID != 0xffffffff) {
          webSocket.sendTXT(num, "statusMessage=attempting erase...");
          webSocket.sendTXT(num, "statusMessage=erase " + fipsy.erase() ? "successful" : "<div class\t\"erreur\">failed (timeout)</div>");
        } else webSocket.sendTXT(num, "devID=0xffffffff\nstatusMessage=<div class\t\"erreur\">device not present? (no DID)</div>");
      }

      //'program' is a special-case, since it accepts as an argument the filename which to use
      else if (strncmp_P((const char *)payload, (PGM_P)F("program="), 8) == 0) {
        webSocket.sendTXT(num, "statusMessage=<div class\t\"erreur\">programming not implemented yet</div>");
      }

      else if (strncmp_P((const char *)payload, (PGM_P)F("delete="), 7) == 0) {
        if (SPIFFS.exists(strstr((const char *)payload, "=") + 1)) SPIFFS.remove(strstr((const char *)payload, "=") + 1);
        dir = SPIFFS.openDir("/");
        while (dir.next())
          if (dir.fileName().endsWith(".JED") || dir.fileName().endsWith(".jed"))
            fileList += String("<option value\t\"") + dir.fileName() + String("\">") + dir.fileName() + String("</option>");

        if (fileList.length() < 1)
          snprintf(tempText, 3183, "statusMessage=file deleted\nfileList=empty");
        else
          snprintf(tempText, 3183, "statusMessage=file deleted\nfileList=%s", fileList.c_str());
        webSocket.sendTXT(num, tempText);
      }

      else if (strncmp_P((const char *)payload, (PGM_P)F("formatSPIFFS"), length) == 0) {
        webSocket.sendTXT(num, "statusMessage=Attempting to format SPIFFS, please wait...");
        formatStatus = SPIFFS.format();
        dir = SPIFFS.openDir("/");
        while (dir.next())
          if (dir.fileName().endsWith(".JED") || dir.fileName().endsWith(".jed"))
            fileList += String("<option value\t\"") + dir.fileName() + String("\">") + dir.fileName() + String("</option>");

        if (fileList.length() < 1)
          snprintf(tempText, 3183, "statusMessage=formatting SPIFFS %s\nfileList=empty", formatStatus ? "successful" : "<div class\t\"erreur\">failed</div>");
        else
          snprintf(tempText, 3183, "statusMessage=formatting SPIFFS %s\nfileList=%s", formatStatus ? "successful" : "<div class\t\"erreur\">failed</div>", fileList.c_str());
        webSocket.broadcastTXT(tempText);
        if (!spiffsMounted) {
          if (SPIFFS.begin()) spiffsMounted = true;
        }
      }
      break;
    case WStype_BIN:
      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
  }
}
//////////// WEBSOCKET

void setup() {
  tempText = (char *)malloc(3184);
  Serial.begin(115200);
  delay(2000);
  WiFiManager wifiManager;
  WiFi.hostname(espName);
  wifiManager.autoConnect(espName);
  Serial.print(espName);
  Serial.println(F(" begin..."));
  fipsy.begin();

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
      SPIFFS.end();
    }
    Serial.print(F("Start updating "));
    Serial.println(type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println(F("\nEnd"));
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println(F("Auth Failed"));
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println(F("Begin Failed"));
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println(F("Connect Failed"));
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println(F("Receive Failed"));
    } else if (error == OTA_END_ERROR) {
      Serial.println(F("End Failed"));
    }
  });
  ArduinoOTA.setHostname(espName);
  ArduinoOTA.begin();
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);

  if (!SPIFFS.begin()) {
    Serial.print(F("Failed to mount SPIFFS, going to attempt to format..."));
    if (!SPIFFS.format())
      Serial.println(F("failed!"));
    else {
      Serial.println(F("ok."));
      if (SPIFFS.begin()) spiffsMounted = true;
    }
  } else spiffsMounted = true;

  webServer.on("/", webRoot);
  webServer.on("/index.htm", webRoot);
  webServer.on("/index.html", webRoot);
  webServer.on("/index.php", webRoot);
  webServer.on("/about", webAbout);
  webServer.on("/logo.svg", webSvg);
  webServer.on("/micro.svg", webSvg);
  webServer.on("/upload", HTTP_POST, []() {
    webServer.send(200, "text/plain", "");
  }, webUpload);
  webServer.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  ArduinoOTA.handle();
  webServer.handleClient();
  webSocket.loop();
  delay(1);
}
