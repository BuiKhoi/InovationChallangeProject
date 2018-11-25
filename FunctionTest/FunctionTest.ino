#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <E32_TTL_100_Lora.h>

#define M0_PIN  7
#define M1_PIN  8
#define AUX_PIN A0
#define SOFT_RX 10
#define SOFT_TX 11

#define SDChipSelect 5
#define Aux_interrupt 2

uint8_t StrBuff[200] = "";
bool NewMessage = false;

SoftwareSerial LoraNode(SOFT_RX, SOFT_TX);

void setup() {
  Serial.begin(9600);
  LoraNode.begin(9600);
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

//  while (!SD.begin(SDChipSelect)) {
//    Serial.println("SD failed");
//    delay(100);
//  }
  ShowError(WaitHighAUX());
  SwitchMode(NORMAL);
  Serial.println("System started!");
}

void loop() {
  SendMessage(0x06, 0x05, "<Bui Quoc Khoi dep trai cute de thuong ahihi>");
  delay(1000);
}
