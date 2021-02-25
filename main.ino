#include<Adafruit_NeoPixel.h>
#include<ArduinoJson.h>
#include<ESP8266WiFi.h>
#include<WiFiManager.h>
#include<ESP8266WebServer.h>
#include<WebSocketsServer.h>
#include<ESP8266HTTPUpdateServer.h>
#include "index.h"
#include "script.h"
#include "styles.h"

#define DI  5
Adafruit_NeoPixel arc = Adafruit_NeoPixel(16, DI, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266HTTPUpdateServer httpUpdater;

char* ssid = "NeoRGB";
uint32_t neoPixelColors[16];


void handleOtherFiles(){
  if(checkInFS(server.uri())){
    return;
  }
  server.send(404,"text.plain", "please restart the car"); 
}


bool checkInFS(String path){
  String dataType = "text/plain";
  const char* data;
  if(path.endsWith("/") || path.endsWith(".html")){
    dataType = "text/html";
    data = html;
  }else if(path.endsWith(".css")){
    dataType = "text/css";
    data = css;
  }else if(path.endsWith(".js")){
    dataType = "application/js";
    data = js;
  }else{
    return false;
  }
  server.send_P(200, dataType.c_str(), data);
  return true;
}


void setup() {
  Serial.begin(115200);
  arc.begin();
  arc.setBrightness(255);
  for(int i=0; i<16; i++)
    arc.setPixelColor(i, 0);
  arc.show();
  
//  WiFi.mode( WIFI_OFF );
//  WiFi.forceSleepBegin();
//  delay(10);
//  WiFi.forceSleepWake();
//  delay(10);
  
  WiFiManager wifimanager;
  wifimanager.autoConnect(ssid);
  delay(100);
  server.on("/jsonfile",HTTP_POST, handleJSON);
  
  server.onNotFound(handleOtherFiles);
  httpUpdater.setup(&server);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(socketHandle);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  delay(1);
  wdt_reset();
}

void socketHandle(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
  }
}

void handleJSON(){
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& colorJSON = jsonBuffer.parseObject(server.arg(0));
  
  for(int i=0; i<16; i++){
    neoPixelColors[i] = StringToHex(colorJSON["n"+String(i)]);
    arc.setPixelColor(i, neoPixelColors[i]);
  }
  arc.show();
  server.send(200, "type/text", "");
}

uint32_t StringToHex(String num){
  uint32_t hexVal = 0;
  for(int i=1; i<=6; i++){
    hexVal*=16;
    hexVal +=(num[i]>='0' && num[i]<='9')? num[i] - '0' : num[i] - 'a' + 10;
  }
  return hexVal;
}
