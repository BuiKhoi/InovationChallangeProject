void ProcessRequest() {
  uint8_t request[10] = "";
  strcpy(request, GetNextCommand());
  if (request == "RQD") {
    uint8_t CardID[10];
    strcpy(CardID, GetNextCommand());
    int destination = GetRoomByCardID(CardID);
    int stand = atoi(GetNextCommand());
    SendRoute(stand, destination);
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

uint8_t SendRoute(int stand, int destination) {
  uint8_t Node[2];
  strcpy(Node, GetNodeAddress(stand));
  if (destination / 100 - stand / 100 != 0) {
    uint8_t cmd;
    strcpy(cmd, "<HRTE,TF@");
    strcat(cmd, char(destination / 100));
    strcat(cmd, ">");
    SendMessage(Node[0], Node[1], cmd);
  } else {
    if (stand - destination > 0) {
      SendMessage(Node[0], Node[1], "<HLTYD>");
    } else {
      SendMessage(Node[0], Node[1], "<HRTYD>");
    }
  }
}

