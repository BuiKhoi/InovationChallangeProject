void ListenForKnob() {
  static bool prev_A = true;
  bool temp = !digitalRead(EncoderA);
  if (temp && prev_A) {
    if (digitalRead(EncoderB)) {
      position++;
    } else position--;
    prev_A = false;
  } else if (!temp) {
    prev_A = true;
  }
}

int GetControl() {
  static bool prev_A = true;
  bool temp = !digitalRead(EncoderA);
  if (temp && prev_A) {
    prev_A = false;
    if (digitalRead(EncoderB)) {
      return 1;
    } else return 2;
  } else if (!temp) {
    prev_A = true;
  }

  static int prev_but = -1;
  static unsigned long long int last_press = millis();
  if (millis() - last_press > 100) {
    last_press = millis();
    if (!digitalRead(EncoderButton)) {
      if (prev_but == -1)  {
        while (!digitalRead(EncoderButton)) {
          if (millis() - last_press > 700) {
            if (prev_but != 3) {
              prev_but = 3;
              return 3;
            }
          }
        }
        if (prev_but != 0) {
          prev_but = 0;
          return 0;
        }
      }
    } else prev_but = -1;
  }

  return -1;
}
