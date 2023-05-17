#ifndef DISCO_HUE
#define DISCO_HUE

#define ENABLE_HUE 1

#define HUE_BRIDGE_IP SECRET_HUE_BRIDGE_IP
#define HUE_PERIOD 500

#define HUE_LIGHT_FIREPLACE 11

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
#define N_HUE_COLOURS 3

void hueTimerCallback();

hueDino hue = hueDino(wifi, SECRET_HUE_BRIDGE_IP);
Ticker hueTimer(hueTimerCallback, HUE_PERIOD); // changing led every 500ms
unsigned long hue_index = 0;
const int hueColours[] = {0, 25500, 46920};

void setupHue() {
  hueTimer.stop();
}

void hueStartTheParty(){

  Serial.println("Hue: starting the party.");

#ifndef DEBUG_MODE_HUE

  hue.lightOn(HUE_LIGHT_PLUG);

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_L, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_L, hueColours[random(0 ,N_HUE_COLOURS)]);

  delay(100);

  hue.brightness(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.sat(HUE_LIGHT_LIVING_ROOM_R, 254);
  hue.hue(HUE_LIGHT_LIVING_ROOM_R, hueColours[random(0, N_HUE_COLOURS)]);

  delay(100);

  hue.brightness(HUE_LIGHT_ARCO, 254);
  hue.sat(HUE_LIGHT_ARCO, 254);
  hue.hue(HUE_LIGHT_ARCO, hueColours[random(0, N_HUE_COLOURS)]);

  delay(100);

  hue.brightness(HUE_LIGHT_FIREPLACE, 254);
  hue.sat(HUE_LIGHT_FIREPLACE, 254);
  hue.hue(HUE_LIGHT_FIREPLACE, hueColours[random(0, N_HUE_COLOURS)]);

#endif

  hueTimer.start();

}

void randomiseHue(hueDino hue){
  
#ifndef DEBUG_MODE_HUE

  ++hue_index;

  switch(hue_index % N_HUE_LIGHTS - 1) {
    case 0:
        hue.hue(HUE_LIGHT_LIVING_ROOM_L, hueColours[random(0, N_HUE_LIGHTS)]);
        break;
    case 1:
        hue.hue(HUE_LIGHT_LIVING_ROOM_R, hueColours[random(0, N_HUE_LIGHTS)]);
        break;
    case 2:
        hue.hue(HUE_LIGHT_FIREPLACE, hueColours[random(0, N_HUE_LIGHTS)]);
        break;
    default:
        hue.hue(HUE_LIGHT_ARCO, hueColours[random(0, N_HUE_LIGHTS)]);
  }
    
#endif

}


void hueStopTheParty(){

  Serial.println("Hue: stopping the party.");
  hueTimer.stop();

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

  delay(100);

  hue.brightness(HUE_LIGHT_FIREPLACE, HUE_LIGHT_LIVING_ROOM_NORMAL_BRI);
  hue.sat(HUE_LIGHT_FIREPLACE, HUE_LIGHT_LIVING_ROOM_NORMAL_SAT);
  hue.hue(HUE_LIGHT_FIREPLACE, HUE_LIGHT_LIVING_ROOM_NORMAL_HUE);

  delay(100);

  hue.lightOff(HUE_LIGHT_PLUG);

#endif

}


void hueTimerCallback(){

  if(discoInferno) {
    randomiseHue(hue);
  }

}


#endif

