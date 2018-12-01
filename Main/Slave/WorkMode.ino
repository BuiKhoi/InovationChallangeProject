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

void ShowInfo() {

}

void ShowDirection() {
  if (RequestRoomDirection()) {
    WaitSerial();
  } else return;
}

void WaitSerial() {
  int i = 0;
  strcpy(StrBuff, "");
  Serial.flush();
  while (!Serial.available()) {};
  while (Serial.available()) {
    StrBuff[i++] = Serial.read();
  }
  ProcessDirection();
  delay(5000);
  SysMode = FREE;
  RoomNumberPrinted = false;
}

