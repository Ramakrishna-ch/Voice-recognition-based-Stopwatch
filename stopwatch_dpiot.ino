#include <LiquidCrystal_I2C.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#include <Wire.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif
BluetoothSerial SerialBT;
int mins;
int sec;
String incomingChar;
String message;
const char* ssid     = "TIC_fiber-ram-lavan";
const char* password = "krizz.ch*9541";
const char* serverName = "http://lavankumarch.heliohost.org/stopwatchpro/php/upload1.php";
const char* serverName1 = "http://lavankumarch.heliohost.org/stopwatchpro/php/upload2.php";
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
lcd.init(); 
lcd.backlight();
Serial.begin(115200);
SerialBT.begin("ESP32");
pinMode(25, OUTPUT);
WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void funin() {
  incomingChar = SerialBT.read();
  Serial.print(incomingChar);
  if(incomingChar != "-1"){
    Serial.print(incomingChar);
    message = incomingChar;}
  }
void funin2(int str){ 
  if(str ==1){
  lcd.clear();
  lcd.setCursor(0,0);  
          lcd.print("Stopwatch");
  lcd.setCursor(0,1);
          lcd.print(mins);
          lcd.setCursor(2,1);
          lcd.print("mins : ");
          lcd.setCursor(9,1);
          lcd.print(sec);
          lcd.setCursor(11 ,1);
          lcd.print(" secs");
         delay(1000);
  }
  else if(str ==2){
    lcd.clear();
  lcd.setCursor(0,0);
          lcd.print("Timer");
  lcd.setCursor(0,1);
          lcd.print(mins);
          lcd.setCursor(2,1);
          lcd.print("mins : ");
          lcd.setCursor(9,1);
          lcd.print(sec);
          lcd.setCursor(11 ,1);
          lcd.print(" secs");
         delay(1000);
  }
}
void buz(){
  for(int i = 0; i<2 ; i++){
    digitalWrite(25,HIGH);
    delay(500);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stopping &");
  lcd.setCursor(0,1);
  lcd.print("Uploading");
  digitalWrite(25,LOW);
  delay(500);
  }}
  void buz1(int g){
    if(g == 1){
      for(int i = 0; i<2 ; i++){
    digitalWrite(25,HIGH);
    delay(500);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Uploaded ");
  lcd.setCursor(0,1);
  lcd.print("Successfully");
  digitalWrite(25,LOW);
  delay(500);
  }}
    else if(g == 2){
      for(int i = 0; i<2 ; i++){
    digitalWrite(25,HIGH);
    delay(500);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Uploading ");
  lcd.setCursor(0,1);
  lcd.print("Not Successful");
  digitalWrite(25,LOW);
  delay(500);
  }}
}
void webdata(int m, int n){
  String dat1;
  
  if(WiFi.status()== WL_CONNECTED){
    if(m == 1){
     int dat2 = (mins * 60) + sec;
     dat1 = String(dat2);
    Serial.print(dat1);
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "dat1=" + dat1 + "";
    Serial.print("httpRequestData: ");      
    Serial.println(httpRequestData);    
    buz();   
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      buz1(1);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      buz1(2);
    }
    http.end();
  }
  else if(m ==2){
    HTTPClient http;
    http.begin(serverName1);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "timerdata=" + String(n) + "";
    Serial.print("httpRequestData: ");      
    Serial.println(httpRequestData);  
     buz();     
    int httpResponseCode = http.POST(httpRequestData);
   
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      buz1(1);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      buz1(2);
    }
    http.end();
  }
  }
  else {
    Serial.println("WiFi Disconnected");
  }  
 
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stopwatch or");
  lcd.setCursor(2,1);
  lcd.print("Timer");
  delay(1500);
  funin();
  if(message == "101"){
    while(message != "104"){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("start-stopwatch");
    lcd.setCursor(1,1);
    lcd.print("home-Goback");
    delay(1000);  
  funin();
  if(message == "97"){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("stopwatch");
    lcd.setCursor(0,1);
    lcd.print("started...");
    delay(500);
    lcd.clear();
    while(message != "100"){
       if(message == "97"){
        if(sec<60){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Stopwatch");
          lcd.setCursor(0,1);
          lcd.print(mins);
          lcd.setCursor(2,1);
          lcd.print("mins : ");
          lcd.setCursor(9,1);
          lcd.print(sec++);
          lcd.setCursor(11,1);
          lcd.print(" secs");
          delay(1000);
        }
        else{
          sec = 0;
          mins++;
          lcd.clear();
        }
         }
       else if(message == "98"){
        funin2(1);
        }
         funin();
  }
  webdata(1, 0);
  mins = 0;
  sec = 0;  
  lcd.clear();
  }
  funin();
  }
  }
  else if(message == "99"){
    funin();
    while(message != "104"){
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("first-30,second");
    lcd.setCursor(00,1);
    lcd.print("-60,home-Goback");
    delay(1000);  
 
  if(message == "102"){
    for(sec=0;sec<30;sec++){
     funin2(2);
     funin();
     if(message == "100"){
      sec=30;
     }}
     webdata(2,30);
     sec=0;
  lcd.clear();
  message = "";
  }
  else if(message == "103"){
     for(sec=0;sec<60;sec++){
     funin2(2);
     funin();
     if(message == "100"){
      sec=60;
     }     
     }
     webdata(2,60);
     sec=0;
  lcd.clear();
  message = "";
  }  
    funin();    
  }
  }            
  delay(1000);
}
