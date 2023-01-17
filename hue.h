#include "secrets.h"

#define HUE_BRIDGE_IP SECRET_HUE_BRIDGE_IP
#define HUE_PERIOD 1000
#define HUE_LIGHT_BEDROOM 14
#define HUE_LIGHT_LIVING_ROOM_L 7
#define HUE_LIGHT_LIVING_ROOM_R 8
#define HUE_LIGHT_ARCO 6
#define HUE_LIGHT_PLUG 17
#define N_HUE_LIGHTS 4
#define N_HUE_COLOURS 4


void hueTicker();

void printHueLightInfo(hueDino hue){

  //Serial.println(); //most hueDino methods return strings containing the raw json responses


  Serial.print("hueDino found: ");
  Serial.print(hue.numLights);
  Serial.println(" connected lights");
  Serial.println();
  Serial.println("Available Light IDs: ");
  
  for(int i=0; i<hue.numLights; i++)
  {
      Serial.print(hue.lightIds[i]);
      Serial.print(",");
  }

}


void setupHue(hueDino hue) {

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_L, 254);

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_R, 254);

  delay(100);

  hue.brightness(HUE_LIGHT_ARCO, 254);
  hue.colorLoop(HUE_LIGHT_ARCO, 1);

}

