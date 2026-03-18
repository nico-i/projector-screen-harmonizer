#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
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

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  mySwitch.enableTransmit(4);  // Using Pin D3 on (GPIO 4)
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(1);

  // Optional set pulse length.
  // mySwitch.setPulseLength(315);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(3);
}

void loop() {
  mySwitch.send(2160016324, 24);
  delay(3000);  
}
