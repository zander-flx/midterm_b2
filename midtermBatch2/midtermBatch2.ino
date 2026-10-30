//GPIO Pins
const byte IR_IN = 36; //IR for detection
const byte SW1 = 13; //Switch 1
const byte SW2 = 2; //Switch 2
const uint8_t LED_1[] = {32, 33, 25, 26, 27, 14, 12};
const uint8_t NUM0 = sizeof(LED_1) / sizeof(LED_1[0]);

const uint8_t LED_2[] = {19, 18, 5, 17, 16, 4, 0};
const uint8_t NUM1 = sizeof(LED_2) / sizeof(LED_2[0]);

//Variables
int currentState = 0;
int sw1 = 0;
int sw2 = 0;
int previousState = 0;
uint8_t count = 0;

#include "Decoder.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_IN, INPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);

  for (int i = 0; i < NUM0; i++) {
    pinMode(LED_1[i], OUTPUT);
  }

  for (int i = 0; i < NUM1; i++) {
    pinMode(LED_2[i], OUTPUT);
  }

  //Initialize count 0
  decoder(count);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(IR_IN);
  sw1 = digitalRead(SW1);
  sw2 = digitalRead(SW2);

  if(currentState == 1 && previousState == 0){
    if(sw1 == 0 && sw2 == 0){
      count = (count + 1) % 100;
    } else if(sw1 == 0 && sw2 == 1 && count > 0){ //extra condition ensures there's no negative numbers
      count = (count - 1) % 100;
    } else if(sw1 == 1 && sw2 == 0){
      count = (count + 2) % 100;
    } else if(sw1 == 1 && sw2 == 1 && count > 1){ //again, to ensure there's no negative numbers
      count = (count - 2) % 100;
    }
  }

  decoder(count);

  previousState = currentState;

  delay(50);
}
