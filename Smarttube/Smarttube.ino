#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
//#include <Dropcounter.h>
//#include <Memorymanager.h>

//Wifi 
//const char *ssid = "Smarttube";
//const char *password = "GC2019";

int count = 0;
int IndentID= 0;
int gcount = 0;


AsyncWebServer server(80);


 
void setup(){
  Serial.begin(115200);
 
  WiFi.softAP("Smarttube", "");
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());




 
server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    char send_data[16]="";
    int paramsNr = request->params();
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
         
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        
        if(p->name()=="MedID"){
          //int Med = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(5, send_data,10);
          };
          if(p->name()=="hMedID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(3, send_data,10);
          };
        if(p->name()=="EXP"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(13, send_data,10);
          };
        if(p->name()=="UserID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(42, send_data,10);
          };
        if(p->name()=="GCount"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          itoa(gcount, send_data,10);
          };
        if(p->name()=="count"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          Serial.println(count);
          itoa(count, send_data,10);
          };
        if(p->name()=="reset"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          count = 0;
          };
        if(p->name()=="inc"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          count = count + 1;
          };
        Serial.println("------");
    }
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", send_data);
    response->addHeader("Server","Grab data");
    request->send(response);
    });

  server.on("/count", HTTP_GET, [](AsyncWebServerRequest *request){
    char cstr[16];
    itoa(count, cstr, 10);
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", cstr);
    response->addHeader("Server","Dropcount");
    int paramsNr = request->params();
    Serial.println(count);
    request->send(response);
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "success");
    response->addHeader("Server","Resetcount");
    int paramsNr = request->params();
    //Serial.println(paramsNr);
    count = 0;
    request->send(response);
  });

   server.on("/inc", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "incremented");
    response->addHeader("Server","Increment");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });

  server.on("/ident", HTTP_GET, [](AsyncWebServerRequest *request){
    char idcstr[16];
    // Static Value, change
    itoa(5, idcstr, 10);
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", idcstr);
    response->addHeader("Server","MID");
    int paramsNr = request->params();
    Serial.println(count);
    request->send(response);
  });

  server.on("/exp", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "Expiration Date");
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

