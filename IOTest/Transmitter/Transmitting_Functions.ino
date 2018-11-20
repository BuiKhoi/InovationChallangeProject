RET_STATUS ReceiveMsg(uint8_t *pdatabuf, uint8_t *data_len)
{

  RET_STATUS STATUS = RET_SUCCESS;
  uint8_t idx;

  SwitchMode(MODE_0_NORMAL);
  *data_len = softSerial.available();

  if (*data_len > 0)
  {
    Serial.print("ReceiveMsg: ");  Serial.print(*data_len);  Serial.println(" bytes.");

    for(idx=0;idx<*data_len;idx++)
      *(pdatabuf+idx) = softSerial.read();

    for(idx=0;idx<*data_len;idx++)
    {
      Serial.print(" 0x");
      Serial.print(0xFF & *(pdatabuf+idx), HEX);    // print as an ASCII-encoded hexadecimal
    } Serial.println("");
  }
  else
  {
    STATUS = RET_NOT_IMPLEMENT;
  }

  return STATUS;
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
  Serial.println("Sending Message");
  return STATUS;
}
