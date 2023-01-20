#include "libs.h"

static bool discoInferno = false;
static bool skipTrack = false;
static bool dubSiren = false;

#include "secrets.h"
#include "wifi.h"
#include "hue.h"
#include "sonos.h"
#include "button.h"


//#define ENABLE_HUE 1
//#define ENABLE_SONOS 1

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
}

void loop() {

  // buttons
  buttonUpdate();
  
  // sonos
  sonosUpdate();

  //hue
  hueTimer.update(); 

}



