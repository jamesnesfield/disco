#ifndef DISCO_HUE
#define DISCO_HUE


#include "secrets.h"
#include "wifi.h"
#include "./include/hueDino-master/src/hueDino.h"
#include "hueDino.h"

//#define DEBUG_MODE_HUE

#define HUE_BRIDGE_IP SECRET_HUE_BRIDGE_IP
#define HUE_PERIOD 500
#define HUE_LIGHT_BEDROOM 14
#define HUE_LIGHT_LIVING_ROOM_L 7
#define HUE_LIGHT_LIVING_ROOM_R 8
#define HUE_LIGHT_LIVING_ROOM_NORMAL_HUE 8596
#define HUE_LIGHT_LIVING_ROOM_NORMAL_SAT 121
#define HUE_LIGHT_LIVING_ROOM_NORMAL_BRI 194
#define HUE_LIGHT_ARCO 6
#define HUE_LIGHT_ARCO_NORMAL_HUE 8596
#define HUE_LIGHT_ARCO_NORMAL_SAT 121
#define HUE_LIGHT_ARCO_NORMAL_BRI 194
#define HUE_LIGHT_PLUG 17
#define N_HUE_LIGHTS 3
#define N_HUE_COLOURS N_HUE_LIGHTS

void hueTimerCallback();

hueDino hue = hueDino(wifi, SECRET_HUE_BRIDGE_IP);
Ticker hueTimer(hueTimerCallback, HUE_PERIOD); // changing led every 500ms
unsigned long hue_index = 0;
const int hueColours[] = {0, 25500, 46920};
bool lastInfernoState = false;

void setupHue() {
  hueTimer.stop();
}

void hueStartTheParty(){

  lastInfernoState = true;

#ifndef DEBUG_MODE_HUE

  hue.lightOn(HUE_LIGHT_PLUG);

  delay(10);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_L, hueColours[random(0 ,N_HUE_LIGHTS)]);

  delay(10);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_R, hueColours[random(0, N_HUE_LIGHTS)]);

  delay(10);

  hue.brightness(HUE_LIGHT_ARCO, 254);
  hue.sat(HUE_LIGHT_ARCO, 254);
  hue.hue(HUE_LIGHT_ARCO, hueColours[random(0, N_HUE_LIGHTS)]);

  delay(10);

#endif

  hueTimer.start();

}

void randomiseHue(hueDino hue){
  
  Serial.println("Hue: changing colour of lights.");

#ifndef DEBUG_MODE_HUE

  ++hue_index;

  switch(hue_index % N_HUE_LIGHTS - 1) {
    case 0:
        hue.hue(HUE_LIGHT_LIVING_ROOM_L, hueColours[random(0, N_HUE_LIGHTS)]);
        break;
    case 1:
        hue.hue(HUE_LIGHT_LIVING_ROOM_R, hueColours[random(0, N_HUE_LIGHTS)]);
        break;
    default:
        hue.hue(HUE_LIGHT_ARCO, hueColours[random(0, N_HUE_LIGHTS)]);
  }
    
#endif

}


void hueStopTheParty(){

  hueTimer.stop();
  lastInfernoState = false;

#ifndef DEBUG_MODE_HUE

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_L, HUE_LIGHT_LIVING_ROOM_NORMAL_BRI);
  hue.sat(HUE_LIGHT_LIVING_ROOM_L, HUE_LIGHT_LIVING_ROOM_NORMAL_SAT);
  hue.hue(HUE_LIGHT_LIVING_ROOM_L, HUE_LIGHT_LIVING_ROOM_NORMAL_HUE);

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_R, HUE_LIGHT_LIVING_ROOM_NORMAL_BRI);
  hue.sat(HUE_LIGHT_LIVING_ROOM_R, HUE_LIGHT_LIVING_ROOM_NORMAL_SAT);
  hue.hue(HUE_LIGHT_LIVING_ROOM_R, HUE_LIGHT_LIVING_ROOM_NORMAL_HUE);

  delay(100);

  hue.brightness(HUE_LIGHT_ARCO, HUE_LIGHT_ARCO_NORMAL_BRI);
  hue.sat(HUE_LIGHT_ARCO, HUE_LIGHT_ARCO_NORMAL_SAT);
  hue.hue(HUE_LIGHT_ARCO, HUE_LIGHT_ARCO_NORMAL_HUE);
  hue.colorLoop(HUE_LIGHT_ARCO, false);

  delay(100);

  hue.lightOn(HUE_LIGHT_PLUG);

#endif

}


void hueTimerCallback(){

  if(discoInferno && !lastInfernoState) {
    hueStartTheParty();
  } else if (!discoInferno && lastInfernoState) {
    hueStopTheParty();
  } else if(discoInferno) {
    randomiseHue(hue);
  }
}


#endif

