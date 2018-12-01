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

void SmartPrint(uint8_t* str, int row) {
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

