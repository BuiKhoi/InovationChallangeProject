#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

char StrBuff[200] = "";
const char myId[5] = "405";
int SysMode = 0;

//RFID + 11 12 13 - Verified
#define SS_PIN A3
#define RST_PIN A2
MFRC522 mfrc522(SS_PIN, RST_PIN);
char CardID[10];

//LCD - Verified
LiquidCrystal lcd(3, 4, 5, 8, 7, 6);

enum SystemMode {
  FREE = 0,
  SHOW_INFO,
  SHOW_DIRECTION,
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(20, 4);
  lcd.clear();
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

bool RoomNumberPrinted = false;

void PrintRoomNumber() {
  if (!RoomNumberPrinted) {
    lcd.clear();
    int length = strlen(myId);
    int pos = 20 - length;
    pos /= 2;
    lcd.setCursor(pos, 0);
    for (int i = 0; i < length; i++) {
      lcd.print(char(myId[i]));
    }
    RoomNumberPrinted = true;
  }
}

void SmartPrint(char* str, int row) {
  int lengths = strlen(str);
  for (int i = 0; i < 80; i++) {
    if (i == 0) {
      lcd.setCursor(0, row);
    } else if (i == 20) {
      lcd.setCursor(0, row + 1);
    } else if (i == 40) {
      lcd.setCursor(0, row + 2);
    } else if (i == 60) {
      lcd.setCursor(0, row + 3);
    }

    if (i < lengths) {
      lcd.print((char)str[i]);
    } else break;
  }
}

void ProcessDirection() {
  char temp[50];
  strcpy(temp, GetNextCommand());
  for (int z = 0; z < strlen(temp); z++) {
    Serial.print((char)temp[z]);
  }
  Serial.println();
  if (!strcmp(temp, "HRE")) {
    lcd.clear();
    lcd.setCursor(0, 0);
    SmartPrint("You have reach your destination", 0);
  } else {
    Route();
  }
}

char* GetNextCommand() {
  char rtr[50] = "";
  int i = 0;
  while (StrBuff[i] == '.' || StrBuff[i] == '<') {
    i++;
  }
  int j = 0;
  strcpy(rtr, "");
  while (StrBuff[i] != '#' && StrBuff[i] != '>') {
    rtr[j] = StrBuff[i];
    StrBuff[i] = '.';
    i++;
    j++;
  }
  StrBuff[i] = '.';
  return rtr;
}

void Route() {
  char des[5] = "";
  strcpy(des, GetNextCommand());
  char heading[40] = "Heading to: ";
  strcat(heading, des);
  //  for (int i=0; i<strlen(heading); i++) {
  //    Serial.print((char)heading[i]);
  //  }
  //  Serial.println();
  lcd.clear();
  SmartPrint(heading, 0);

  char rut[20] = "";
  char dir[80] = "";
  strcpy(rut, GetNextCommand());
  for (int i = 0; i < strlen(rut); i++) {
    strcat(dir, GetRoute(rut[i]));
    strcat(dir, " ");
  }
  //  for (int i=0; i<strlen(dir); i++) {
  //    Serial.print((char)dir[i]);
  //  }
  //  Serial.println();
  SmartPrint(dir, 1);
}

void GetCardID() {
  strcpy(CardID, "");
  for (byte i = 0; i < 4; i++) {
    int temp = mfrc522.uid.uidByte[i];
    char str_temp[4];
    strcpy(str_temp, "");
    str_temp[1] = GetChar(temp % 16);
    temp /= 16;
    str_temp[0] = GetChar(temp);
    CardID[2 * i] = str_temp[0];
    CardID[2 * i + 1] = str_temp[1];
  }
}

char GetChar(int index) {
  static char RtrCh[16] = "0123456789ABCDEF";
  return RtrCh[index];
}

char* GetRoute(char chr) {
  switch (chr) {
    case 'H': {
        return "Head";
      }
    case 'L': {
        return "left";
      }
    case 'R': {
        return "right";
      }
    case 'T': {
        return "to";
      }
    case 'E': {
        return "elevator";
      }
    case 'S': {
        return "stair";
      }
    case 'D': {
        return "destination";
      }
    case 'Y': {
        return "your";
      }
  }
}

bool RequestRoomDirection() {
  char request[200] = "<";
  strcat(request, CardID);
  strcat(request, "#");
  strcat(request, myId);
  strcat(request, ">");
  Serial.flush();
  Serial.println(request);
  lcd.setCursor(0, 2);
  lcd.print("Requesting data");
  return true;
}

void FreeMode() {
  PrintRoomNumber();
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      lcd.setCursor(0, 1);
      lcd.print("Card found");
      GetCardID();
      SysMode = SHOW_DIRECTION;
    } else return;
  } else return;
}

bool WaitMessage = false;;

void ShowDirection() {
  if (RequestRoomDirection()) {
    WaitSerial();
  }
}

void WaitSerial() {
  int i = 0;
  strcpy(StrBuff, "");
  int start = millis();
  while (true) {
    if (Serial.available()) {
      int temp;
      while ((temp=Serial.read())!='>') {
        Serial.print((char)temp);
        strcat(StrBuff, (char)temp);
        delay(3);
      }
      WaitMessage = false;
      break;
    }
  }
//  Serial.println(StrBuff);
  ProcessDirection();
  delay(5000);
  SysMode = FREE;
  RoomNumberPrinted = false;
}
