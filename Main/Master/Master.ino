#include <E32_TTL_100_Lora.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

uint8_t StrBuff[200] = "";
bool ListeningMessage = false;
bool NewMessage = false;

#define MyAddH 0x02
#define MyAddL 0x01

LiquidCrystal lcd(3, 4, 5, 8, 7, 6);

#define M0_PIN  9
#define M1_PIN  10
#define AUX_PIN A0
SoftwareSerial LoraNode(13, 15);

void setup() {
  Serial.begin(9600);
  //Lora init
  LoraNode.begin(9600);
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);
  ShowError(WaitHighAUX());
  SwitchMode(NORMAL);
  SetAddress(MyAddH, MyAddL);

  //LCD init
  lcd.begin(20, 4);
  lcd.clear();
  
  Serial.println("Master started!");
}

void loop() {
  ReciveMessage();
  if (NewMessage) {
    
  }
}
