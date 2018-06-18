#ifndef _PROGMEMSTUFF_H_
#define _PROGMEMSTUFF_H_

//HTML + CSS + JS
const char webRootPage[] PROGMEM = "<html>\n<head>\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0\">\n<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\n<title>Fipsy8266Programmer</title>\n<link href='https://fonts.googleapis.com/css?family=Abhaya Libre' rel='stylesheet'>\n<style>\nbody {\n    font-family: 'Abhaya Libre',\"Times New Roman\", Times, serif;\n\tfont-size: 1.2em;\n\tbackground-color: #2196F3;\n}\n\n.bodyBox {\n  border: 1px solid black;\n  margin: auto;\n  width: 38em;\n  padding-left: 0.5em;\n  padding-right: 0.5em;\n  padding-bottom: 0.5em;\n  border-radius: 1.4em;\n  background-color: white;\n}\n\n.switch {\n  position: relative;\n  display: inline-block;\n  width: 3.3em;\n  height: 1.5em;\n}\n\n.switch input {display:none;}\n\n.slider {\n  position: absolute;\n  cursor: pointer;\n  top: 0;\n  left: 0;\n  right: 0;\n  bottom: 0;\n  background-color: #ccc;\n  -webkit-transition: .4s;\n  transition: .4s;\n}\n\n.slider:before {\n  position: absolute;\n  content: \"\";\n  height: 1.3em;\n  width: 1.3em;\n  left: 0.3em;\n  bottom: 0.1em;\n  background-color: white;\n  -webkit-transition: .4s;\n  transition: .4s;\n}\n\ninput:checked + .slider {\n  background-color: #2196F3;\n}\n\ninput:focus + .slider {\n  box-shadow: 0 0 1px #2196F3;\n}\n\ninput:checked + .slider:before {\n  -webkit-transform: translateX(1.4em);\n  -ms-transform: translateX(1.4em);\n  transform: translateX(1.4em);\n}\n\n/* Rounded sliders */\n.slider.round {\n  border-radius: 1.4em;\n}\n\n.slider.round:before {\n  border-radius: 50%;\n}\n\n.settings {\n  display: table;\n  width: 100%;\n}\n\n.settings .cell,\n.settings .switch .cell {\n  display: table-cell;\n  vertical-align: middle;\n  padding-right: 0.5em;\n  padding-top: 0.12em;\n  padding-bottom: 0.12em;\n  text-align: center;\n}\n\n.icons .cell,\n.icons .switch .cell {\n  display: table-cell;\n  vertical-align: middle;\n  padding-right: 0.5em;\n}\n\n.row {\n  display: table-row;\n}\n\n.icon {\n  display: table-cell;\n  width: 1.8em;\n  height: 1.8em;\n  padding-right: 0.5em;\n}\n\nh1 {\n  margin: 0px;\n  padding: 0px;\n  text-align: center;\n  font-weight: bold;\n}\n\nh6 {\n  margin: 0px;\n  padding: 0px;\n  text-align: center;\n}\n\n#programmerNameP {\n  margin: 0px;\n  padding: 0px;\n}\n\n#statusMessageP {\n  margin: 0px;\n  padding: 0px;\n}\n\na {\n\tcolor: black;\n\ttext-decoration: none;\n}\n\na:visited {\n\tcolor: black;\n}\n\na:hover {\n\tcolor: red;\n}\n\n#aboutP {\n\ttext-align: right;\n\tfont-size: 0.5em;\n}\n\n#spiffsP {\n\tfont-size: 0.5em;\n\tdisplay: inline;\n}\n\n#spiffsP:hover {\n\tcursor: pointer;\n\tcolor: red;\n}\n\n.erreur {\n\tcolor: red;\n\tdisplay: inline;\n}\n\n#leftA {\n\ttext-align: left;\n}\n\n#programmerLogo {\n\twidth: 0.8em;\n\theight: 0.8em;\n\tposition: relative;\n\ttop: 0.1em;\n\tright: 0.2em;\n}\n\n</style>\n<script type=\"text/javascript\">\nvar programmerHostname=\"Name\", statusMessage = \"idle\", devID = \"\";\nvar ws;\n  \nfunction parseMessageLine(item, index){\n\titems = item.split(\"=\", 2);\n\tif(items.length < 2) return;\n\tswitch(items[0]) {\n\t\tcase \"hostname\":\n\t\t\tif(items[1].length < 1) break;\n\t\t\tprogrammerHostname = items[1];\n\t\t\tdocument.title = items[1];\n\t\t\tbreak;\n\t\tcase \"statusMessage\":\n\t\t\tif(items[1].length < 1) break;\n\t\t\tstatusMessage = items[1].replace(\"\\t\", \"=\");\n\t\t\tbreak;\n\t\tcase \"devID\":\n\t\t\tif(items[1].length < 1) break;\n\t\t\tdevID = items[1];\n\t\t\tif(devID != \"0xffffffff\"){\n\t\t\t\tdocument.getElementById(\"eraseButton\").disabled = false;\n\t\t\t\tdocument.getElementById(\"programButton\").disabled = document.getElementById(\"programFile\").disabled;\n\t\t\t}\n\t\t\telse{\n\t\t\t\tdocument.getElementById(\"eraseButton\").disabled = true;\n\t\t\t\tdocument.getElementById(\"programButton\").disabled = true;\n\t\t\t}\n\t\t\tbreak;\n\t\tcase \"fileList\":\n\t\t\tif(items[1].length < 1) break;\n\t\t\tif(items[1] == \"empty\"){\n\t\t\t\tdocument.getElementById(\"programFile\").disabled = true;\n\t\t\t\tdocument.getElementById(\"programFile\").innerHTML = \"<option disabled=true selected=true>[No programmable files, upload some!]</option>\";\n\t\t\t\tdocument.getElementById(\"deleteButton\").disabled = true;\n\t\t\t\tdocument.getElementById(\"programButton\").disabled = true;\n\t\t\t} else {\n\t\t\t\tdocument.getElementById(\"programFile\").disabled = false;\n\t\t\t\tdocument.getElementById(\"programFile\").innerHTML = items[1].replace(\"\\t\", \"=\");\n\t\t\t\tdocument.getElementById(\"deleteButton\").disabled = false;\n\t\t\t\tif(devID != \"\" && devID != \"0xffffffff\") document.getElementById(\"programButton\").disabled = false;\n\t\t\t}\n\t\t\tbreak;\n\t}\n}\n\nfunction updateStats(){\n\tif (typeof ws == 'undefined'){\n\t\tbeginWebsocket();\n\t\treturn;\n\t}\n\telse if (ws.readyState == 2) return;\n\telse if (ws.readyState == 3){\n\t\tws = undefined;\n\t\tbeginWebsocket();\n\t\treturn\n\t}\n}\n\nfunction beginWebsocket() {\n\tif (\"WebSocket\" in window) {\n\t\t//ws = new WebSocket(\"ws://192.168.178.20:81/\");\n\t\tws = new WebSocket(\"ws://\" + window.location.hostname + \":81/\");\n\n\t\tws.onopen = function()\n\t\t{\n\t\t//TODO?\n\t\t};\n\n\t\tws.onmessage = function (evt) \n\t\t{ \n\t\t\tvar receivedMessage = evt.data;\n\t\t\tvar messageArray = receivedMessage.split(\"\\n\");\n\t\t\tmessageArray.forEach(parseMessageLine);\n\t\t\tdocument.getElementById(\"programmerNameP\").innerHTML = \"<h1><img id=\\\"programmerLogo\\\" src=\\\"/micro.svg\\\">\" + programmerHostname + \"</h1>\";\n\t\t\tdocument.getElementById(\"statusMessageP\").innerHTML = \"<h6>Status: \" + statusMessage + \"</h6><br><h6>Device ID: \" + devID + \"</h6>\";\n\t\t};\n\n\t\tws.onclose = function()\n\t\t{ \n\t\t\t// websocket is closed.\n\t\t\t// alert(\"Connection is closed...\"); \n\t\t};\n\n\t\twindow.onbeforeunload = function(event) {\n\t\t\tws.close();\n\t\t};\n\t}\n\telse {\n\t\t// The browser doesn't support WebSocket\n\t\talert(\"WebSockets NOT supported by your Browser!\");\n\t}\n}\n\nfunction beginStuff() {\n\tbeginWebsocket();\n\tsetInterval(updateStats, 5000);\n}\n\nfunction boxAction(checked, yesString, noString){\n\tif(checked) ws.send(yesString);\n\telse ws.send(noString);\n}\n\nfunction uploadFile() {\n\tfd = new FormData();\n\tfd.append(\"jedecFile\", document.getElementById(\"jedecFile\").files[0]);\n\tvar xhr = new XMLHttpRequest();\n\txhr.onreadystatechange = function() {\n\tif (xhr.readyState === 4 && xhr.status === 200) {\n\t\t// upload is complete, output result data\n\t\t//console.dir(JSON.parse(xhr.responseText));\n\t\t}\n\t};\n\txhr.open(\"POST\", \"/upload\");\n\txhr.send(fd);\n}\n\n</script>\n</head>\n<body onload=\"beginStuff()\">\n<div class=\"bodyBox\">\n<p id=\"programmerNameP\"></p>\n<p id=\"statusMessageP\"></p>\n<p id=\"sensorStatsP\"></p>\n\n<div class=\"settings\">\n\n<div class=\"row\">\n<div class=\"cell\">\n<input type=\"button\" id=\"idButton\" value=\"Read deviceID\" onClick=\"ws.send('readDID');\">\n<input type=\"button\" id=\"eraseButton\" value=\"Erase device\" disabled=true onClick=\"ws.send('erase');\">\n</div>\n</div>\n\n<div class=\"row\">\n<div class=\"cell\">\n\t<select id=\"programFile\" disabled=true>\n\t<option disabled=true selected=true>[No programmable files, upload some!]</option>\n\t</select>\n\t<input type=\"button\" value=\"Delete file\" disabled=true id=\"deleteButton\" onClick='ws.send(\"delete=\" + document.getElementById(\"programFile\").value);'>\n\t<input type=\"button\" id=\"programButton\" value=\"Program device\" disabled=true onClick='ws.send(\"program=\" + document.getElementById(\"programFile\").value);'>\n</div>\n</div>\n\n<div class=\"row\">\n<div class=\"cell\">\n\t<input type=\"file\" id=\"jedecFile\" name=\"jedecFile\" accept=\".jed\">\n\t<input type=\"submit\" value=\"Upload JEDEC-file\" onClick=\"uploadFile();\">\n</div>\n</div>\n\n</div>\n\n<div class=\"settings\">\n<div class=\"row\">\n<div class=\"cell\" id=\"leftA\">\n<p id=\"spiffsP\" onClick=\"ws.send('formatSPIFFS');\">Format SPIFFS</p>\n</div>\n<div class=\"cell\" id=\"aboutP\">\n<a href=\"/about\">About</a>\n</div>\n</div>\n</div>\n\n</div>\n</div>\n</body>\n</html>";
const char webAboutPage[] PROGMEM = "<html>\n<head>\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0\">\n<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\n<title>Fipsy8266Programmer</title>\n<link href='https://fonts.googleapis.com/css?family=Abhaya Libre' rel='stylesheet'>\n<style>\nbody {\n    font-family: 'Abhaya Libre',\"Times New Roman\", Times, serif;\n\tfont-size: 1.2em;\n\tbackground-color: #2196F3;\n}\n\n.bodyBox {\n  border: 1px solid black;\n  margin: auto;\n  width: 38em;\n  padding-left: 0.5em;\n  padding-right: 0.5em;\n  padding-bottom: 0.5em;\n  border-radius: 1.4em;\n  background-color: white;\n}\n\n.switch {\n  position: relative;\n  display: inline-block;\n  width: 3.3em;\n  height: 1.5em;\n}\n\n.switch input {display:none;}\n\n.slider {\n  position: absolute;\n  cursor: pointer;\n  top: 0;\n  left: 0;\n  right: 0;\n  bottom: 0;\n  background-color: #ccc;\n  -webkit-transition: .4s;\n  transition: .4s;\n}\n\n.slider:before {\n  position: absolute;\n  content: \"\";\n  height: 1.3em;\n  width: 1.3em;\n  left: 0.3em;\n  bottom: 0.1em;\n  background-color: white;\n  -webkit-transition: .4s;\n  transition: .4s;\n}\n\ninput:checked + .slider {\n  background-color: #2196F3;\n}\n\ninput:focus + .slider {\n  box-shadow: 0 0 1px #2196F3;\n}\n\ninput:checked + .slider:before {\n  -webkit-transform: translateX(1.4em);\n  -ms-transform: translateX(1.4em);\n  transform: translateX(1.4em);\n}\n\n/* Rounded sliders */\n.slider.round {\n  border-radius: 1.4em;\n}\n\n.slider.round:before {\n  border-radius: 50%;\n}\n\n.settings {\n  display: table;\n  width: 100%;\n}\n\n.settings .cell,\n.settings .switch .cell {\n  display: table-cell;\n  vertical-align: middle;\n  padding-right: 0.5em;\n  padding-top: 0.12em;\n  padding-bottom: 0.12em;\n  text-align: center;\n}\n\n.icons .cell,\n.icons .switch .cell {\n  display: table-cell;\n  vertical-align: middle;\n  padding-right: 0.5em;\n}\n\n.row {\n  display: table-row;\n}\n\n.icon {\n  display: table-cell;\n  width: 1.8em;\n  height: 1.8em;\n  padding-right: 0.5em;\n}\n\nh1 {\n  margin: 0px;\n  padding: 0px;\n  text-align: center;\n  font-weight: bold;\n}\n\nh6 {\n  margin: 0px;\n  padding: 0px;\n  text-align: center;\n}\n\n#programmerNameP {\n  margin: 0px;\n  padding: 0px;\n}\n\n#statusMessageP {\n  margin: 0px;\n  padding: 0px;\n}\n\na {\n\tcolor: black;\n}\na:visited {\n\tcolor: black;\n}\n\n#justify {\n\ttext-align: justify;\n\tpadding-left: 0.8em;\n}\n\n#logoP {\n\ttext-align: right;\n\tfont-size: 0.6em;\n}\n#logoSvg {\n\twidth: 6em;\n\theight: 6em;\n}\n\n#programmerLogo {\n\twidth: 0.8em;\n\theight: 0.8em;\n\tposition: relative;\n\ttop: 0.1em;\n\tright: 0.2em;\n}\n\n</style>\n<script type=\"text/javascript\">\nvar programmerHostname=\"Name\";\nvar ws;\n  \nfunction parseMessageLine(item, index){\n\titems = item.split(\"=\", 2);\n\tif(items.length < 2) return;\n\tswitch(items[0]) {\n\t\tcase \"hostname\":\n\t\t\tif(items[1].length < 1) break;\n\t\t\tprogrammerHostname = items[1];\n\t\t\tdocument.title = items[1];\n\t\t\tbreak;\n\t}\n}\n\nfunction updateStats(){\n\tif (typeof ws == 'undefined'){\n\t\tbeginWebsocket();\n\t\treturn;\n\t}\n\telse if (ws.readyState == 2) return;\n\telse if (ws.readyState == 3){\n\t\tws = undefined;\n\t\tbeginWebsocket();\n\t\treturn\n\t}\n}\n\nfunction beginWebsocket() {\n\tif (\"WebSocket\" in window) {\n\t\tws = new WebSocket(\"ws://\" + window.location.hostname + \":81/\");\n\n\t\tws.onopen = function()\n\t\t{\n\t\t//TODO?\n\t\t};\n\n\t\tws.onmessage = function (evt) \n\t\t{ \n\t\t\tvar receivedMessage = evt.data;\n\t\t\tvar messageArray = receivedMessage.split(\"\\n\");\n\t\t\tmessageArray.forEach(parseMessageLine);\n\t\t\tdocument.getElementById(\"programmerNameP\").innerHTML = \"<h1><img id=\\\"programmerLogo\\\" src=\\\"/micro.svg\\\">\" + programmerHostname + \"</h1>\";\n\t\t};\n\n\t\tws.onclose = function()\n\t\t{ \n\t\t\t// websocket is closed.\n\t\t\t// alert(\"Connection is closed...\"); \n\t\t};\n\n\t\twindow.onbeforeunload = function(event) {\n\t\t\tws.close();\n\t\t};\n\t}\n\telse {\n\t\t// The browser doesn't support WebSocket\n\t\talert(\"WebSockets NOT supported by your Browser!\");\n\t}\n}\n\nfunction beginStuff() {\n\tbeginWebsocket();\n\tsetInterval(updateStats, 5000);\n}\n\n</script>\n</head>\n<body onload=\"beginStuff()\">\n<div class=\"bodyBox\">\n<p id=\"programmerNameP\"></p>\n\n<div class=\"settings\">\n\n<div class=\"row\">\n<div class=\"cell\">\n<p>This is just a simplistic frontend to allow one to easily program the <a href=\"https://www.mocomakers.com/fipsy-fpga\">Fipsy FPGA-board.</a></p>\n</div>\n</div>\n</div>\n\n<div class=\"settings\">\n<div class=\"row\">\n<div class=\"cell\">\n<p id=\"justify\">The project was hastily thrown together by WereCatf and uses <a href=https://github.com/tzapu/WiFiManager\">the great WiFiManager by tzapu</a>,\n <a href=\"https://github.com/Links2004/arduinoWebSockets\">arduinoWebSockets by Links2004</a> and\n <a href=\"https://github.com/esp8266/Arduino\">the Arduino-core for the ESP8266 by Ivan Grokhotkov and others.</a>\n The logo was by <a href=\"https://www.flaticon.com/authors/nhor-phai\" title=\"Nhor Phai\">Nhor Phai</a> from <a href=\"https://www.flaticon.com/\"\n title=\"Flaticon\">www.flaticon.com</a> and is licensed by <a href=\"http://creativecommons.org/licenses/by/3.0/\" title=\"Creative Commons BY 3.0\" target=\"_blank\">CC 3.0 BY</a></p>\n <p>The latest code for this project can be found on <a href=\"insertgithub\">insertgithub</a></p>\n</div>\n<div class=\"cell\">\n<p id=\"logoP\"><img id=\"logoSvg\" src=\"/logo.svg\"><br>Copyright (C) 2018 WereCatf</p>\n</div>\n</div>\n</div>\n\n<div class=\"settings\">\n<div class=\"row\">\n<div class=\"cell\">\n<p><a href=\"/\">&#8604; Back to programmer</a></p>\n</div>\n</div>\n\n</div>\n</div>\n\n</div>\n</body>\n</html>";

