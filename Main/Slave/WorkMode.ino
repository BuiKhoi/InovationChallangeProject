void FreeMode() {
  PrintRoomNumber();
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()){
      lcd.setCursor(0, 1);
      lcd.print("Card found");
      GetCardID();
      SysMode = SHOW_DIRECTION;
    } else return;
  } else return;
}

void ShowInfo() {
  
}

void ShowDirection() {
  if (RequestRoomDirection()) {
    while (!NewMessage) {
      ReciveMessage();
    }
    ProcessDirection();
  } else return;
}
