#include<Adafruit_NeoPixel.h>
#include<ESP8266WiFi.h>
#include<WiFiManager.h>
#include<ESP8266WebServer.h>
#include<WebSocketsServer.h>
#include<EEPROM.h>

#define INIT
#define PixelCount 16
#define DI  5

#include "index.h"
#include "script.h"
#include "styles.h"

Adafruit_NeoPixel arc = Adafruit_NeoPixel(PixelCount, DI, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

IPAddress apIP(192, 168, 4,1);  
IPAddress gateway(192, 168,12, 7);
IPAddress subnet(255, 255, 255, 0); 

char* ssid = "NeoRGB";
uint32_t neoPixelColors[16];
int32_t count = -1;
bool countStatus = 0;
int32_t cf[10] = {100,0,0,0,0,-1,0,0,0,0};
//chase
uint32_t chaseVector[16];

void handleOtherFiles(){
  if(checkInFS(server.uri())){
    return;
  }
  server.send(404,"text.plain", "please restart the wear"); 
}

void returnOK(){
  server.send(200, "text/plain", "");
}


bool checkInFS(String path){
  String dataType = "text/plain";
  const char* data;
  
  if(path.endsWith("/") || path.endsWith(".html")){
    dataType = "text/html";
    data = _index;
  }
  else if(path.endsWith(".css")){
      dataType = "text/css";
      data = _styles;
  }else if(path.endsWith(".js")){
      dataType = "application/js";
      data = _script;
  }else{
      return false;
  }
  server.send_P(200, dataType.c_str(), data);
  return true;
}

unsigned long tChase = 0;
unsigned long tupdate =0;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(64);
  arc.begin();
  arc.setBrightness(30);
  for(int i=0; i<16; i++)
    arc.setPixelColor(i, 0xff0000);
  arc.show();
  delay(1);
#ifdef INIT
if(EEPROM.read(0) == 84){
  for(int i=1; i<7; i++)
   cf[i] = EEPROM.read(i);
  count = cf[5];
  countStatus = cf[2+count];
}else{
  EEPROM.write(0, 84);
  for(int i=1; i<7; i++){
      EEPROM.write(i, cf[i]);
  }
  EEPROM.commit();
}
#endif
  if(cf[1] == 1){
    WiFi.config(apIP, gateway, subnet);
    WiFi.mode(WIFI_AP);
    WiFi.disconnect();
    delay(100);
        //changing softAP config and starting the Start AP
    WiFi.softAPConfig(apIP, gateway, subnet);
    WiFi.softAP("NeoRGB_AP");
  }else{
    WiFiManager wifimanager;
    wifimanager.autoConnect(ssid);
    delay(100);
  }
  
  Serial.println(WiFi.localIP());
  
  for(int i=0; i<16; i++)
    arc.setPixelColor(i, 0x00ff00);
  arc.show();
  delay(1);

  
  arc.setBrightness(255);
  server.onNotFound(handleOtherFiles);
  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(socketHandle);
}


void loop(){
  server.handleClient();
  webSocket.loop();
  feature();
  save();
  delay(1);
  wdt_reset();
}

void socketHandle(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    //do all stuff here
    switch(payload[0]){
     case 'n':{
        applyColor((char*)(&payload[1]));
        break;
     }
     case 'M' : {
                  count = payload[1] - 48;
                  countStatus = (bool)(payload[2] - 48);
                  cf[2] = 0;
                  cf[3] = 0;
                  cf[4] = 0;
                  cf[2+count] = countStatus;//update cf[2 - 4]
                  cf[5]= count;
                  break;
                }
     case 'C' : {
                  control((char*) &payload[1]);
                  break;
                }
     case 'B' : {
                   cf[0] = (uint16_t) strtol((const char *)&payload[1], NULL, 10);
                   break;
                }
     case 'I' : {
                  webSocket.broadcastTXT("c"+createCFJSON());
                }
  }
  //Serial.println(String((char *) &payload[1]));
}
}


void feature(){
  switch(count){
    case 0:{      
      //chase
      if(countStatus)
      if(millis() - tChase > 100){
      //Rotate Array
      uint32_t temp = chaseVector[0];
      for(int i=0; i<PixelCount-1; i++){
        chaseVector[i] = chaseVector[i+1];
        arc.setPixelColor(i,chaseVector[i]);
      }
      arc.setPixelColor(PixelCount - 1, temp);
      chaseVector[PixelCount - 1] = temp;
      arc.show();
      tChase = millis();
      }
      break;
    }
    case 1:{
      
      if(countStatus){
      arc.clear();
      arc.show();
      }else{
       for(int i=0; i<PixelCount; i++)
         arc.setPixelColor(i,chaseVector[i]);
        arc.show();
      }
      break;
    }
    case 2:{
     
      if(countStatus){
      for(int i=0; i<PixelCount; i++)
        arc.setPixelColor(i, 0xFFFFFF);
      arc.show();
      }else{
       for(int i=0; i<PixelCount; i++)
        arc.setPixelColor(i,chaseVector[i]);
       arc.show();
      }
      break;
    }
  }
}


void control(char * payload){
  switch(payload[0]){
    case 'W' : 
              cf[1] = (payload[1] - 48);
              break;
    case 'T' : 
              cf[6] = (payload[1] - 48);
              break;
    case 'R' : 
              ESP.restart();
  }
}

void applyColor(char * serverArg){
  for(int i=0; i<PixelCount; i++){
    char temp[6] = "";
    for(int j=0; j<6; j++){
      temp[j] = serverArg[(i*6) + j]; //take a slice
    }
     neoPixelColors[i] = StringToHex(temp);
     chaseVector[i] = neoPixelColors[i];
     arc.setPixelColor(i, neoPixelColors[i]);
  }
  arc.show();
}

void save(){
  if(millis() - tupdate > 1000){     
    for(int i=1; i<7; i++){
      EEPROM.write(i, cf[i]);
    }
    EEPROM.commit();
    tupdate = millis();
  }
}

uint32_t StringToHex(char * num){
  uint32_t hexVal = 0;
  for(int i=0; i<6; i++){
    hexVal*=16;
    hexVal +=(num[i]>='0' && num[i]<='9')? num[i] - '0' : num[i] - 'a' + 10;
  }
  return hexVal;
}

String hexToString(uint32_t num){
  String hexVal = "";
  while(num != 0){
    int rem = num%16;
    char stRem = (rem >= 10)? ('a' +(rem-10)) : ('0'+rem);
    hexVal =  stRem + hexVal;
    num/=16;
  }
  hexVal = "000000" + hexVal;
  return "#" + hexVal.substring(hexVal.length() - 6);
}

String createCFJSON(){
  return "{\"br\" : " + String(cf[0]) + ", \"wifimode\" : " + String(cf[1]) + ", \"chase\" : " + String(cf[2]) + ", \"pf\" : " + String(cf[3]) + ", \"flash\" : " + String(cf[4]) + ", \"realTime\" : " + String(cf[6]) + "}";
}
