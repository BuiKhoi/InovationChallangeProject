#include <SoftwareSerial.h>
#include "E32-TTL-100.h"

#define M0_PIN  A4
#define M1_PIN  A5
#define AUX_PIN A6
#define SOFT_RX 9
#define SOFT_TX 10

SoftwareSerial softSerial(SOFT_RX, SOFT_TX);

void setup() {
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  softSerial.begin(9600);
  Serial.begin(9600);

  SwitchMode(MODE_0_NORMAL);
  WaitAUX_H();
  delay(10);
}

void loop() {
  uint8_t AddH = 0x02;
  uint8_t AddL = 0x01;
  uint8_t Mess[7] = "Hello!";
  SendMessage(AddH, AddL, Mess);
  delay(2000);
}

