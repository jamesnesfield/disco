#ifndef DISCO_HUE
#define DISCO_HUE


#include "secrets.h"
#include "wifi.h"
#include "./include/hueDino-master/src/hueDino.h"
#include "hueDino.h"

#define HUE_BRIDGE_IP SECRET_HUE_BRIDGE_IP
#define HUE_PERIOD 1000
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
#define N_HUE_LIGHTS 4
#define N_HUE_COLOURS 4

void hueTimerCallback();

hueDino hue = hueDino(wifi, SECRET_HUE_BRIDGE_IP);
Ticker hueTimer(hueTimerCallback, HUE_PERIOD); // changing led every 500ms
unsigned long hue_index = 0;
const int HueColours[] = {0, 25500, 46920};
bool lastInfernoState = false;

void setupHue() {

  delay(100);

  //hue.getLightIds();

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_L, HueColours[random(0,2) % (N_HUE_COLOURS-1)]);

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_R, HueColours[random(0,2) % (N_HUE_COLOURS-1)]);

  delay(100);

  hue.brightness(HUE_LIGHT_ARCO, 254);
  hue.colorLoop(HUE_LIGHT_ARCO, 1);

  delay(100);

  hue.lightOn(HUE_LIGHT_PLUG);

}

void randomiseHue(hueDino hue){
  
    ++hue_index;

    //living room lights
    if(hue_index % 2 == 0){
      hue.hue(HUE_LIGHT_LIVING_ROOM_L, HueColours[random(0,2) % (N_HUE_COLOURS-1)]);

    } else {
      hue.hue(HUE_LIGHT_LIVING_ROOM_R, HueColours[random(0,2) % (N_HUE_COLOURS-1)]);
    }

    //arco
    if(random(0,9) == 0){
      hue.flash(HUE_LIGHT_ARCO);
    } else {
      hue.colorLoop(HUE_LIGHT_ARCO, true);
    }

}

void backToNormalHue(){

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

}

void hueTimerCallback(){
  if(discoInferno && !lastInfernoState) {
    Serial.println("Hue: Put on the party lights.");
    lastInfernoState = true;
  } else if (!discoInferno && lastInfernoState) {
    Serial.println("Hue: Putting lights back to normal.");
    #ifdef ENABLE_HUE
      backToNormalHue();
    #endif
    lastInfernoState = false;
  } else if(discoInferno) {
    //Serial.println("Changing party lights");
    #ifdef ENABLE_HUE
      randomiseHue(hue);
    #endif
  }
}


#endif

