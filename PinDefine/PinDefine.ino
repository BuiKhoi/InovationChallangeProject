#include <SoftwareSerial.h>
#include <E32_TTL_100_Lora.h>

//Encoder
#define EncoderA 2
#define EncoderB A0
#define EncoderButton A1

//RFID + 11 12 13
#define SS_PIN A2
#define RST_PIN A3
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

//LCD
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
SoftwareSerial LoraNode(SOFT_RX, SOFT_TX);

//Lora
#define M0_PIN  A4
#define M1_PIN  A5
#define AUX_PIN A6
#define SOFT_RX 9
#define SOFT_TX 10

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
