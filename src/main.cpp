#include <Arduino.h>
#include <RF24-STM.h>
#include <nRF24L01-STM.h>

#include <motor.hpp>

#define DIP1 PB12
#define DIP2 PB13
#define DIP3 PB14
#define DIP4 PB15
#define DIP5 PA8
#define DIP6 PB11
#define LED0 PC13
#define LED1 PB1
#define LED2 PB2

RF24 radio (PB0, PA4);
const uint64_t address = 0xF0F0F0F0E1LL;

void setup() {
  Serial1.begin(115200);
  Serial1.println ("----------init----------");
  pinMode (PA0, PWM);
  pinMode (PA1, PWM);
  pinMode (PA2, PWM);
  pinMode (PA3, PWM);
  analogWrite (PA0, 0);
  analogWrite (PA1, 0);
  analogWrite (PA2, 0);
  analogWrite (PA3, 0);
  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  radio.printDetails();
}

void loop() {
  digitalWrite (PC13, HIGH);
  analogWrite (PA0, 128);
  analogWrite (PA1, 0);
  Serial1.println("HIGH");
  delay (1000);
  digitalWrite (PC13, LOW);
  analogWrite (PA0, 0);
  analogWrite (PA1, 128);
  Serial1.println("LOW");
  delay (1000);
}