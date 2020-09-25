/*******************************************************************
 *  A simple Macro keyboard built with Arduino Pro Micro and a        
 *  4*4 Button Matrix.
 *  
 *  Parts:
 *  Arduino Pro Micro* - http://s.click.aliexpress.com/e/FQmMd5uc 
 *  4*4 Keypad Button Matrix* - http://s.click.aliexpress.com/e/CqnjTgGg 
 *  
 *  * = Affilate
 *                                                                 
 *  Written by Brian Lough
 *  YouTube: https://www.youtube.com/brianlough
 *  Tindie: https://www.tindie.com/stores/brianlough/
 *  Twitter: https://twitter.com/witnessmenow                                 
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

/**
 * right side
 *   gnd
 *   rst - n/c
 *   vcc
 *   A2 - re up
 *   A3 - re down
 *   A4 - re button
 * left side
 *   gnd
 *   2 - btn
 *   3 - btn
 *   4 - btn
 *   5 - btn
 *   6 - btn
 */

// Button Pinout
const int RED_PIN = 4;
const int BLUE_PIN = 3;
const int GREEN_PIN = 5;
const int YELLOW_PIN = 2;
const int BLACK_PIN = 6;

const int ledPin =  17;      // the number of the LED pin (RXLED)

AceButton redButton(RED_PIN);
AceButton blueButton(BLUE_PIN);
AceButton greenButton(GREEN_PIN);
AceButton yellowButton(YELLOW_PIN);
AceButton blackButton(BLACK_PIN);

SimpleRotary rotary(21, 20, 19);

void handleEvent(AceButton*, uint8_t, uint8_t);
void sendMacroCommand(uint8_t key);

void setup() {
  Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the pushbutton pins as an input:
  pinMode(RED_PIN, INPUT_PULLUP);
  pinMode(BLUE_PIN, INPUT_PULLUP);
  pinMode(GREEN_PIN, INPUT_PULLUP);
  pinMode(YELLOW_PIN, INPUT_PULLUP);
  pinMode(BLACK_PIN, INPUT_PULLUP);

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
  
//  int prevState = buttonState; u
//  // read the state of the pushbutton value:
//  buttonState = digitalRead(buttonPin);
//  if (prevState != buttonState) {
//    Serial.println(buttonState);
//  
//    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//    if (buttonState == 1) {
//      Serial.println("down");
//      // turn LED on:
//      digitalWrite(ledPin, LOW);
////      Keyboard.write('A');
//      sendMacroCommand('m');
//      delay(100);
//      Keyboard.releaseAll(); // this releases the buttons
//    } else {
//      Serial.println("up");
//      // turn LED off:
//      digitalWrite(ledPin, HIGH);
//    }
//  }

  auto i = rotary.rotate();
  if ( i == 1 ) {
    Serial.println("CW");
//     Consumer.write(MEDIA_VOLUME_UP);
  }
  if ( i == 2 ) {
    Serial.println("CCW");
//     Consumer.write(MEDIA_VOLUME_DOWN);
  }

  // TODO
  i = rotary.push();
  if ( i == 1 ) {
    Serial.println("Pushed");
  }
}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println(button->getPin());
  Serial.println(eventType);
  Serial.println(buttonState);
  switch (eventType) {
    case AceButton::kEventPressed:
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case AceButton::kEventReleased:
      digitalWrite(LED_BUILTIN, HIGH);
      break;
  }
}

// This will hold down all the following buttons.
void sendMacroCommand(uint8_t key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
//  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}
