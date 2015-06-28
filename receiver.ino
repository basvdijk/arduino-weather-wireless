/*

Author:      Bas van Dijk
Date:        21 May 2015
Description: Wireless 433Mhz Arduino weather station with OLED screen (RECEIVER)

Display used: http://www.hobbyelectronica.nl/product/128x64-oled-geel-blauw-i2c/
Determine display type: https://code.google.com/p/u8glib/wiki/gallery

OLED pins:

  VCC -> 5V
  GND -> GND
  SCL -> A5
  SDA -> A4
  

433Mhz receiver pins (has two of the same data pins):

  VCC -> 5V
  GND -> GND
  Data -> D4

*/


#undef int
#undef abs
#undef double
#undef float
#undef round

#include <VirtualWire.h>    // you must download and install the VirtualWire.h to your hardware/libraries folder

#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send AC


// Bitmap of temperature icon
#define temperature_width 18
#define temperature_height 47
static unsigned char temperature_bits[] U8G_PROGMEM = {
   0xc0, 0x0f, 0x00, 0xe0, 0x1f, 0x00, 0x70, 0x38, 0x00, 0x30, 0x30, 0x00,
   0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,
   0x30, 0x30, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x98, 0x67, 0x00, 0x8c, 0xc7, 0x00,
   0xc6, 0x8f, 0x01, 0xe2, 0x1f, 0x01, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03,
   0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03,
   0xf3, 0x3f, 0x03, 0xe6, 0x9f, 0x01, 0xc6, 0x8f, 0x01, 0x0c, 0xc0, 0x00,
   0x38, 0x70, 0x00, 0xf0, 0x3f, 0x00, 0xc0, 0x0f, 0x00 };


void setup()
{
    Serial.begin(9600);    
    
    // flip screen, if required
    //u8g.setRot180();

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true);    // Required for RX Link Module
    vw_setup(2000);               // Bits per sec
    vw_set_rx_pin(4);             // We will be receiving on pin 4 i.e the RX pin from the module connects to this pin. 
    vw_rx_start();                // Start the receiver 
    
    // Onboard LED
    pinMode(13, OUTPUT);
    
}


uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
char* message = (char*)buf;

bool blinker = true;

void loop() {
  
    if (vw_get_message(buf, &buflen)) { // check to see if anything has been received
      Serial.println(message);
      blinker = !blinker;
    }
     
    u8g.firstPage();
    
    do {
      
      u8g.setFont(u8g_font_unifont);
      u8g.setPrintPos(0, 10); 
      u8g.print("TEMPERATURE");
      
      if (blinker) {
        u8g.setPrintPos(120, 6);
        u8g.print(".");
        digitalWrite(13, HIGH);  
      } else {
        digitalWrite(13, LOW);  
      }

      
      u8g.setPrintPos(0, 50); 
      u8g.setFont(u8g_font_fub25r);
      
      // Check if message is empty
      if (message && message[0] == '\0') {
        u8g.print("??.??");
      } else {
        u8g.print(message);
      }
      
      u8g.drawXBMP(100, 16, temperature_width, temperature_height, temperature_bits);
  
    } while(u8g.nextPage());
}
