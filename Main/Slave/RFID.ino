void GetCardID() {
  strcpy(CardID, "");
  for (byte i = 0; i < 4; i++) {
    int temp = mfrc522.uid.uidByte[i];
    char str_temp[4];
    strcpy(str_temp, "");
    str_temp[1] = GetChar(temp % 16);
    temp /= 16;
    str_temp[0] = GetChar(temp);
    CardID[2*i] = str_temp[0];
    CardID[2*i+1] = str_temp[1];
  }
  for (int i=0; i<8; i++) {
    Serial.print(CardID[i]);
  }
  Serial.println();
}

