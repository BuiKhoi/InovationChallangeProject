void ProcessDirection() {
  uint8_t temp[50];
  strcpy(temp, GetNextCommand());
  if (temp == "DIR") {
    Route();
  } else if (temp == "HRE") {
    lcd.clear();
    lcd.setCursor(0, 0);
    SmartPrint("You have reach your destination");
  }
}

uint8_t* GetNextCommand() {
  uint8_t rtr[50] = "";
  int i = 0;
  while (StrBuff[i] == "." || StrBuff[i] == "<") {
    i++;
  }
  while (StrBuff[i] != '#') {
    strcat(rtr, StrBuff[i]);
    StrBuff[i] = ".";
  }
  return rtr;
}

void Route() {
  uint8_t rte[80];
  strcpy(rte, "");
  uint8_t rcv[100];
  strcpy(rcv, GetNextCommand());
  for (int i=0; i<strlen(rcv); i++) {
    strcat(rte, " ");
    strcat(rte, GetRoute(rcv[i]));
  }
  SmartPrint(rte);
}

