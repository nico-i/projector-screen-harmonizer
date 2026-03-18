#include <RCSwitch.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>

// Projector Screen RF Codes
#define RF_SCREEN_UP 6865298
#define RF_SCREEN_DOWN 6865300
#define RF_SCREEN_STOP 6865304

// Living Room Lamp IR Codes
#define LAMP_TOGGLE 2160016324
#define LAMP_BRIGHTER 2160042334
#define LAMP_DIMMER 2160026014
#define LAMP_CHECK 18446744073709551615

// Harmony IR Codes
// Screen
#define IR_SCREEN_UP 3841
#define IR_SCREEN_DOWN 3844
// Magic Lighting Light Controller
#define MLL_ON 16769055
#define MLL_OFF 16736415
#define MLL_DIMMER 16720095
#define MLL_BRIGHTER 16752735

// Pins
#define IR_REC 14 // GPIO Pin 14 := D5 on ESP8226
#define IR_SEND 4 // GPIO Pin 4 := D2 on ESP8226
 
RCSwitch mySwitch = RCSwitch();
IRsend irsend(IR_SEND);
IRrecv irrecv(IR_REC, 1024, 50, false);
decode_results results;
bool isLivingRoomLampOn = true;

void setup() {
  irrecv.enableIRIn();  // Start IR receiver
  irsend.begin(); // Start IR transmitter
  Serial.begin(115200, SERIAL_8N1);
  mySwitch.enableTransmit(0); // Enable RF transmission over ESP8226 Pin D3 (:= GPIO Pin 10)
  mySwitch.setPulseLength(315); // Optional set pulse length.
  mySwitch.setRepeatTransmit(3);   // Optional set number of transmission repetitions.
}

void loop() {
  if(irrecv.decode(&results)){
    uint64_t input = results.value;
    Serial.print("Recieved value: ");
    Serial.println(input);
    switch(input) {
      case IR_SCREEN_DOWN:
        Serial.println("Screen down.");
        mySwitch.send(RF_SCREEN_DOWN, 24);
        break;
      case IR_SCREEN_UP:
        Serial.println("Screen up.");
        mySwitch.send(RF_SCREEN_UP, 24);
        break;
      case MLL_OFF:
        if(!isLivingRoomLampOn) {
          Serial.println("Light on.");
          irsend.sendNEC(LAMP_TOGGLE);
          isLivingRoomLampOn = true;
        }
        break;
      case MLL_ON:
        if(isLivingRoomLampOn) {
          Serial.println("Light off.");
          irsend.sendNEC(LAMP_TOGGLE);
          isLivingRoomLampOn = false;
        }
        break;
      case MLL_DIMMER:
        Serial.println("Dim light.");
        irsend.sendNEC(LAMP_DIMMER);
        break;
      case MLL_BRIGHTER:
        Serial.println("Brighten light.");
        irsend.sendNEC(LAMP_BRIGHTER);
        break;
  }
  irsend.sendNEC(LAMP_CHECK);
  irrecv.resume();  // Receive the next value
  }
}
