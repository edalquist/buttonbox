# Simple Button Box

Button box for executing keyboard shortcuts and controlling volume. Makes my kids remote-learning life on
video calls much easier. The sketch is setup for MS Teams to control Mute and Camera, volume, and to enter
their password (I know this isn't secure, it is just their school account).

## Parts List

What I used to put these together. You'll also need a soldering iron and a way to drill out the button holes.

* SparkFun Pro Micro - https://www.amazon.com/gp/product/B01B26MAR6
* Push Button Rotary Encoder - https://www.amazon.com/gp/product/B08BFJ4F5C
* Momentary Buttons - https://www.amazon.com/gp/product/B07F24Y1TB
* Project Box - https://www.amazon.com/gp/product/B073Y7FW1Q
* Ribbon Cable Kit - https://www.amazon.com/dp/B07CVYPDGS
* Right Angle Headers - https://www.amazon.com/gp/product/B07C89T16T

## Assembly

I didn't do a great job with photos, hopefully the assembly is pretty self explanitory

1. Drill holes in the project box for the 5 buttons, 1 rotary encoder, and micro usb plug
1. Insert and wire the buttons: ![Wire Buttons 1](https://imgur.com/H3OsSWE.jpg)
1. Crimp ribbon cables and wire to Pro Micro: ![Wire Buttons 2](https://imgur.com/Q9iOJWI.jpg)
1. Assembled: ![Assembled](https://imgur.com/5ZsChbr.jpg)

Wiring
* The buttons and rotary switch are all wired off the GND pin adjacant to Pin 2.
* The buttons are wired to pins 2-6.
* The A/B pins of the rotary encoder are wired to A2 & A3, the push button of the encoder is wired to A1.

## Flashing

These instructions are for use with the Ardunio IDE

1. Install [Pro Micro Board Addon](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide#windows_boardaddon)
1. **Select The Right Pro Micro Voltage!** Either 3.3v or 5v, incorrect selections make reflashing hard.
1. Install the libraries linked from the sketch
1. Update shortcuts, passwords, etc.
