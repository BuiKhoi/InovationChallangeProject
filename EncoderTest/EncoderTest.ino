#define KnobA 5
#define KnobB 6

int position = 0;

void setup() {
  Serial.begin(9600);
  pinMode(KnobA, INPUT);
  pinMode(KnobB, INPUT);
}

void loop() {
  static int pos = -1;
  ListenForKnob();
  if (position != pos) {
    pos = position;
    Serial.print("Position: ");
    Serial.println(pos);
  }
}

void ListenForKnob() {
  static bool prev_A = true;
  bool temp = !digitalRead(KnobA);
  if (temp&&prev_A) {
    if (digitalRead(KnobB)) {
      position++;
    } else position--;
    prev_A = false;
  } else if (!temp) {
    prev_A = true;
  }
}

