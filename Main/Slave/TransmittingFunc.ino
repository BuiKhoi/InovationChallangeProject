bool RequestRoomDirection() {
  uint8_t request[200] = "<";
  strcat(request, CardID);
  strcat(request, "#");
  strcat(request, myId);
  strcat(request, ">");

  for (int i = 0; i < strlen(request); i++) {
    Serial.print((char)request[i]);
  }
  NewMessage = false;
  lcd.setCursor(0, 2);
  lcd.print("Requesting data");
  return true;
}

uint8_t* GetCommand(int command) {
  switch (command) {
    case 0: {
        return "RQD";
      }
  }
}

