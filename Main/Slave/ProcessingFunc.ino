void ProcessDirection() {
  uint8_t temp[50];
  strcpy(temp, GetNextCommand());
  for (int z = 0; z < strlen(temp); z++) {
    Serial.print((char)temp[z]);
  }
  Serial.println();
  if (!strcmp(temp, "DIR")) {
    Route();
  } else if (!strcmp(temp, "HRE")) {
    Serial.println("You are here");
    lcd.clear();
    lcd.setCursor(0, 0);
    SmartPrint("You have reach your destination", 0);
  } else {
    Serial.println("Not included");
    lcd.clear();
    lcd.setCursor(0, 0);
    SmartPrint("Command not included", 0);
  }
}

uint8_t* GetNextCommand() {
  uint8_t rtr[50] = "";
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
  for (int i=0; i<strlen(StrBuff); i++) {
    Serial.print((char)StrBuff[i]);
  }
  Serial.println();
  return rtr;
}

void Route() {
  uint8_t des[5] = "";
  strcpy(des, GetNextCommand());
  uint8_t heading[40] = "Heading to: ";
  strcat(heading, des);
  for (int i=0; i<strlen(heading); i++) {
    Serial.print((char)heading[i]);
  }
  Serial.println();
  lcd.clear();
  SmartPrint(heading, 0);

  uint8_t rut[20] = "";
  uint8_t dir[80] = "";
  strcpy(rut, GetNextCommand());
  for (int i=0; i<strlen(rut); i++) {
    strcat(dir, GetRoute(rut[i]));
    strcat(dir, " ");
  }
  for (int i=0; i<strlen(dir); i++) {
    Serial.print((char)dir[i]);
  }
  Serial.println();
  SmartPrint(dir, 1);
}

