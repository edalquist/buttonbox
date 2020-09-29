/*******************************************************************
 *  A simple Macro keyboard built with Arduino Pro Micro
 *  https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/hardware-overview-pro-micro
 *
 * MIT License
 *
 * Copyright (c) 2020 Eric B Dalquist
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************/

// https://github.com/NicoHood/HID
#include <HID-Project.h>
#include <HID-Settings.h>

// https://github.com/mprograms/SimpleRotary/blob/master/src/SimpleRotary.h
#include <SimpleRotary.h>

// https://github.com/bxparks/AceButton
#include <AceButton.h>
using namespace ace_button;


// Button Pinout
const int RED_PIN = 4;
const int BLUE_PIN = 3;
const int GREEN_PIN = 5;
const int YELLOW_PIN = 2;
const int BLACK_PIN = 6;

// ProMicro onboard LED pin (RXLED)
const int LED_PIN =  17;

// Create AceButton wrappers
AceButton redButton(RED_PIN);
AceButton blueButton(BLUE_PIN);
AceButton greenButton(GREEN_PIN);
AceButton yellowButton(YELLOW_PIN);
AceButton blackButton(BLACK_PIN);

// Create Rotary Switch wrapper
const int ROATARY_A_PIN = 20; // A2
const int ROATARY_B_PIN = 21; // A3
const int ROATARY_S_PIN = 19; // A1
SimpleRotary rotary(ROATARY_A_PIN, ROATARY_B_PIN, ROATARY_S_PIN);

// AceButton event handler
void handleEvent(AceButton*, uint8_t, uint8_t);

void setup() {
  Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);

  // initialize the pushbutton pins as an input with onboard pullup:
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
    Consumer.write(MEDIA_VOLUME_MUTE);
  }
}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventPressed) {
    switch (button->getPin()) {
      case RED_PIN: {
        Serial.println("RED: Leave");
        // TODO MS Team's doesn't have a leave shortcut yet :(
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
        // TODO MS Team's doesn't have a raise-hand shortcut yet :(
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
        Keyboard.print("XXStu#XXXXXXX");
        break;
      }
    }
  } else {
    Serial.println("Unknown Button: ");
    Serial.println(button->getPin());
    Serial.println(eventType);
    Serial.println(buttonState);
  }
}
