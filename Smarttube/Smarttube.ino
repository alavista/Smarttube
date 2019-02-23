#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "EEPROM.h"

//#include <Dropcounter.h>
//#include <Memorymanager.h>

//Wifi 
//const char *ssid = "Smarttube2";
//const char *password = "GC2019";

const char ui_html[] PROGMEM = "<!DOCTYPE html><html><style>h3{color: black; font-family: verdana; font-size: 300%;}a:link, a:visited{width: 100%; background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; border-radius: 4px; cursor: pointer;}a:hover, a:active{background-color: #45a049;}input[type=number]{width: 100%; padding: 12px 20px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box;}input[type=submit]{width: 100%; background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; border-radius: 4px; cursor: pointer;}input[type=submit]:hover{background-color: #45a049;}div{border-radius: 5px; background-color: #f2f2f2; padding: 20px;}</style><body><h3>Farbwerte fuer inneren Ring</h3><div> <form> <label for=\"red\">Red</label> <input type=\"number\" id=\"fname\" name=\"red\" placeholder=\"0\" min=\"0\" max=\"255\"><label for=\"green\">Green</label> <input type=\"number\" id=\"green\" name=\"green\" placeholder=\"0\" min=\"0\" max=\"255\"> <label for=\"blue\">Blue</label> <input type=\"number\" id=\"blue\" name=\"blue\" placeholder=\"0\" min=\"0\" max=\"255\"> <label for=\"white\">White</label> <input type=\"number\" id=\"white\" name=\"white\" placeholder=\"0\" min=\"0\" max=\"255\"> <input type=\"submit\" value=\"Submit\"> </form></div><div><a href=\"/\">Main</a></div><div><a href=\"/LED1\">Innen</a></div><div><a href=\"/LED2\">Aussen</a></div></body></html>";
const char HTML[] PROGMEM = "<!DOCTYPE html><html><style>input[type=text], input[type=number], select{width: 200px; padding: 12px 20px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box;}input[type=submit]{width: 200px; background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; border-radius: 4px; cursor: pointer;}input[type=submit]:hover{background-color: #45a049;}div{display: flex; justify-content: center; border-radius: 5px; background-color: #f2f2f2; padding: 20px;}body{font-family: Verdana,sans-serif;}</style><body><div> <form action=\"\"> <label for=\"pname\">Patient</label><br/> <input type=\"text\" id=\"pname\" name=\"patientname\" placeholder=\"Patient name..\" size=10><br/> <label for=\"medId\">Medicine</label><br/> <select id=\"medID\" name=\"medID\"> <option value=\"0\">Procrastinozin</option> <option value=\"1\">Makeathetamol</option> <option value=\"2\">ITQdipine</option> </select><br/> <label for=\"dose\">Drops</label><br/> <input type=\"number\" id=\"dose\" name=\"dose\" placeholder=\"0\"><br/> <input type=\"submit\" value=\"Submit\"> </form></div></body></html>";

String patientName = "";
int medicine = -1;
int drops = -1;



int count = 0;
int IndentID= 0;
int gcount = 0;
int addr = 0;
int ID = 4;
#define EEPROM_SIZE 512

AsyncWebServer server(80);

 
void setup(){
  Serial.begin(115200);
 
  WiFi.softAP("Smarttube2", "");
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

   Serial.println("start...");
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
 
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
        //Mediacation ID
        if(p->name()=="MedID"){
          //int Med = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(5, send_data,10);
          };
        //historical Mediacation ID
          if(p->name()=="hMedID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(3, send_data,10);
          };
        //Expiration Date
        if(p->name()=="EXP"){
          if(p->value()==""){
             itoa(13, send_data,10);
            }
          else if(p->value().toInt()!=0){
            //MemoryManager.read(ID, Offset)
            //itoa(readval(p->value().toInt(),2), send_data,10);
            }
          
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
         
          };
        //User ID
        if(p->name()=="UserID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(42, send_data,10);
          };
        //Global Count
        if(p->name()=="GCount"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          itoa(gcount, send_data,10);
          };
        //Momentary Count
        if(p->name()=="count"){
          if(p->value()==""){
             //itoa(readval(ID,7), send_data,10);
            }
          else if(p->value().toInt()!=0){
            //MemoryManager.read(ID, Offset)
            //itoa(readval(p->value().toInt(),7), send_data,10);
            }}
        //Reset
        if(p->name()=="reset"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          count = 0;
          };
        //Increase Count by one
        if(p->name()=="inc"){
          //int gcount = memory lookup (Offset,p->value())
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

  server.on("/ui", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", HTML);
    response->addHeader("Server","Innere Beleuchtung");
    int paramsNr = request->params();
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
         
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        
        if(p->name()=="patientname"){
          patientName = p->value();
          Serial.print("patient name: ");
          Serial.println(patientName);
          
          //red1 = p->value().toInt();
          //Serial.println("red set");
        
        }else if(p->name()=="medID"){
          medicine = p->value().toInt();
          Serial.print("medicine: ");
          Serial.println(medicine);
          
          //green1 = p->value().toInt();
          //Serial.println("green set");
          
        }else if(p->name()=="dose"){
          drops = p->value().toInt();
          Serial.print("drops: ");
          Serial.println(drops);
          
          //blue1 = p->value().toInt();
          //Serial.println("blue set");
          }
    }
    request->send(response);
  });
 
  server.begin();
  //Wait for Medication ID
  //Load Data from EEPROM
  //UserID
  //MedID
  //gcount
  //check if UserID matches saved one
  
}
 
void loop(){
 int Reading = analogRead(34);
 //Serial.println(Reading);
 //Serial.println(count);
  if( Reading <= 100){
    count=count+1;
    Serial.println(1);
    delay(200);  
    }
  else{
    Serial.println(0);
    delay(20);
    };
  }
  
