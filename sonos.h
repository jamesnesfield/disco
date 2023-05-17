//#define SONOS_DEBUG 1
#define ENABLE_SONOS 1
#define SONOS_URI_AIRHORN "//SynologyRouter/music/airhorn.mp3"
#define SONOS_URI_DISCO_PLAYLIST_ID 4
#define SONOS_PARTY_VOLUME 50
#define SONOS_SFX_VOLUME 50

IPAddress SONOS_OFFICE_IP(10, 0, 4, 93);
IPAddress SONOS_BEDROOM_IP(10, 0, 4, 92);
IPAddress SONOS_LIVINGROOM_IP(10, 0, 4, 79);
IPAddress SONOS_MOVE_IP(10, 0, 4, 84);


const char sonosLivingrID[] = "48A6B801443301400";
const char sonosMoveID[] = "5CAAFDD4D0CC01400";
const char sonosOfficeID[] = "7828CAEECD2C01400";
const char sonosBedroomID[] = "949F3E51888201400";


SonosUPnP sonos = SonosUPnP(wifi); 


void sonosClearQueue() {
}

void sonosSkipTrack() {
  
    Serial.println("Sonos: Skipping track");

    #ifdef ENABLE_SONOS
      #ifdef SONOS_DEBUG
        sonos.skip(SONOS_OFFICE_IP, SONOS_DIRECTION_FORWARD);
      #else
        sonos.skip(SONOS_LIVINGROOM_IP, SONOS_DIRECTION_FORWARD);
      #endif
    #endif

}

void sonosPlayDubSiren() {
  
    #ifdef ENABLE_SONOS
      Serial.println("Sonos: dooo doo dooo dooooooooo");
      #ifdef SONOS_DEBUG
        sonos.setPlayMode(SONOS_MOVE_IP, 0);
        sonos.setVolume(SONOS_MOVE_IP, SONOS_SFX_VOLUME);
        sonos.playFile(SONOS_MOVE_IP, SONOS_URI_AIRHORN);
      #else
        sonos.setPlayMode(SONOS_MOVE_IP, 0);
        sonos.setVolume(SONOS_MOVE_IP, SONOS_SFX_VOLUME);
        sonos.playFile(SONOS_MOVE_IP, SONOS_URI_AIRHORN);
      #endif
    #endif

}

void sonosStartTheParty(){
  
  Serial.println("Sonos: starting disco tunes...");

  sonosPlayDubSiren();

  #ifdef SONOS_DEBUG
    Serial.println("(in debug)");
    sonos.disconnectFromMaster(SONOS_OFFICE_IP);
    sonos.removeAllTracksFromQueue(SONOS_OFFICE_IP);
    sonos.addPlaylistToQueue(SONOS_OFFICE_IP, SONOS_URI_DISCO_PLAYLIST_ID);
    sonos.playQueue(SONOS_OFFICE_IP, sonosOfficeID);
    sonos.setPlayMode(SONOS_OFFICE_IP, 3);
  #else
    sonos.stop(SONOS_LIVINGROOM_IP);

    sonos.removeAllTracksFromQueue(SONOS_LIVINGROOM_IP);
    Serial.println("..cleared queue");
    sonos.addPlaylistToQueue(SONOS_LIVINGROOM_IP, SONOS_URI_DISCO_PLAYLIST_ID);
    Serial.println("..playing queue");
    sonos.playQueue(SONOS_LIVINGROOM_IP, sonosLivingrID);
    sonos.setPlayMode(SONOS_LIVINGROOM_IP, 3);
    sonos.setVolume(SONOS_LIVINGROOM_IP, SONOS_PARTY_VOLUME);
    // sonos.disconnectFromMaster(SONOS_MOVE_IP);
    // sonos.disconnectFromMaster(SONOS_LIVINGROOM_IP);
    Serial.println("..disconnected masters and set play mode");

  #endif

  Serial.println("Sonos: ...done");

}

void sonosStopTheParty(){
  Serial.println("Sonos: stopping disco tunes");
  #ifdef SONOS_DEBUG
    sonos.stop(SONOS_OFFICE_IP);
  #else
    sonos.stop(SONOS_LIVINGROOM_IP);
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

