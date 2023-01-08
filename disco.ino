#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WiFiNINA.h>  // JV : Wireless Mkr1010
#include <WiFiUdp.h>   // JV : UDP service
#include "./include/hueDino-master/src/hueDino.h"
#include "./include/microxpath-master/src/MicroXPath.h"
#include "./include/microxpath-master/src/MicroXPath_P.h"
#include "./include/Sonos-ESP32-master/src/SonosUPnP.h"


 /******************************************************************* 
  The typical 'hello world' of embedded development, blinky! In this 
  example sketch the hueDino library queries the Hue Bridge for all 
  established groups. If groups are found it then toggles all groups 
  on, and then off, every 3 seconds. The sequence of On and Off 
  states are printed to the terminal if '#define DEBUG' is uncommented 
  in hueDino.h.
  
  Check out the included Arduino sketch examples to get started!
  https://github.com/andium/hueDino

  Written by Brian Carbonette Copyright © 2017 Andium 
  
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
 
  http://www.apache.org/licenses/LICENSE-2.0
 
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *******************************************************************/
 
#include "hueDino.h"
#include "secrets.h"

WiFiClient wifi;
hueDino hue = hueDino(wifi, SECRET_HUE_BRIDGE_IP);

void setup() {
  Serial.begin(115200);

  delay(3000);

  connectToWiFi();

  //Start Hue
  hue.begin(SECRET_HUE_USERNAME);
}

void loop() {

  //Blinky!
  hue.lightOn(13);  //turns all hue lights on
  delay(3000);
  hue.lightOff(13); //turns all hue lights off
  delay(3000);

}

void connectToWiFi()
{
  int status = WL_IDLE_STATUS;
   
  while(status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(SECRET_SSID);                   // print the network name (SSID);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
}

