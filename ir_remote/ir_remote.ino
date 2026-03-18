/*
 ON / OFF
 2160016324
 18446744073709551615

 Brighter
 2160042334
 18446744073709551615

 Dimmer
 2160026014
 18446744073709551615
*/

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  irsend.sendNEC(2160016324);
  irsend.sendNEC(18446744073709551615);
  delay(2000);
}
