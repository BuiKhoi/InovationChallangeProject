//  switch (SysMode) {
//    case FREE: {
//      FreeMode();
//      break;
//    }
//    case SHOW_INFO: {
//      ShowInfo();
//      break;
//    }
//    case SHOW_DIRECTION: {
//      ShowDirection();
//      break;
//    }
//  }

//  static int pos = -1;
//  ListenForKnob();
//  if (position != pos) {
//    pos = position;
//    lcd.setCursor(0,0);
//    lcd.clear();
//    lcd.print("Position: ");
//    lcd.print(pos);
//  }
//  if (digitalRead(EncoderButton)) {
//    lcd.clear();
//  }

//  if ( ! mfrc522.PICC_IsNewCardPresent())
//    return;
//
//  if ( ! mfrc522.PICC_ReadCardSerial())
//    return;
//
//  lcd.setCursor(0,0);
//  lcd.print("UID: ");
//  for (int i=0; i<4; i++) {
//    lcd.print(mfrc522.uid.uidByte[i], HEX);
//    lcd.print(" ");
//  }

//static int number = 0;
//int temp = GetControl();
//if (temp != -1) {
//  number += temp;
//  lcd.setCursor(0, 0);
//  lcd.print(number);
//}
