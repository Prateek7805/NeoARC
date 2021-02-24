# NeoARC - Neopixel ARC Wearable/lighting - 16 pixel

SuperCool Web interface for RGB NeoPixel Ring to operate in realtime.
```
MCU - ESP8266 (ESP8285)
NeoPixel Ring - 16 Pixels WS2812 5050
```
```
Connection
ESP8266       NeoPixel
GPIO 5        DI
3.3V          5V(VCC)
GND           GND

Optional:
LiPo battery with a TP4056 charger module.
```

The project is an attempt to use WebSockets to update the color of a neoPixel ring in realtime.

WebSockets is a protocol which allows bidirectional communication between client and server at high speeds suited for projects with the requirement of fast response time.

It also uses XMLHttpRequests to send the actual pixel colors in hex using JSON.

I have used the following external libraries:
  
 [ArduinoJSON by bblanchon](https://github.com/bblanchon/ArduinoJson)
 [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets)
 [ESP8266HTTPUpdateServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer)
 [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
 [WiFiManager](https://github.com/tzapu/WiFiManager)
 
 
