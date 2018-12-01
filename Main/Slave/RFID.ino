void GetCardID() {
  strcpy(CardID, "");
  for (byte i = 0; i < 4; i++) {
    int temp = mfrc522.uid.uidByte[i];
    Serial.print(temp, HEX);
//    uint8_t str_temp[2];
//    strcpy(str_temp, "");
//    str_temp[1] = GetChar(temp % 16);
//    temp /= 16;
//    str_temp[0] = GetChar(temp);
//    strcat(CardID, str_temp);
  }
  Serial.println();
}

