#include <LiquidCrystal_I2C.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#include <Wire.h>
BluetoothSerial SerialBT;
int mins;
int sec;
String incomingChar;
String message;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
lcd.init(); 
lcd.backlight();
Serial.begin(115200);
SerialBT.begin("ESP32");
pinMode(25, OUTPUT);
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
  for(int i = 0; i<3 ; i++){
    digitalWrite(25,HIGH);
    delay(500);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stopping");
  digitalWrite(25,LOW);
  delay(500);
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
  mins = 0;
  sec = 0;
  buz();
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
     sec=0;
  lcd.clear();
  message = "";
  buz();
  }
  else if(message == "103"){
     for(sec=0;sec<60;sec++){
     funin2(2);
     funin();
     if(message == "100"){
      sec=60;
     }     
     }
     sec=0;
  lcd.clear();
  message = "";
  buz();
  }  
    funin();    
  }
  }            
  delay(1000);
}
