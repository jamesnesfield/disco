#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WiFiNINA.h>  // JV : Wireless Mkr1010
#include <WiFiUdp.h>   // JV : UDP service
#include "Ticker.h"
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
#include "hue.h"
#include "wifi.h"
#include "secrets.h"

WiFiClient wifi;
hueDino hue = hueDino(wifi, SECRET_HUE_BRIDGE_IP);
Ticker hueTimer(hueTicker, HUE_PERIOD); // changing led every 500ms


unsigned long time_now = 0;
unsigned long hue_index = 0;

const int HueColours[] = {0, 25500, 46920};

void setup() {
  Serial.begin(9600);
  delay(3000);
  //while (!Serial) {;}


  connectToWiFi();
  delay(3000);

  //Start Hue
  hue.begin(SECRET_HUE_USERNAME);
  setupHue(hue);
  printHueLightInfo(hue);

  
  hueTimer.start(); //start the ticker.
}

void loop() {

  hueTimer.update(); 

}


void hueTicker(){

    if(hue_index % 2 == 0){
      hue.hue(HUE_LIGHT_LIVING_ROOM_L, HueColours[hue_index % (N_HUE_COLOURS-1)]);
    } else {
      hue.hue(HUE_LIGHT_LIVING_ROOM_R, HueColours[(hue_index + 1) % (N_HUE_COLOURS-1)]);      
    }
    ++hue_index;
}
