#include <E32_TTL_100_Lora.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

uint8_t StrBuff[200] = "";
const uint8_t myId[5] = "405";
bool ListeningMessage = false;
bool NewMessage = false;
int SysMode = 0;

//Address
#define MASTER_ADDH 0x08
#define MASTER_ADDL 0x07
#define MyAddH 0x02
#define MyAddL 0x01

//Encoder
#define EncoderA 2
#define EncoderB A1
#define EncoderButton A0

//RFID + 11 12 13 - Verified
#define SS_PIN A2
#define RST_PIN A3
MFRC522 mfrc522(SS_PIN, RST_PIN);
char CardID[10];

//LCD - Verified
LiquidCrystal lcd(3, 4, 5, 8, 7, 6);
byte arrow[8] = {
  0b10000,
  0b11000,
  0b11100,
  0b11110,
  0b11110,
  0b11100,
  0b11000,
  0b10000
};

//Lora
#define M0_PIN  A4
#define M1_PIN  A5
#define AUX_PIN A6
SoftwareSerial LoraNode(10, 9);

enum SystemMode {
  FREE = 0,
  SHOW_INFO,
  SHOW_DIRECTION,
};

int position = 0;

void setup() {
  Serial.begin(9600);
  //Lora init
  LoraNode.begin(9600);
  //  pinMode(M0_PIN, OUTPUT);
  //  pinMode(M1_PIN, OUTPUT);
  //  pinMode(AUX_PIN, INPUT);
  //  ShowError(WaitHighAUX());
  //  SwitchMode(NORMAL);
  //  SetAddress(MyAddH, MyAddL);

  //RFID init
  SPI.begin();
  mfrc522.PCD_Init();

  //Encoder init
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);
  pinMode(EncoderButton, INPUT);

  //LCD init
  lcd.begin(20, 4);
  lcd.clear();
  lcd.createChar(1, arrow);
}

void loop() {
  switch (SysMode) {
    case FREE: {
        FreeMode();
        break;
      }
    case SHOW_DIRECTION: {
        ShowDirection();
        break;
      }
  }
}
