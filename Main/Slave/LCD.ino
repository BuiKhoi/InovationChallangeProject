void PrintRoomNumber() {
  int length = strlen(myId);
  int pos = 20 - length;
  pos /= 2;
  lcd.setCursor(pos, 0);
  for (int i = 0; i < length; i++) {
    lcd.print(char(myId[i]));
  }
}

void SmartPrint(uint8_t* str) {
  int lengths = strlen(str);
  for (int i=0; i<80; i++) {
    if (i==0) {
      lcd.setCursor(0, 0);
    } else if (i==20) {
      lcd.setCursor(1, 0);
    } else if (i==40) {
      lcd.setCursor(2, 0);
    } else if (i==60) {
      lcd.setCursor(3, 0);
    }
    
    if (i<lengths) {
      lcd.print(str[i]);
    } else break;
  }
}

