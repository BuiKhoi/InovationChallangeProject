void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t arr[3] = {0x30, 0x31, 0x3A};
  for (int i=0; i<3; i++) {
    uint8_t temp = 0xFF & arr[i];
    Serial.print((char)temp);
    Serial.print("  ");
  }
  Serial.println();
//  Serial.write(arr, 3);
  delay(1000);
}
