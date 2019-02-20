#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>

//Wifi 
//const char *ssid = "Smarttube";
//const char *password = "GC2019";

int count = 0;


AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
  WiFi.softAP("Smarttube", "");
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());



  server.on("/count", HTTP_GET, [](AsyncWebServerRequest *request){
    char cstr[16];
    itoa(count, cstr, 10);
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", cstr);
    response->addHeader("Server","Dropcount");
    int paramsNr = request->params();
    Serial.println(count);
 
    
    request->send(response);
  });
 

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", "success");
    response->addHeader("Server","Resetcount");
    int paramsNr = request->params();
    //Serial.println(paramsNr);
    count = 0;
    request->send(response);
  });

   server.on("/inc", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", "incremented");
    response->addHeader("Server","Increment");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });

  server.on("/ident", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", "Medication ID");
    response->addHeader("Server","MID");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });

  server.on("/exp", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", "Expiration Date");
    response->addHeader("Server","Expiration");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });
 
  server.begin();
}
 
void loop(){
  }

