/*

Author:      Bas van Dijk
Date:        21 May 2015
Description: Wireless 433Mhz Arduino weather station with OLED screen (TRANSMITTER)


1 Wire temperature sensor pins:

  VCC -> 5V
  DATA -> D4
  GND -> GND

433Mhz transmitter pins (has two of the same data pins):

  ATAD -> D3
  VCC -> 5V
  GND -> GND
  
*/


#include <VirtualWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#undef int
#undef abs
#undef double
#undef float
#undef round

// arrays to hold device address: 28A3E6E005000021
uint8_t insideThermometer[8] =  { 0x28, 0xA3, 0xE6, 0xE0, 0x05, 0x00, 0x00, 0x21 };

void setup()
{
    vw_set_ptt_inverted(true);     // Required for RF Link module
    vw_setup(2000);                // Bits per sec
    vw_set_tx_pin(3);              // pin 3 is used as the transmit data out into the TX Link module, change this as per your needs
    
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}


void loop()
{
  // Update all sensor values
  sensors.requestTemperatures();
  
  // Get the temperature of our 1-wire thermometer
  float tempC = sensors.getTempC(insideThermometer);
  
  char charVal[5]; 
  
  // Convert the temperature (which is a float) into an ASCII characte representation
  // syntax dtostrf(value, with, precision, target);
  dtostrf(tempC, 4, 2, charVal);

  // round temperature to 0.5 degree Celsius
  int tempInteger = (int)tempC;
  float tempFractionAsFloat = tempC - tempInteger;
  int tempFractionAsInteger = tempFractionAsFloat * 100;
  
  char msg[24];
  sprintf(msg, "%i.%i", tempInteger, tempFractionAsInteger);
  Serial.print(msg);

  digitalWrite(13, HIGH); 
  
  vw_send((uint8_t *)msg, strlen(msg));

  digitalWrite(13, LOW); 

  vw_wait_tx();  // Wait for message to finish
  delay(2000);
}


