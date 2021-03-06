#define EncoderA 2
#define EncoderB A1
#define EncoderButton A0

int position = 0;

void setup() {
  Serial.begin(9600);
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);
  pinMode(EncoderButton, INPUT);
}

void loop() {
  static int number = 0;
  int temp = GetControl();
  if (temp != -1) {
    number+=temp;
    lcd.print(number);
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
  static int last_press = millis();
  if (millis() - last_press > 100) {
    last_press = millis();
    if (!digitalRead(EncoderButton)) {
      //    Serial.println("Press");
      if (prev_but == -1)  {
        int start = millis();
        while (!digitalRead(EncoderButton)) {
          if (millis() - start > 500) {
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
