bool AUX_STT = false;

bool ReadAUX() {
  int val = analogRead(AUX_PIN);

  if (val < 50)
  {
    AUX_STT = LOW;
  }
  else {
    AUX_STT = HIGH;
  }

  return AUX_STT;
}

TRANS_STATUS WaitHighAUX() {
  int start = millis();
  while (!ReadAUX() && (millis() - start < 2000)) {
    Serial.print(".");
    delay(50);
  }

  if (millis() - start > 2000) {
    return TRANS_TIMEOUT;
  }

  return TRANS_SUCCESS;
}

void SwitchMode(WORK_MODE mode) {
  static WORK_MODE prev_mode = INIT;
  if (mode != prev_mode) {
    switch (mode) {
      case NORMAL: {
          digitalWrite(M0_PIN, LOW);
          digitalWrite(M1_PIN, LOW);
          break;
        }
      case WAKEUP: {
          digitalWrite(M0_PIN, HIGH);
          digitalWrite(M1_PIN, LOW);
          break;
        }
      case POWERSAVER: {
          digitalWrite(M0_PIN, LOW);
          digitalWrite(M1_PIN, HIGH);
          break;
        }
      case SLEEP: {
          digitalWrite(M0_PIN, HIGH);
          digitalWrite(M1_PIN, HIGH);
          break;
        }
    }
  }
  WaitHighAUX();
}

void CleanBuffer() {
  while (LoraNode.available())
  {
    LoraNode.read();
  }
}

TRANS_STATUS SetAddress(uint8_t AddH, uint8_t AddL) {
  uint8_t SendBuff[6] = { 0xC0, AddH, AddL, 0x1A, 0x17, 0x04 };
  SwitchMode(SLEEP);
  int start = millis();
  while (!ReadAUX()) {
    if (millis() - start > 200) {
      return TRANS_TIMEOUT;
      break;
    }
    delay(10);
  }
  LoraNode.write(SendBuff, 6);
  SwitchMode(NORMAL);
  return TRANS_SUCCESS;
}

TRANS_STATUS SendMessage(Node node, uint8_t* Mess) {
  //  TRANS_STATUS STATUS = TRANS_SUCCESS;
  //  SwitchMode(NORMAL);
  //  if (ReadAUX() != HIGH)
  //  {
  //    return TRANS_NOT_IMPLEMENT;
  //  }
  //  delay(10);
  //  if (ReadAUX() != HIGH)
  //  {
  //    return TRANS_NOT_IMPLEMENT;
  //  }
  //  uint8_t addr[2] = GetAddress(node);
  //  int lengths = 3 + strlen(Mess);
  //  //Send format : ADDH ADDL CHAN DATA_0 DATA_1 DATA_2 ...
  //  uint8_t SendBuff[lengths] = { addr[0], addr[1], 0x17 };
  //  for (int i = 3; i < lengths; i++) {
  //    SendBuff[i] = Mess[i - 3];
  //  }
  //  LoraNode.write(SendBuff, lengths);
  //  return STATUS;
}

void SendMessage(uint8_t AddH, uint8_t AddL, uint8_t *Mess) {
  Serial.println("Starting send message");
  TRANS_STATUS STATUS = TRANS_SUCCESS;
  SwitchMode(NORMAL);
  if (ReadAUX() != HIGH)
  {
    return TRANS_NOT_IMPLEMENT;
  }
  delay(10);
  if (ReadAUX() != HIGH)
  {
    return TRANS_NOT_IMPLEMENT;
  }
  int lengths = 3 + strlen(Mess);
  //Send format : ADDH ADDL CHAN DATA_0 DATA_1 DATA_2 ...
  uint8_t SendBuff[lengths] = { AddH, AddL, 0x17 };
  for (int i = 3; i < lengths; i++) {
    SendBuff[i] = Mess[i - 3];
  }
  LoraNode.write(SendBuff, lengths);
  return STATUS;
}

void ReciveMessage() {
  //  detachInterrupt(Aux_interrupt);
  uint8_t idx;

  SwitchMode(NORMAL);
  int count = 0;
  while (!ReadAUX() && (StrCtn(StrBuff, '<') && StrCtn(StrBuff, '>'))) {
    int length = LoraNode.available();

    if (length > 0)
    {
      for (idx = 0; idx < length; idx++)
        StrBuff[count++] = LoraNode.read();
        Serial.println(StrBuff[count-1]);
    }
    NewMessage = true;
  }
}

bool StrCtn(uint8_t* str, uint8_t key) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == key) {
      return true;
    }
  }
  return false;
}

void ShowError(TRANS_STATUS status) {
  switch (status) {
    case TRANS_SUCCESS: {
        Serial.println("Success");
        break;
      }
    case TRANS_UNKNOWN_ERROR: {
        Serial.println("Unknown error");
        break;
      }
    case TRANS_NOT_SUPPORTED: {
        Serial.println("Transmission not supported");
        break;
      }
    case TRANS_NOT_IMPLEMENT: {
        Serial.println("Transmission not implemented");
        break;
      }
    case TRANS_NOT_INITIAL: {
        Serial.println("System is not initialized");
        break;
      }
    case TRANS_INVALID_PARAM: {
        Serial.println("Invalid parameters");
        break;
      }
    case TRANS_DATA_SIZE_NOT_MATCH: {
        Serial.println("Data size not match");
        break;
      }
    case TRANS_BUFF_TOO_SMALL: {
        Serial.println("Buffer size too small");
        break;
      }
    case TRANS_TIMEOUT: {
        Serial.println("Transmission timeout");
        break;
      }
    case TRANS_HW_ERROR: {
        Serial.println("HW error");
        break;
      }
  }
}

uint8_t* GetAddress(Node node) {
  uint8_t rtr[2];
  if (node.AddH != 0x00 && node.AddL != 0x00) {
    rtr[0] = node.AddH;
    rtr[1] = node.AddL;
  }
  else {
    char path[20];
    strcpy(path, "Node/");
    strcat(path, node.Id);
    strcat(path, ".txt");
    File dataFile = SD.open(path);

    if (dataFile) {
      uint8_t Buff[20];
      int count = 0;
      while (dataFile.available()) {
        Buff[count++] = dataFile.read();
      }
      dataFile.close();

      uint8_t temp[3];
      temp[0] = Buff[0];
      temp[1] = Buff[1];
      rtr[0] = GetHex(temp);

      temp[0] = Buff[3];
      temp[1] = Buff[4];
      rtr[1] = GetHex(temp);
    }
    else {
      Serial.println("Data file failed to open");
    }
  }
  return rtr;
}

