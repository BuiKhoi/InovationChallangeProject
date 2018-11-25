void ReceiveMsg() {
  uint8_t idx;
  uint8_t pdatabuf[200];
  SwitchMode(MODE_0_NORMAL);
  int count = 0;
  while (!ReadAUX() || !((StrCtn(pdatabuf, '<') && StrCtn(pdatabuf, '>')))) {
    int lengths = softSerial.available();

    if (lengths > 0)
    {
      for (idx = 0; idx < lengths; idx++) {
        pdatabuf[count++] = softSerial.read();
        if (pdatabuf[count-1] != '<') {
          if (pdatabuf[count-1] == '>') {
            Serial.println();
          } else {
            Serial.print((char)pdatabuf[count-1]);
          }
        }
      }
    }
  }
}

bool StrCtn(uint8_t* str, uint8_t key) {
//  Serial.println(key);
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == key) {
      return true;
    }
  }
  return false;
}

RET_STATUS SendMessage(uint8_t ADDH, uint8_t ADDL, uint8_t *Mess)
{
  RET_STATUS STATUS = RET_SUCCESS;

  SwitchMode(MODE_0_NORMAL);

  if(ReadAUX()!=HIGH)
  {
    return RET_NOT_IMPLEMENT;
  }
  delay(10);
  if(ReadAUX()!=HIGH)
  {
    return RET_NOT_IMPLEMENT;
  }

  int lengths = 3+strlen(Mess);

  //TRSM_FP_MODE
  //Send format : ADDH ADDL CHAN DATA_0 DATA_1 DATA_2 ...
  uint8_t SendBuff[lengths] = {ADDH, ADDL, 0x17};
  for (int i=3; i<lengths; i++) {
    SendBuff[i] = Mess[i-3];
  }
  softSerial.write(SendBuff, lengths);

  return STATUS;
}
