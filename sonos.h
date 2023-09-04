#define SONOS_DEBUG 1
#define ENABLE_SONOS 1
#define SONOS_URI_AIRHORN "//SynologyRouter/music/airhorn.mp3"
#define SONOS_URI_PARTY_TIME "//SynologyRouter/music/party-time.mp3"
#define SONOS_URI_PARTY_TIME_ERIC "//SynologyRouter/music/party-time-eric.mp3"
#define SONOS_URI_SHAKE_IT "//SynologyRouter/music/shake-it.mp3"
#define SONOS_URI_DISCO_PLAYLIST_ID 4
#define SONOS_PARTY_VOLUME 10
#define SONOS_SFX_VOLUME 10
#define SONOS_N_SFX 4

#ifdef SONOS_DEBUG
  IPAddress SONOS_DISCO_IP(10, 0, 4, 93); // office
  IPAddress SONOS_SFX_IP(10, 0, 4, 84); // move
  const char sonosDiscoID[]  = "7828CAEECD2C01400"; // office
  const char sonosSFXID[]    = "5CAAFDD4D0CC01400"; // move
#else
  IPAddress SONOS_DISCO_IP(10, 0, 4, 79); // livingroom
  IPAddress SONOS_SFX_IP(10, 0, 4, 84); // move
  const char sonosDiscoID[] = "48A6B801443301400"; // livingroom
  const char sonosSFXID[]    = "5CAAFDD4D0CC01400"; // move
#endif

String sfxArray[4] = {SONOS_URI_AIRHORN,SONOS_URI_PARTY_TIME,SONOS_URI_PARTY_TIME_ERIC,SONOS_URI_SHAKE_IT};


SonosUPnP sonos = SonosUPnP(wifi); 

void sonosSkipTrack() {
  
    Serial.println("Sonos: Skipping track");

    #ifdef ENABLE_SONOS
        sonos.skip(SONOS_DISCO_IP, SONOS_DIRECTION_FORWARD);
    #endif

}

void sonosPlayDubSiren() {
  
    #ifdef ENABLE_SONOS
      Serial.println("Sonos: dooo doo dooo dooooooooo");
      sonos.setPlayMode(SONOS_SFX_IP, 0);
      sonos.setVolume(SONOS_SFX_IP, SONOS_SFX_VOLUME);
      sonos.playFile(SONOS_SFX_IP, SONOS_URI_AIRHORN);
    #endif

}

void sonosStartTheParty(){
  
  Serial.println("Sonos: starting disco tunes...");

  #ifdef ENABLE_SONOS
    //SFX
    sonos.setVolume(SONOS_SFX_IP, SONOS_SFX_VOLUME);
    sonos.playFile(SONOS_SFX_IP, SONOS_URI_AIRHORN);

    // Disco tunes
    //sonos.disconnectFromMaster(SONOS_DISCO_IP);
    delay(100);
    sonos.stop(SONOS_DISCO_IP);
    //sonos.removeAllTracksFromQueue(SONOS_DISCO_IP);
    delay(100);
    sonos.addPlaylistToQueue(SONOS_DISCO_IP, SONOS_URI_DISCO_PLAYLIST_ID);
    delay(100);
    sonos.playQueue(SONOS_DISCO_IP, sonosDiscoID);
    //sonos.setPlayMode(SONOS_DISCO_IP, 3);
    Serial.println("Sonos: ...done");
  #endif


}

void sonosStopTheParty(){
  Serial.println("Sonos: stopping disco tunes");
  sonos.stop(SONOS_DISCO_IP);
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

