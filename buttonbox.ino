/*******************************************************************
 *  A simple Macro keyboard built with Arduino Pro Micro
 *                                                                 
 *******************************************************************/

// ----------------------------
// Standard Libraries
// ----------------------------

#include <HID-Project.h>
#include <HID-Settings.h>
// https://github.com/NicoHood/HID

#include <SimpleRotary.h>
// https://github.com/mprograms/SimpleRotary/blob/master/src/SimpleRotary.h

#include <AceButton.h>
using namespace ace_button;
// https://github.com/bxparks/AceButton


// Button Pinout
const int RED_PIN = 4;
const int BLUE_PIN = 3;
const int GREEN_PIN = 5;
const int YELLOW_PIN = 2;
const int BLACK_PIN = 6;

const int LED_PIN =  17;      // the number of the LED pin (RXLED) on ProMicro

AceButton redButton(RED_PIN);
AceButton blueButton(BLUE_PIN);
AceButton greenButton(GREEN_PIN);
AceButton yellowButton(YELLOW_PIN);
AceButton blackButton(BLACK_PIN);

SimpleRotary rotary(20, 21, 19);

void handleEvent(AceButton*, uint8_t, uint8_t);

void setup() {
  Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);

  // initialize the pushbutton pins as an input:
  pinMode(RED_PIN, INPUT_PULLUP);
  pinMode(BLUE_PIN, INPUT_PULLUP);
  pinMode(GREEN_PIN, INPUT_PULLUP);
  pinMode(YELLOW_PIN, INPUT_PULLUP);
  pinMode(BLACK_PIN, INPUT_PULLUP);

  // init the event handlers
  redButton.setEventHandler(handleEvent);
  blueButton.setEventHandler(handleEvent);
  greenButton.setEventHandler(handleEvent);
  yellowButton.setEventHandler(handleEvent);
  blackButton.setEventHandler(handleEvent);
  
  // init media key support
  Consumer.begin();
}

void loop() {
  redButton.check();
  blueButton.check();
  greenButton.check();
  yellowButton.check();
  blackButton.check();

  switch (rotary.rotate()) {
    case 1: {
      Serial.println("CW - Volume Up");
      Consumer.write(MEDIA_VOLUME_UP);
      break;
    }
    case 2: {
      Serial.println("CCW - Volume Down");
      Consumer.write(MEDIA_VOLUME_DOWN);
      break;
    }
  }

  if (rotary.push() == 1) {
    Serial.println("Pushed");
    Consumer.write(MEDIA_VOLUME_DOWN);
  }
}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventPressed) {
    switch (button->getPin()) {
      case RED_PIN: {
        Serial.println("RED: Leave");
        break;
      }
      case BLUE_PIN: {
        Serial.println("BLUE: Camera");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_O);
        delay(100);
        Keyboard.releaseAll();
        break;
      }
      case GREEN_PIN: {
        Serial.println("GREEN: Hand");
        break;
      }
      case YELLOW_PIN: {
        Serial.println("YELLOW: Mute");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_M);
        delay(100);
        Keyboard.releaseAll();
        break;
      }
      case BLACK_PIN: {
        Serial.println("BLACK: Password");
        Keyboard.print("00Foo#1234567");
        break;
      }
    }
  } else {
    Serial.println(button->getPin());
    Serial.println(eventType);
    Serial.println(buttonState);
  }
}
