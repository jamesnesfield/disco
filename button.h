#ifndef DISCO_BUTTON
#define DISCO_BUTTON

#include <EasyButton.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 8

// Instance of the button.
EasyButton button(BUTTON_PIN);

// callbacks
void buttonPressed();
void buttonDoublePressed();
void buttonLongPressed();

void setupButton(){

    button.onPressed(buttonPressed);
    button.onPressedFor(1000, buttonLongPressed);
    button.onSequence(2 /* number of presses */, 2000 /* timeout */, buttonDoublePressed /* callback */);

}

// Callback function to be called when the button is pressed.
void buttonPressed()
{
  Serial.println("Button pressed");
  if(!discoInferno){
    discoInferno = true;
  } else {
    skipTrack =true;
  }
}

// Callback function to be called when the button is long pressed.
void buttonLongPressed()
{
  Serial.println("Button long-pressed");
  discoInferno = false;
}

// Callback function to be called when the button is double pressed.
void buttonDoublePressed()
{
  Serial.println("Button double-pressed");
  dubSiren = true;

}

#endif