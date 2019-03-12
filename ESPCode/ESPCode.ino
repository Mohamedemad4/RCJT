#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
// from http://playground.arduino.cc/Code/QueueArrayst`
//http://fritzing.org/projects/wifi-serial-monitor
#include <QueueArray.h>

const char* ssid = "3elbet 7alwa";
const char* password = "7alwa_bel_24ta";


ESP8266WebServer server(80);
SoftwareSerial swSer(13, 15); // D7, D8 (sending not used)
QueueArray <char> queue;

const int led = 2;

void handleRoot() {
  digitalWrite(led, 1);

  String output = "<html>\n";
  output += "<head></head>\n";
  output += "<body>\n";
  output += "    <span id='output'></span>\n";
  output += "    <script type='text/javascript'>\n";
  output += "        function getAjax(url, success) {\n";
  output += "            var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');\n";
  output += "            xhr.open('GET', url);\n";
  output += "            xhr.onreadystatechange = function () {\n";
  output += "                if (xhr.readyState > 3 && xhr.status == 200)\n";
  output += "                    success(xhr.responseText);\n";
  output += "            };\n";
  output += "            xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');\n";
  output += "            xhr.send();\n";
  output += "            return xhr;\n";
  output += "        }\n";
  output += "        var span = document.getElementById('output');\n";
  output += "        setInterval(function () {\n";
  output += "            getAjax('/console', function (response) {\n";
  output += "                span.innerHTML = span.innerHTML + response;\n";
  output += "                window.scroll(0, span.offsetHeight)\n";
  output += "            });\n";
  output += "        }, 500);\n";
  output += "    </script>\n";
  output += "</body>\n";
  output += "</html>";
  server.send(200, "text/html", output);

  digitalWrite(led, 0);
}

void handleConsole() {
  digitalWrite(led, 1);

  String output = "";
  while (!queue.isEmpty ())
  {
    char dequeued = queue.dequeue();
    if (dequeued == '\n') {
      output += "<br/>";
    } else {
      output += dequeued;
    }
  }
  server.send(200, "text/text", output);

  digitalWrite(led, 0);
}

void setup(void) {
  swSer.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("AP IP address: ");
  
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/console", handleConsole);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();

  // get input from Arduino
  if (swSer.available())
  {
    char ch = swSer.read();
    queue.enqueue(ch);
  }
}
