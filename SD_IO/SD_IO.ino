#include <SPI.h>
#include <SD.h>

void setup() {
  Serial.begin(9600);
  while (!SD.begin(10)) {
    Serial.println("SD Failed, check card or wiring");
  }
  Serial.println("Begin Testing");
//  writeFile("Bui Quoc Khoi");
//  Serial.println("Done Writing");
  Serial.println(readFile());
}

void loop() {
  
}

void writeFile(String str) {
  File SDReadFile;
  
  if (SD.exists("Data.txt")) {
    SD.remove("Data.txt");
  }
  
  SDReadFile = SD.open("Data.txt", FILE_WRITE);
  if (SDReadFile) {
    SDReadFile.println(str);
    SDReadFile.close();
  } else {
    Serial.println("File failed to write");
  }
}

String readFile() {
  File SDReadFile;
  String str;
  SDReadFile = SD.open("Data.txt");
  if (SDReadFile) {
    while (SDReadFile.available()) {
      str.concat(char(SDReadFile.read()));
    }
    SDReadFile.close();
  } else {
    Serial.println("File failed to open");
  }
  return str;
}

