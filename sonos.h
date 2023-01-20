
#include "wifi.h"
#include "./SonosUPnP.h"


SonosUPnP sonos = SonosUPnP(wifi); 


void sonosSkipTrack() {
  
    Serial.println("Sonos: Skipping track");

    #ifdef ENABLE_SONOS
      sonos.skip(g_sonosLivingrIP, SONOS_DIRECTION_FORWARD);
    #endif

}

void sonosPlayDubSiren() {
  
    Serial.println("Sonos: dooo doo dooo dooooooooo");

    #ifdef ENABLE_SONOS
      sonos.skip(g_sonosLivingrIP, SONOS_DIRECTION_FORWARD);
    #endif

}

void sonosUpdate(){

  if(skipTrack) {
    sonosSkipTrack();
    skipTrack = false;
  }

  if(dubSiren) {
    sonosPlayDubSiren();
    dubSiren = false;
  }

}

