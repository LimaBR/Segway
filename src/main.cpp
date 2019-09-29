#include <Arduino.h>
#include <MapleFreeRTOS.h>

#include <RF24-STM.h>
#include <nRF24L01-STM.h>

#define DIP1 PB12
#define DIP2 PB13
#define DIP3 PB14
#define DIP4 PB15
#define DIP5 PA8
#define DIP6 PB11
#define LED0 PC13
#define LED1 PB1
#define LED2 PB10

//RF24 radio (PB0, PA4);
const uint64_t address = 0xF0F0F0F0E1LL;

static void task0( void* pvParameters){
  while(true){
    digitalWrite (LED1, HIGH);
    vTaskDelay (500);
    digitalWrite (LED1, LOW);
    vTaskDelay (500);
  }
}

static void task1( void* pvParameters){
  while(true){
    digitalWrite (LED2, HIGH);
    vTaskDelay (1000);
    digitalWrite (LED2, LOW);
    vTaskDelay (1000);
  }
}

static void motorTask( void* pvParameters){
  while(true){
    analogWrite(PA2, 0);
    for(uint16 i=0; i<255; i++){
      analogWrite(PA3, i);
      vTaskDelay (5);
    }
    for(uint16 i=255; i>0; i--){
      analogWrite(PA3, i);
      vTaskDelay (5);
    }
    analogWrite(PA3, 0);
    for(uint16 i=0; i<255; i++){
      analogWrite(PA2, i);
      vTaskDelay (5);
    }
    for(uint16 i=255; i>0; i--){
      analogWrite(PA2, i);
      vTaskDelay (5);
    }
  }
}

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
  xTaskCreate(
    task0,
    (signed char*)"LED",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL
    );
  xTaskCreate(
    task1,
    (signed char*)"LED02",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL
    );
  xTaskCreate(
    motorTask,
    (signed char*)"motorTask",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL
    );
  vTaskStartScheduler();
}

void loop() {

}

