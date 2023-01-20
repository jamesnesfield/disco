#ifndef DISCO_BUTTON
#define DISCO_BUTTON

#include <EasyButton.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 8
#define DOUBLE_PRESS_DELAY 350
#define LONG_PRESS_DELAY 1000

void buttonTimerCallback();

// Instance of the button.
EasyButton button(BUTTON_PIN);
Ticker buttonTimer(buttonTimerCallback, DOUBLE_PRESS_DELAY, 1); // changing led every 500ms

// callbacks
void buttonPressed();
void buttonDoublePressed();
void buttonLongPressed();

void setupButton(){
    button.onPressed(buttonPressed);
    button.onPressedFor(LONG_PRESS_DELAY, buttonLongPressed);
    //button.onSequence(2 /* number of presses */, 2000 /* timeout */, buttonDoublePressed /* callback */);
}

// Callback function to be called when the button is pressed.
void buttonPressed() {

  Serial.println("Button: pressed");

  if(buttonTimer.state() == RUNNING) { // second press detected within DOUBLE_PRESS_DELAY
    Serial.print("time elapsed :");
    Serial.println(buttonTimer.elapsed()/1000);
    buttonDoublePressed();
    buttonTimer.stop();
  } else {
    buttonTimer.start(); // start waiting for double press
  }

}


void buttonTimerCallback(){
    Serial.println("Button: timer end reached");
    if(discoInferno){ 
      Serial.println("Button: - neeeexxxxt!!!");
      skipTrack =true; 
    } else {
      discoInferno = true; // start the disco
    }
}

void buttonUpdate(){
    digitalWrite(LED_BUILTIN, !digitalRead(8));
    button.read();
    buttonTimer.update();
}

// Callback function to be called when the button is long pressed.
void buttonLongPressed()
{
  Serial.println("Button: long-pressed");
  if(discoInferno) {
    Serial.println("Button:........... back to reality :)");
    discoInferno = false;
  }
}

// Function called when the button is double pressed.
void buttonDoublePressed()
{
  // allow a dub siren whether there is a party on or not :)
  Serial.println("Button: double-pressed");
  Serial.println("Button: - duuuuub siiiirrrreeeennnn....");
  dubSiren = true;
}

#endif