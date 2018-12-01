#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "gdg-dev-fest-2d456.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "Hackathon_2"
#define WIFI_PASSWORD "GWET03M6UT"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //  Firebase.setInt("abc", 100);
  //  if (Firebase.failed()) {
  //    Serial.print("setting /number failed:");
  //    Serial.println(Firebase.error());
  //    return;
  //  }
}

void loop() {
  static bool printed = false;
  if (!printed) {
    char temp[20] = "";
    if (Serial.available()) {
      int i = 0;
      while (Serial.available()) {
        temp[i++] = (char)Serial.read();
      }
    }
    Serial.println(temp);
  }
  printed = true;
}
