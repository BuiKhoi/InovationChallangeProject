#include <SoftwareSerial.h>
#include "E32-TTL-100.h"

#define M0_PIN  7
#define M1_PIN  8
#define AUX_PIN A0
#define SOFT_RX 10
#define SOFT_TX 11

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
  uint8_t AddH = 0x06;
  uint8_t AddL = 0x05;
  uint8_t Mess[7] = "Hello!";
  SendMessage(AddH, AddL, Mess);
  delay(2000);
}

