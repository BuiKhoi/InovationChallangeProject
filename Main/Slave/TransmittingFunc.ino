bool RequestRoomDirection() {
  uint8_t request[200] = "<";
  strcat(request, GetCommand(0));
  strcat(request, "#");
  strcat(request, CardID);
  strcat(request, "#");
  strcat(request, myId);
  strcat(request, ">");
  
  SendMessage(MASTER_ADDH, MASTER_ADDL, request);
  NewMessage = false;
  return true;
}

uint8_t* GetCommand(int command) {
  switch(command) {
    case 0: {
      //Request direction
      return "RQD";
    }
  }
}

