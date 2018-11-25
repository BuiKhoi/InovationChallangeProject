char moduleID[5];

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int count = 0;
    while (Serial.available()) {
      moduleID[count++] = Serial.read();
    }
    
    char path[20];
    strcpy(path, GetPath(moduleID));
    for (int i = 0; i < strlen(path); i++) {
      Serial.print(path[i]);
    }
    Serial.println();
  }
}

char* GetPath(char* file) {
  char path[20];
  strcpy(path, "Node/");
  strcat(path, file);
  strcat(path, ".txt");
  return path;
}