//SVG
const char webSvgLogo[] PROGMEM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg width=\"125.2mm\" height=\"125.18mm\" version=\"1.1\" viewBox=\"0 0 443.6093 443.53615\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:cc=\"http://creativecommons.org/ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n<metadata>\n<rdf:RDF>\n<cc:Work rdf:about=\"\">\n<dc:format>image/svg+xml</dc:format>\n<dc:type rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\"/>\n<dc:title/>\n</cc:Work>\n</rdf:RDF>\n</metadata>\n<g transform=\"translate(-161.05 -264.84)\">\n<g>\n<desc>Copyright (C) 2016 Nita Vesa (WereCatf)</desc>\n<circle cx=\"383.07\" cy=\"485.72\" r=\"217.36\" fill=\"#fff\"/>\n<path d=\"m368.28 706.82c-71.466-5.0747-134.88-43.078-172.74-103.52-5.1726-8.2577-12.971-23.535-16.751-32.816-16.167-39.694-20.561-82.052-12.855-123.92 9.9945-54.296 40.22-103.11 84.444-136.38 37.635-28.311 85.363-44.253 132.49-44.253s94.851 15.942 132.49 44.253c36.135 27.183 63.036 64.754 77.125 107.72 11.562 35.257 14.05 72.264 7.3191 108.83-9.9945 54.296-40.22 103.11-84.444 136.38-41.733 31.394-95.492 47.371-147.07 43.709zm32.005-8.9943c35.693-2.7763 70.453-15.054 101.38-35.81 10.697-7.1782 19.946-14.923 31.651-26.505 8.5073-8.4177 9.2321-9.2317 17.492-19.645 18.459-23.273 33.026-54.231 39.223-83.357 3.5724-16.79 4.2496-24.059 4.2496-45.61 0-19.047-0.23284-22.577-2.338-35.447-5.3876-32.938-19.596-65.72-40.284-92.944-2.2368-2.9435-4.3552-5.6402-4.7075-5.9928-0.35235-0.35253-1.4921-1.7101-2.5328-3.0168-2.2185-2.7857-21.986-22.498-25.744-25.672-4.2586-3.5969-14.536-11.103-20.428-14.92-20.657-13.382-43.79-23.215-67.877-28.852-15.557-3.6409-24.171-4.6169-43.492-4.9272-22.096-0.35491-33.635 0.78362-52.542 5.1845-19.472 4.5323-40.65 13.004-58.073 23.23-17.139 10.059-27.6 18.237-42.939 33.57-18.129 18.12-28.552 32.389-39.45 54.006-9.4787 18.801-14.251 32.324-18.632 52.793-3.0405 14.207-4.0614 24.95-4.0614 42.737 0 21.097 1.7796 35.426 6.7125 54.05 6.6562 25.131 18.685 50.364 33.675 70.642 6.2654 8.4759 19.949 24.054 24.92 28.37 0.66079 0.57377 2.0183 1.8059 3.0168 2.7381 20.287 18.941 43.921 33.407 70.731 43.294 15.45 5.6974 33.03 9.8408 50.02 11.789 6.8772 0.78864 31.351 0.96811 40.024 0.2935zm-25.72-13.38c-6.2942-0.49236-17.614-1.8441-22.942-2.7396-55.31-9.2957-103.06-40.51-134.26-87.763-13.886-21.031-23.339-44.193-28.503-69.837-5.9984-29.786-4.4658-63.151 4.2442-92.394 12.959-43.51 39.472-80.156 77.559-107.2 18.46-13.108 39.072-22.742 61.182-28.594 19.055-5.0435 32.637-6.8518 51.521-6.8596 53.127-0.022 104.11 21.936 141.57 60.975 24.581 25.618 41.135 55.168 49.492 88.349 4.3825 17.399 6.0372 30.63 6.0372 48.268 0 17.654-1.6609 30.92-6.0428 48.268-10.852 42.964-36.02 80.83-72.393 108.92-27.992 21.614-61.5 34.953-99.05 39.428-8.0121 0.95492-23.234 1.5901-28.408 1.1854zm-63.101-62.421c2.8455-1.4215 2.6597-3.0496-0.98066-8.5935-1.6729-2.5477-3.0417-4.7688-3.0417-4.9356 0-0.31222 5.7931 0.0925 9.2201 0.64413 1.2874 0.20723 3.1281-0.0413 5.5307-0.74676 6.1889-1.8172 13.594-2.7133 23.499-2.8438 6.7238-0.0886 9.6397-0.31064 10.412-0.79281 1.0083-0.6297 2.2155-2.5971 2.8314-4.6147 0.20997-0.68775 0.59183-0.81808 1.6661-0.56868 2.1966 0.50997 3.4745 1.5142 5.2083 4.0929 2.2836 3.3964 3.3502 4.1329 5.9899 4.1362 1.7807 2e-3 3.0373-0.46324 5.9007-2.1856 2.7234-1.6382 4.3756-2.2719 6.5711-2.5203 3.7714-0.42669 5.126-1.3581 5.126-3.5248 0-1.9836-1.7992-4.8328-3.5981-5.6981-0.71391-0.3434-3.0757-0.96447-5.2484-1.3802-3.0531-0.58416-4.2572-1.0704-5.3012-2.141-0.74297-0.76185-5.6747-9.1821-10.959-18.712-9.0635-16.343-12.099-22.922-12.099-26.219 0-1.1332 3.2648-6.1441 5.9124-9.0748 2.7491-3.0429 6.1164-5.2627 11.23-7.4034 2.6008-1.0886 6.8114-2.8992 9.3569-4.0234 5.7367-2.5336 9.926-3.2549 16.489-2.839 8.2525 0.52305 15.284-0.34792 21.417-2.6529 12.178-4.5766 15.505-7.0872 27.719-20.918 2.1284-2.4101 2.9027-2.0735 2.9027 1.2618 0 2.9105 1.2457 9.3281 2.3429 12.07 0.4175 1.0435 1.249 2.2157 1.8478 2.605 1.5124 0.98335 5.8285 1.9493 8.7219 1.9519 2.241 2e-3 2.58-0.17126 4.5212-2.3108 1.1542-1.2722 2.4504-3.3849 2.8804-4.695 1.1345-3.4564 1.8623-10.988 1.7754-18.375-0.0416-3.5419 0.0384-6.554 0.17783-6.6934 0.13946-0.13946 0.57808 0.72218 0.97473 1.9147 0.448 1.3469 1.2235 2.4515 2.0473 2.916 1.188 0.66979 1.6551 0.65433 4.4848-0.14845 6.0636-1.7202 5.9427-1.7557 3.3106 0.97367-2.9563 3.0656-4.4001 6.19-4.4145 9.5529-0.0275 6.4276 4.4791 10.712 10.644 10.12 3.1115-0.29898 4.9638-1.6445 5.9374-4.313 0.96943-2.657 6.6377-9.815 8.8597-11.188 1.9258-1.1902 2.4739-2.0387 3.4925-5.4069 0.39068-1.2918 1.6141-3.7664 2.7187-5.499l2.0084-3.1502 11.949 0.33536c13.045 0.36611 16.043 0.13995 17.62-1.3292 1.2215-1.138 2.0087-5.9765 1.3011-7.9973-0.43865-1.2527-0.63575-1.3099-5.356-1.5544-4.6697-0.24181-4.9554-0.32247-6.0632-1.7118-1.0546-1.3226-1.3678-1.4305-3.3715-1.1618-1.6954 0.22741-2.5256 0.68381-3.571 1.9632l-1.3621 1.6669-23.037-0.0985c-22.756-0.0973-37.993-0.61158-38.687-1.3058-0.424-0.42399 0.30717-3.5354 1.7539-7.4634 0.87268-2.3694 1.1725-5.2136 1.8284-17.344 0.68173-12.608 0.9201-14.79 1.8185-16.646 2.2034-4.5517 18.954-18.232 22.323-18.232 0.33632 0 1.2032-0.46541 1.9263-1.0342s2.6203-1.2438 4.2158-1.5c15.206-2.4412 15.873-2.7196 16.13-6.7263 0.15125-2.3648 0.074-2.5181-2.5248-5.0112-1.4745-1.4145-5.6396-4.3177-9.2557-6.4515-7.2888-4.301-8.4432-5.4268-16.645-16.232-2.5188-3.3184-5.3304-6.7123-6.2479-7.5419-0.91753-0.82961-1.2687-1.0302-0.78046-0.44579 0.87479 1.047 0.8509 1.0785-1.6304 2.1459-8.0051 3.4437-31.105 5.7977-45.405 4.627-9.7655-0.79958-14.002-1.67-23.88-4.9066-9.7347-3.1895-10.357-3.1851-11.908 0.0846-1.0264 2.1631-1.7562 6.7005-1.8199 11.316l-0.0451 3.2682-0.76557-2.4952c-0.93051-3.0328-1.568-3.9843-3.7466-5.5915-1.5486-1.1426-1.7085-1.1699-2.0335-0.34759-0.19401 0.49085-0.36865 2.0803-0.38809 3.5321-0.0352 2.629-0.35737 3.1221-1.3749 2.1046-0.59445-0.59445-2.18 0.64605-2.18 1.7056 0 0.68552-3.8434 2.0162-4.5544 1.5768-0.26042-0.16097-0.47352-0.5945-0.47352-0.9634 0-1.0615-0.77553-1.1176-9.3017-0.67272-5.7077 0.29781-11.842 1.0799-21.117 2.6921-14.318 2.4889-16.114 2.9257-16.535 4.0223-0.21146 0.55105-0.7707 0.65988-2.209 0.42989-3.939-0.62988-10.006 2.151-18.157 8.322-2.7874 2.1105-5.6059 3.8-7.0594 4.2316-3.7737 1.1207-5.3347 2.1141-7.3849 4.6998-2.6108 3.2928-3.1288 3.653-5.2523 3.653-4.838 0-9.6704 3.0554-15.109 9.5531-4.4368 5.3007-7.8622 11.473-11.106 20.012-2.4001 6.3176-2.6377 8.384-2.1033 18.295 0.25976 4.8176 0.24223 4.9138-1.591 8.7252l-1.8537 3.8539 0.23774 6.1072c0.22427 5.7614 0.1565 6.3332-1.1969 10.1-1.2662 3.5241-1.4346 4.6787-1.4346 9.8344 0 4.0512 0.29693 7.0652 0.96882 9.8339 0.53286 2.1958 1.113 5.0714 1.2892 6.3902 0.23952 1.7925 0.63687 2.6052 1.5741 3.2193 0.68954 0.4518 1.7259 1.7485 2.3029 2.8815 1.2126 2.3809 7.5477 9.1108 9.5623 10.158 1.9717 1.0252 2.3388 2.0114 3.204 8.6089 0.42675 3.2541 1.7708 10.442 2.9868 15.973 2.6338 11.981 4.1675 21.247 4.3645 26.369l0.14395 3.7417-3.6536 1.3595c-6.0862 2.2647-8.1315 4.0011-8.1509 6.9196-8e-3 1.2539 0.42567 2.1212 1.6983 3.3938 1.9585 1.9585 2.9857 2.0838 7.4968 0.91489 3.4987-0.9066 3.407-0.96057 5.6247 3.3086 1.8374 3.5369 5.0799 7.9238 10.836 14.659 2.9169 3.4136 5.9421 7.0555 6.7227 8.0933 0.79891 1.0621 2.107 2.0862 2.9927 2.3429 2.7251 0.78997 7.4544 0.62139 9.3667-0.33388zm6.8456-29.91c-0.42867-2.285-2.9848-5.8088-4.6817-6.454-0.8787-0.33407-2.8187-0.33555-5.7848-5e-3 -2.4545 0.27404-4.7632 0.38293-5.1305 0.24198-0.64532-0.24751-8.8464-31.058-8.8464-33.235 0-1.1864 4.8527-5.95 6.8253-6.7 0.85001-0.32317 4.2641-0.39376 9.2043-0.19029 6.3978 0.2635 8.4256 0.17266 10.942-0.49018 1.6991-0.4475 3.7497-0.81363 4.5568-0.81363 2.4501 0 3.7284 1.7382 13.128 17.849 6.8955 11.819 9.484 17.185 8.8196 18.281-0.81888 1.3505-3.7843 2.55-9.0484 3.6601-6.4628 1.3629-7.43 1.9635-7.0551 4.3807 0.15654 1.0092 0.42759 2.3121 0.60233 2.8954 0.39111 1.3054-0.73915 1.5897-8.1141 2.0409l-5.0848 0.31112-0.33253-1.7726zm69.812-200.14c-0.16881-0.67258 0.0132-3.234 0.4045-5.6921l0.71144-4.4693 0.3712 3.2682c0.47055 4.1429 0.2174 7.6567-0.57027 7.9156-0.33547 0.11027-0.74806-0.34981-0.91687-1.0224zm54.069-27.551c8.8624-0.9521 17.502-2.5191 21.962-3.9834l4.4348-1.4561 2.2363 2.113c1.7457 1.6495 1.6044 1.4136-0.64442-1.0753-5.016-5.5516-8.1727-7.542-13.659-8.6124-1.6592-0.32373-4.8268-1.1179-7.0391-1.7648s-4.747-1.3254-5.6328-1.5077-2.1822-0.78127-2.8811-1.331c-0.69885-0.54971-2.6892-1.2356-4.423-1.5241-1.7338-0.28853-5.1036-0.95441-7.4884-1.4797-6.9721-1.5358-11.718-1.1195-17.365 1.523-3.4116 1.5965-4.4449 2.9229-4.002 5.1375 0.26516 1.3258 0.20188 1.4111-0.6921 0.93263-0.77605-0.41532-1.1966-0.3139-1.9906 0.48005-0.74846 0.74845-1.3962 0.92872-2.5255 0.70286-1.2309-0.24619-1.5188-0.13557-1.5188 0.58354 0 1.7506-1.4908 2.2347-5.8855 1.9112-3.3828-0.24905-4.359-0.1509-5.421 0.54499-0.71243 0.46681-1.1738 1.0453-1.0254 1.2856 0.88301 1.4287 26.52 7.5713 34.455 8.2553 3.1557 0.27204 13.4-0.12215 19.106-0.7352zm-54.461-5.5814c-0.1605-0.4011-0.27964-0.28196-0.30376 0.30377-0.0218 0.53002 0.097 0.82699 0.26407 0.65991 0.16708-0.16707 0.18493-0.60073 0.0397-0.96368z\" fill=\"#fc0404\"/>\n<path d=\"m374.56 684.45c-6.2942-0.49236-17.614-1.8441-22.942-2.7396-55.31-9.2957-103.06-40.51-134.26-87.763-13.886-21.031-23.339-44.193-28.503-69.837-5.9984-29.786-4.4658-63.151 4.2442-92.394 12.959-43.51 39.472-80.156 77.559-107.2 18.46-13.108 39.072-22.742 61.182-28.594 19.055-5.0435 32.637-6.8518 51.521-6.8596 53.127-0.022 104.11 21.936 141.57 60.975 24.581 25.618 41.135 55.168 49.492 88.349 4.3825 17.399 6.0372 30.63 6.0372 48.268 0 17.654-1.6609 30.92-6.0428 48.268-10.852 42.964-36.02 80.83-72.393 108.92-27.992 21.614-61.5 34.953-99.05 39.428-8.0121 0.95492-23.234 1.5901-28.408 1.1854zm-63.101-62.421c2.8455-1.4215 2.6597-3.0496-0.98066-8.5935-1.6729-2.5477-3.0417-4.7688-3.0417-4.9356 0-0.31222 5.7931 0.0925 9.2201 0.64413 1.2874 0.20723 3.1281-0.0413 5.5307-0.74676 6.1889-1.8172 13.594-2.7133 23.499-2.8438 6.7238-0.0886 9.6397-0.31064 10.412-0.79281 1.0083-0.6297 2.2155-2.5971 2.8314-4.6147 0.20997-0.68775 0.59183-0.81808 1.6661-0.56868 2.1966 0.50997 3.4745 1.5142 5.2083 4.0929 2.2836 3.3964 3.3502 4.1329 5.9899 4.1362 1.7807 2e-3 3.0373-0.46324 5.9007-2.1856 2.7234-1.6382 4.3756-2.2719 6.5711-2.5203 3.7714-0.42669 5.126-1.3581 5.126-3.5248 0-1.9836-1.7992-4.8328-3.5981-5.6981-0.71391-0.3434-3.0757-0.96447-5.2484-1.3802-3.0531-0.58416-4.2572-1.0704-5.3012-2.141-0.74297-0.76185-5.6747-9.1821-10.959-18.712-9.0635-16.343-12.099-22.922-12.099-26.219 0-1.1332 3.2648-6.1441 5.9124-9.0748 2.7491-3.0429 6.1164-5.2627 11.23-7.4034 2.6008-1.0886 6.8114-2.8992 9.3569-4.0234 5.7367-2.5336 9.926-3.2549 16.489-2.839 8.2525 0.52305 15.284-0.34792 21.417-2.6529 12.178-4.5766 15.505-7.0872 27.719-20.918 2.1284-2.4101 2.9027-2.0735 2.9027 1.2618 0 2.9105 1.2457 9.3281 2.3429 12.07 0.4175 1.0435 1.249 2.2157 1.8478 2.605 1.5124 0.98335 5.8285 1.9493 8.7219 1.9519 2.241 2e-3 2.58-0.17126 4.5212-2.3108 1.1542-1.2722 2.4504-3.3849 2.8804-4.695 1.1345-3.4564 1.8623-10.988 1.7754-18.375-0.0416-3.5419 0.0384-6.554 0.17783-6.6934 0.13946-0.13946 0.57808 0.72218 0.97473 1.9147 0.448 1.3469 1.2235 2.4515 2.0473 2.916 1.188 0.66979 1.6551 0.65433 4.4848-0.14845 6.0636-1.7202 5.9427-1.7557 3.3106 0.97367-2.9563 3.0656-4.4001 6.19-4.4145 9.5529-0.0275 6.4276 4.4791 10.712 10.644 10.12 3.1115-0.29898 4.9638-1.6445 5.9374-4.313 0.96943-2.657 6.6377-9.815 8.8597-11.188 1.9258-1.1902 2.4739-2.0387 3.4925-5.4069 0.39068-1.2918 1.6141-3.7664 2.7187-5.499l2.0084-3.1502 11.949 0.33536c13.045 0.36611 16.043 0.13995 17.62-1.3292 1.2215-1.138 2.0087-5.9765 1.3011-7.9973-0.43865-1.2527-0.63575-1.3099-5.356-1.5544-4.6697-0.24181-4.9554-0.32247-6.0632-1.7118-1.0546-1.3226-1.3678-1.4305-3.3715-1.1618-1.6954 0.22741-2.5256 0.68381-3.571 1.9632l-1.3621 1.6669-23.037-0.0985c-22.756-0.0973-37.993-0.61158-38.687-1.3058-0.424-0.42399 0.30717-3.5354 1.7539-7.4634 0.87268-2.3694 1.1725-5.2136 1.8284-17.344 0.68173-12.608 0.9201-14.79 1.8185-16.646 2.2034-4.5517 18.954-18.232 22.323-18.232 0.33632 0 1.2032-0.46541 1.9263-1.0342s2.6203-1.2438 4.2158-1.5c15.206-2.4412 15.873-2.7196 16.13-6.7263 0.15125-2.3648 0.074-2.5181-2.5248-5.0112-1.4745-1.4145-5.6396-4.3177-9.2557-6.4515-7.2077-4.2532-8.6228-5.6162-16.005-15.418-4.1607-5.5241-12.61-15.171-15.189-17.34-2.3009-1.9361-6.086-3.6644-9.472-4.325-1.6592-0.32373-4.8268-1.1179-7.0391-1.7648s-4.747-1.3254-5.6328-1.5077-2.1822-0.78127-2.8811-1.331c-0.69885-0.54971-2.6892-1.2356-4.423-1.5241-1.7338-0.28853-5.1036-0.95441-7.4884-1.4797-6.9721-1.5358-11.718-1.1195-17.365 1.523-3.4116 1.5965-4.4449 2.9229-4.002 5.1375 0.26516 1.3258 0.20188 1.4111-0.6921 0.93263-0.77605-0.41532-1.1966-0.3139-1.9906 0.48005-0.74846 0.74845-1.3962 0.92872-2.5255 0.70286-1.2309-0.24619-1.5188-0.13557-1.5188 0.58354 0 1.7421-1.494 2.2345-5.8155 1.9166-5.731-0.4216-7.1622 0.61982-7.9544 5.788-0.18389 1.1997-1.3931 4.2071-2.6871 6.6831-1.9252 3.6838-2.3903 5.092-2.5595 7.7489-0.20768 3.2616-0.43955 3.7016-1.4292 2.7119-0.59445-0.59445-2.18 0.64605-2.18 1.7056 0 0.68552-3.8434 2.0162-4.5544 1.5768-0.26044-0.16097-0.47354-0.5945-0.47354-0.9634 0-1.0615-0.77553-1.1176-9.3017-0.67272-5.7077 0.29781-11.842 1.0799-21.117 2.6921-14.318 2.4889-16.114 2.9257-16.535 4.0223-0.21146 0.55105-0.7707 0.65988-2.209 0.42989-3.939-0.62988-10.006 2.151-18.157 8.322-2.7874 2.1105-5.6059 3.8-7.0594 4.2316-3.7737 1.1207-5.3347 2.1141-7.3849 4.6998-2.6108 3.2928-3.1288 3.653-5.2523 3.653-4.838 0-9.6704 3.0554-15.109 9.5531-4.4368 5.3007-7.8622 11.473-11.106 20.012-2.4001 6.3176-2.6377 8.384-2.1033 18.295 0.25976 4.8176 0.24223 4.9138-1.591 8.7252l-1.8537 3.8539 0.23774 6.1072c0.22427 5.7614 0.1565 6.3332-1.1969 10.1-1.2662 3.5241-1.4346 4.6787-1.4346 9.8344 0 4.0512 0.29693 7.0652 0.96882 9.8339 0.53286 2.1958 1.113 5.0714 1.2892 6.3902 0.23952 1.7925 0.63687 2.6052 1.5741 3.2193 0.68954 0.4518 1.7259 1.7485 2.3029 2.8815 1.2126 2.3809 7.5477 9.1108 9.5623 10.158 1.9717 1.0252 2.3388 2.0114 3.204 8.6089 0.42675 3.2541 1.7708 10.442 2.9868 15.973 2.6338 11.981 4.1675 21.247 4.3645 26.369l0.14395 3.7417-3.6536 1.3595c-6.0862 2.2647-8.1315 4.0011-8.1509 6.9196-8e-3 1.2539 0.42567 2.1212 1.6983 3.3938 1.9585 1.9585 2.9857 2.0838 7.4968 0.91489 3.4987-0.9066 3.407-0.96057 5.6247 3.3086 1.8374 3.5369 5.0799 7.9238 10.836 14.659 2.9169 3.4136 5.9421 7.0555 6.7227 8.0933 0.79891 1.0621 2.107 2.0862 2.9927 2.3429 2.7251 0.78997 7.4544 0.62139 9.3667-0.33388zm6.8456-29.91c-0.42867-2.285-2.9848-5.8088-4.6817-6.454-0.8787-0.33407-2.8187-0.33555-5.7848-5e-3 -2.4545 0.27404-4.7632 0.38293-5.1305 0.24198-0.64532-0.24751-8.8464-31.058-8.8464-33.235 0-1.1864 4.8527-5.95 6.8253-6.7 0.85001-0.32317 4.2641-0.39376 9.2043-0.19029 6.3978 0.2635 8.4256 0.17266 10.942-0.49018 1.6991-0.4475 3.7497-0.81363 4.5568-0.81363 2.4501 0 3.7284 1.7382 13.128 17.849 6.8955 11.819 9.484 17.185 8.8196 18.281-0.81888 1.3505-3.7843 2.55-9.0484 3.6601-6.4628 1.3629-7.43 1.9635-7.0551 4.3807 0.15654 1.0092 0.42759 2.3121 0.60233 2.8954 0.39111 1.3054-0.73915 1.5897-8.1141 2.0409l-5.0848 0.31112-0.33253-1.7726z\"/>\n</g>\n</g>\n</svg>";
const char webSvgMicro[] PROGMEM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg enable-background=\"new 0 0 480 480\" version=\"1.1\" viewBox=\"0 0 480 480\" xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\">\n<path d=\"M288,432h112l32-32V80l-32-32H80L48,80v320l32,32h112H288z\" fill=\"#B3B3B3\"/>\n<path d=\"M96,96h288v288H96V96z\" fill=\"#E6E6E6\"/>\n<path d=\"m264 384v64c0 13.255-10.745 24-24 24s-24-10.745-24-24v-64h48z\" fill=\"#8C6239\"/>\n<path d=\"m372.21 230.22l-25.256 10.632-10.768 25.976 10.36 25.432-26.064 26.072-25.44-10.4-25.976 10.76-10.664 25.304h-36.8l-10.632-25.264-26.008-10.736-25.44 10.4-26.064-26.072 10.4-25.432-10.768-25.976-25.256-10.632v-36.936l25.256-10.632 10.768-25.976-10.4-25.432 26.064-26.064 25.44 10.352 25.976-10.76 10.664-25.264h36.8l10.632 25.264 26.008 10.76 25.44-10.352 26.064 26.064-10.36 25.432 10.768 25.976 25.256 10.632v36.872z\" fill=\"#F7931E\"/>\n<circle cx=\"240\" cy=\"211.79\" r=\"72\" fill=\"#E6E6E6\"/>\n<path d=\"m216 432h48v16c0 13.255-10.745 24-24 24s-24-10.745-24-24v-16z\" fill=\"#754C24\"/>\n<path d=\"M440,80c0-2.122-0.844-4.156-2.344-5.656l-32-32c-1.5-1.5-3.534-2.344-5.656-2.344h-32V0h-16v40h-24V0h-16v40h-24V0h-16v40  h-24V0h-16v40h-24V0h-16v40h-24V0h-16v40h-24V0h-16v40H80c-2.122,0-4.156,0.844-5.656,2.344l-32,32C40.844,75.844,40,77.878,40,80  v32H0v16h40v24H0v16h40v24H0v16h40v24H0v16h40v24H0v16h40v24H0v16h40v24H0v16h40v32c0,2.122,0.844,4.156,2.344,5.656l32,32  c1.5,1.5,3.534,2.344,5.656,2.344h32v40h16v-40h24v40h16v-40h24v-16H83.312L56,396.688V83.312L83.312,56h313.376L424,83.312v313.376  L396.688,424H288v16h24v40h16v-40h24v40h16v-40h32c2.122,0,4.156-0.844,5.656-2.344l32-32c1.5-1.5,2.344-3.534,2.344-5.656v-32h40  v-16h-40v-24h40v-16h-40v-24h40v-16h-40v-24h40v-16h-40v-24h40v-16h-40v-24h40v-16h-40v-24h40v-16h-40V80z\"/>\n<path d=\"M104,104h24V88H96c-4.418,0-8,3.582-8,8v32h16V104z\"/>\n<path d=\"M88,352v32c0,4.418,3.582,8,8,8h32v-16h-24v-24H88z\"/>\n<path d=\"m376 376h-24v16h32c4.418 0 8-3.582 8-8v-32h-16v24z\"/>\n<path d=\"m392 128v-32c0-4.418-3.582-8-8-8h-32v16h24v24h16z\"/>\n<path d=\"m162.54 325.74l22.4-9.12 19.904 8.24 9.36 22.24c1.253 2.976 4.171 4.907 7.4 4.896h10.4v24h-16c-4.418 0-8 3.582-8 8v64c0 17.673 14.327 32 32 32s32-14.327 32-32v-64c0-4.418-3.582-8-8-8h-16v-24h10.4c3.22 1e-3 6.127-1.928 7.376-4.896l9.36-22.232 19.904-8.248 22.4 9.12c2.982 1.217 6.403 0.526 8.68-1.752l26.064-26.072c2.275-2.275 2.965-5.692 1.752-8.672l-9.12-22.4 8.248-19.904 22.24-9.36c2.965-1.252 4.89-4.158 4.888-7.376v-36.848c2e-3 -3.218-1.923-6.124-4.888-7.376l-22.24-9.36-8.264-19.904 9.12-22.4c1.213-2.98 0.523-6.397-1.752-8.672l-26.056-26.072c-2.277-2.278-5.698-2.969-8.68-1.752l-22.4 9.12-19.832-8.24-9.36-22.224c-1.247-2.971-4.154-4.904-7.376-4.904h-36.864c-3.222 0-6.129 1.933-7.376 4.904l-9.424 22.224-19.904 8.248-22.4-9.12c-2.982-1.217-6.403-0.526-8.68 1.752l-26.064 26.072c-2.275 2.275-2.965 5.692-1.752 8.672l9.12 22.4-8.248 19.896-22.24 9.36c-2.965 1.252-4.89 4.158-4.888 7.376v36.864c-2e-3 3.218 1.923 6.124 4.888 7.376l22.24 9.36 8.328 19.896-9.12 22.4c-1.213 2.98-0.523 6.397 1.752 8.672l26.024 26.072c2.279 2.275 5.699 2.963 8.68 1.744zm77.464 138.26c-8.837 0-16-7.163-16-16v-8h32v8c0 8.837-7.163 16-16 16zm16-40h-32v-32h32v32zm-104.8-160.22l-10.76-25.976c-0.804-1.944-2.342-3.493-4.28-4.312l-20.368-8.584v-26.24l20.368-8.568c1.938-0.819 3.476-2.368 4.28-4.312l10.76-25.976c0.8-1.948 0.8-4.132 0-6.08l-8.36-20.52 18.56-18.552 20.512 8.352c1.945 0.816 4.135 0.816 6.08 0l25.984-10.768c1.946-0.806 3.495-2.347 4.312-4.288l8.568-20.36h26.24l8.568 20.36c0.817 1.941 2.366 3.482 4.312 4.288l26.024 10.752c1.942 0.816 4.13 0.816 6.072 0l20.52-8.352 18.56 18.552-8.352 20.536c-0.8 1.948-0.8 4.132 0 6.08l10.76 25.976c0.804 1.944 2.342 3.493 4.28 4.312l20.368 8.576v26.232l-20.368 8.584c-1.938 0.819-3.476 2.368-4.28 4.312l-10.76 25.976c-0.798 1.945-0.798 4.127 0 6.072l8.336 20.552-18.56 18.552-20.512-8.352c-1.948-0.8-4.132-0.8-6.08 0l-25.984 10.752c-1.946 0.806-3.495 2.347-4.312 4.288l-8.568 20.36h-26.24l-8.568-20.368c-0.819-1.943-2.371-3.484-4.32-4.288l-25.992-10.76c-1.945-0.798-4.127-0.798-6.072 0l-20.52 8.352-18.544-18.536 8.336-20.552c0.798-1.945 0.798-4.127 0-6.072z\"/>\n<path d=\"m240 291.79c44.183 0 80-35.817 80-80s-35.817-80-80-80-80 35.817-80 80c0.053 44.161 35.839 79.947 80 80zm0-144c35.346 0 64 28.654 64 64s-28.654 64-64 64-64-28.654-64-64c0.04-35.33 28.67-63.96 64-64z\"/>\n<path d=\"m232 203.79h16v16h-16v-16z\"/>\n<path d=\"m200 203.79h16v16h-16v-16z\"/>\n<path d=\"m264 203.79h16v16h-16v-16z\"/>\n</svg>";

#endif
