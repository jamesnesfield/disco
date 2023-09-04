#include "libs.h"

static bool discoInferno = false;
static bool lastInfernoState = false;
static bool skipTrack = false;
static bool dubSiren = false;

#include "secrets.h"

WiFiClient wifi;

#include "sonos.h"
#include "wifi.h"
#include "button.h"
#include "hue.h"

void setup() {

// start serial
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Serial started. ");

//start wifi
  connectToWiFi();
  delay(3000);

//Start Hue
  hue.begin(SECRET_HUE_USERNAME);
  setupHue();

// setup button
  button.begin();
  setupButton();

// timers and callbacks
  hueTimer.start();


    Serial.println("Setup finished, starting loop...");

}

void loop() {


  if(discoInferno && !lastInfernoState){
      Serial.println("=========== START THE PARTY! =============");
      hueStartTheParty();
      sonosStartTheParty();
      lastInfernoState = true;


  }else if(!discoInferno && lastInfernoState){
      hueStopTheParty();
      sonosStopTheParty();
      Serial.println("=========== STOP THE PARTY :( =============");
      lastInfernoState = false;

  }

  // buttons
  buttonUpdate();
  
  // sonos
  sonosUpdate();

  //hue
  hueTimer.update(); 

}



