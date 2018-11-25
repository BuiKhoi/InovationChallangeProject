#include <E32_TTL_100_Lora.h>
#include <SoftwareSerial.h>

uint8_t StrBuff[200] = "";
uint8_t myId[5] = "F405";
bool ListeningMessage = false;
bool NewMessage = false;
int SysMode = 0;

#define MASTER_ADDH 0x02
#define MASTER_ADDL 0x01
#define MyAddH 0x06
#define MyAddL 0x05

#define Aux_interrupt 2
#define M0_PIN  7
#define M1_PIN  8
#define AUX_PIN A0
#define SOFT_RX 10
#define SOFT_TX 11

enum SystemMode {
  FREE = 0,
  SHOW_INFO,
  SHOW_DIRECTION,
};

SoftwareSerial LoraNode(SOFT_RX, SOFT_TX);

void setup() {
  Serial.begin(9600);
  LoraNode.begin(9600);
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);
  pinMode(Aux_interrupt, INPUT);
  ShowError(WaitHighAUX());
  SwitchMode(NORMAL);
  Serial.println("Slave started!");
}

void loop() {
  switch (SysMode) {
    case FREE: {
      FreeMode();
      break;
    }
    case SHOW_INFO: {
      ShowInfo();
      break;
    }
    case SHOW_DIRECTION: {
      ShowDirection();
      break;
    }
  }
}
