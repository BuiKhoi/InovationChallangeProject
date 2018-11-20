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
  SetAddress(0x06, 0x05);
  SwitchMode(MODE_0_NORMAL);
  WaitAUX_H();
  delay(10);
}

void loop() {
  uint8_t DataBuff[100], data_len = 0;
  ReceiveMsg(DataBuff, &data_len);
}

