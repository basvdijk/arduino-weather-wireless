# arduino-weather-wireless
Wireless 433Mhz weather station using Arduino

## Files
* receiver.ino - source file for the receiver in Arduino
* transmitter.ino - source file for the transmitter in Arduino
* README.md - this file

## Video
todo

## Parts used

* [OLED sceen](http://www.ebay.com/itm/Yellow-Blue-0-96-IIC-I2C-128X64-OLED-LCD-Display-Module-Arduino-STM32-M45-/291216702333)
* [433Mhz sender/reveiver pair](www.ebay.com/itm/433Mhz-RF-transmitter-and-receiver-kit-for-Arduino-ARM-WL-MCU-Raspberry-pi-new-/370685120131)
* [2x breadboard](www.ebay.com/itm/Mini-Solderless-Breadboard-Bread-Board-400-Contacts-Available-Test-Develop-DIY-/171635895280)
* 1-wire temperature sensor
* [2x Arduino nano compatible](http://www.ebay.com/itm/MINI-USB-Nano-V3-0-ATmega328P-CH340G-5V-16M-Micro-controller-board-for-Arduino-/281626083826)
* [some wires](http://www.hobbyelectronica.nl/product/breadbord-jumper-wiresdraden/)

### Note on Arduino nano compatible
It turned out the Arduinos used a different type of serial converter. These need a driver to be installed on OSX. More info at http://kiguino.moos.io/2014/12/31/how-to-use-arduino-nano-mini-pro-with-CH340G-on-mac-osx-yosemite.html
