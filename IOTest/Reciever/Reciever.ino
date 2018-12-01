#include <SoftwareSerial.h>
#include "E32-TTL-100.h"

#define M0_PIN  A1
#define M1_PIN  A0
#define AUX_PIN A2

SoftwareSerial softSerial(11, 10); // RX, TX

void setup() {
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  softSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println(SetAddress(0x08, 0x07));
  SwitchMode(MODE_0_NORMAL);
  WaitAUX_H();
  delay(10);
}

void loop() {
  uint8_t DataBuff[100], data_len = 0;
  ReceiveMsg();
}

