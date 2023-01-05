#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WiFiNINA.h>  // JV : Wireless Mkr1010
#include <WiFiUdp.h>   // JV : UDP service
#include "./include/hueDino-master/src/hueDino.h"
#include "./include/microxpath-master/src/MicroXPath.h"
#include "./include/microxpath-master/src/MicroXPath_P.h"
#include "./include/Sonos-ESP32-master/src/SonosUPnP.h"


// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // put your setup code here, to run once:
  char ssid[] = "test";

}

void loop() {
  // put your main code here, to run repeatedly:

}
