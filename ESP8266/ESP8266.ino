#include <NTPtimeESP.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
NTPtime NTPch("ch.pool.ntp.org");   // Server NTP
char *ssid      = "VIP";               // Ten WiFi SSID
char *password  = "1234567890";               // Mat khau wifi
strDateTime dateTime;

#include "DHT.h"
// Pin
#define DHTPIN D4
// Su dung cam bien DHT11
#define DHTTYPE DHT11
// Cau hinh chan DHT 
DHT dht(DHTPIN, DHTTYPE, 15);
#include <LiquidCrystal_I2C.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

// Set these to run example.
#define WIFI_SSID "VIP"
#define WIFI_PASSWORD "1234567890"

#define CHIPID ESP.getChipId()
#define PATH "/device/"
#define FBHOST "myswitch-4f0b8.firebaseio.com"
#define FBKEY "lSnOGSEu18vO9DutyxYP4cEmcoMKcDNlmpVVvlUA"

int   num = 4;
int   pins[] = {14, 12, 13, 15}; //D0-3
// 12: D6
// 13: D7;
// 14: D5;
// 15: D8
int   switchs[] = {1,2,3,4};
int   states[] = {LOW ,LOW, LOW, LOW};
 String s,hour;
LiquidCrystal_I2C lcd(0x3f,20,4);
void setup() {
//  Serial.begin(9600);
//
// 
//  // connect to wifi.
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//  }






int cnt = 0;
  //Khởi tạo baud 9600
  Serial.begin(9600);
  //Mode wifi là station
  WiFi.mode(WIFI_STA);
  //Chờ kết nối
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(cnt++ >= 10){
       WiFi.beginSmartConfig();
       while(1){
           delay(1000);
           //Kiểm tra kết nối thành công in thông báo
           if(WiFi.smartConfigDone()){
             Serial.println("SmartConfig Success");
             break;
           }
       }
    }
  }
  
  Serial.println("");
  Serial.println("");
  
  WiFi.printDiag(Serial);
  
  // Khởi tạo server
  Udp.begin(49999);
  Serial.println("Server started");

  // In địa chỉ IP
  Serial.println(WiFi.localIP());








  Firebase.begin(FBHOST, FBKEY);

  delay(1000);
  
  
  lcd.init();
  lcd.backlight();
  dht.begin();
  firebaseGetFirst();
  registerMicrocontroller();
 
}

void loop() {
 // Nhận gói tin gửi từ ESPTouch
  Udp.parsePacket();
  //In IP của ESP8266
  while(Udp.available()){
    Serial.println(Udp.remoteIP());
    Udp.flush();
    delay(5);
  }
  firebaseGet();
  sendDHT();
// show();

  
}
void show(){
 
}
void sendDHT() {
  dateTime = NTPch.getNTPtime(7.0, 0);
  delay(100);
  String path = getPath();
  path+="/DHT";
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 String thu="";
 switch(dateTime.dayofWeek){
  case 1: thu="Sun"; break;
  case 2: thu="Mon"; break;
  case 3: thu="Tue"; break;
  case 4: thu="Wed"; break;
  case 5: thu="Thu"; break;
  case 6: thu="Fri"; break;
  case 7: thu="Sat"; break;
 }

 if(dateTime.minute < 10)
    s="0"+(String)dateTime.minute;
 else s=(String)dateTime.minute;
 if(dateTime.hour < 10)
    hour="0"+(String)dateTime.hour; 
 else hour=(String)dateTime.hour;
 // Firebase.pushString(path+"/Temp", (String)t );
//  Firebase.pushString(path+"/Humid", (String)h);
  // lcd.clear();
       if(dateTime.valid){
     lcd.setCursor(3,0);
    lcd.print(thu+" "+(String)dateTime.day+"/"+(String)dateTime.month+"/"+(String)dateTime.year);
    lcd.setCursor(7,1);
    lcd.print(hour+":"+s);
  
  
       }
  if (isnan(t) || isnan(h)) { // Kiểm tra xem thử việc đọc giá trị có bị thất bại hay không. Hàm isnan bạn xem tại đây http://arduino.vn/reference/isnan
  } 
  else {
    lcd.setCursor(1,2);
    lcd.print("Nhiet do: "+(String)t+"*C");
    lcd.setCursor(1,3);
    lcd.print("Do am:    "+(String)h+"%");
    String path = getPath();
    Firebase.setFloat(path + "temp", t);
    Firebase.setFloat(path + "humid", h);
  }
 
  
}


void registerMicrocontroller() {
  lcd.setCursor(1,1);
  lcd.print("Loading database...");
  for (int i = 0; i < num; i++) { 
    pinMode(pins[i], OUTPUT); 
    String path = getPath();
    path = path + "/switch" + switchs[i];
  
    Firebase.setBool(path, states[i]);
  }
  lcd.clear();
  
}

void firebaseGet() {

  String path = getPath();
  //path += "switch";
  FirebaseObject object = Firebase.get(path);


  if (Firebase.failed()) {
    lcd.setCursor(1,1);
    lcd.print("Database error...");
    lcd.clear();
    Serial.println("Firebase error");
    Serial.println(Firebase.error());
  }

      
  for (int i = 0; i < num; i++) {
  
    int pin = switchs[i];
    String p = "switch";
    p = p + pin;
    
    bool state = object.getBool(p);

    if (states[i] != state) {

      digitalWrite(pins[i], state);
      states[i] = state;

      Serial.println();
      Serial.printf("Switch: %d State: %d", pin, state);

    }
  }

  delay(500);

}

void firebaseGetFirst() {

  String path = getPath();
  FirebaseObject object = Firebase.get(path);


  if (Firebase.failed()) {
    lcd.setCursor(1,1);
    lcd.print("Database error");
    lcd.setCursor(1,2);
    lcd.print("Create new Database");
    Serial.println("Khoi tao database");
    Serial.println(Firebase.error());
    delay(1000);
    lcd.clear();
  }


  for (int   i = 0; i < num; i++) {

    int   pin = switchs[i];
    String p = "switch";
    p = p + pin;
   
    bool state = object.getBool(p);

    if (states[i] != state) {

      digitalWrite(pins[i], state);
      states[i] = state;

      Serial.println();
      Serial.printf("Switch: %d State: %d", pin, state);

    }




  }

  delay(500);

}


String getPath() {

  String path = "";

  path += PATH;
  path += CHIPID;
  return path;
}
