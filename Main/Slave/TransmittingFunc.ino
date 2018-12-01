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

uint8_t* GetCommand(int command) {
  switch (command) {
    case 0: {
        return "RQD";
      }
  }
}

