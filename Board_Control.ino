/*
 * Hardware Prototype :
 * 1. LoLin V.1.0
 * 2. Arduino Mini Pro
 * 3. Trafic Light
 * 4. SDcard + Amplifier
 * 5. Regulator tegangan
 * 6. I2C LCD 16x2
 * 7. LCD 16x2
 * 8. Speaker
 */

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define FIREBASE_HOST "smart-traffic-e7625.firebaseio.com"
#define FIREBASE_AUTH "NKy5jMn9Kw1IhCusddwxmCe9DTpi97jGpMbFvdFK"

#define WIFI_SSID "testing"
#define WIFI_PASSWORD "12345678"

String lastdatam, datam, lastdatao, datao;
String TLB="", TLT="", TLU="", TLS="";

const int PT = 6;
const int PU = 7;
const int PB = 3;
const int PS = 4;
const int SP = 5;


void setup() {
  Serial.begin(9600);
  Wire.begin(1, 2);
  
  // Tampilan LCD
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Smart Traffic");
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(PT, OUTPUT);
  pinMode(PU, OUTPUT);
  pinMode(PB, OUTPUT);
  pinMode(PS, OUTPUT);
  pinMode(SP, OUTPUT);
}

int n = 0;
bool TLstate;
bool TLplaysound;
String TLsound;
String TlbUlamp="",TluUlamp="",TltUlamp="",TlsUlamp="";

void loop() {
  TLstate = Firebase.getBool("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLstate");
  if (Firebase.failed()) {
      Serial.print("TLstate : /Failed");
      Serial.println(Firebase.error()); 
      lcd.setCursor(0,1);
      lcd.print("Check Up"); 
      return;
  }
  delay(400);
  
  if (TLstate == false ){
    //Serial.println("cek Manual")
     TlbUlamp = Firebase.getString("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLpos/TLb/ulamp");
     TltUlamp = Firebase.getString("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLpos/TLt/ulamp");
     TluUlamp = Firebase.getString("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLpos/TLu/ulamp");
     TlsUlamp = Firebase.getString("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLpos/TLs/ulamp");
     TLplaysound = Firebase.getBool("/new-tl/-KlKL87oFYPYGnFJeb5F/-Kw0-L2Tq9ditAA0IdHj/TLplaysound");
     
     if (Firebase.failed()) {
          Serial.print("TLstate : /Failed");
          Serial.println(Firebase.error());
          lcd.setCursor(0,1);  
          lcd.print("Firebase Err");
          return;
      }
      
      if (TlbUlamp == "red"){
      digitalWrite(PB, HIGH);
      digitalWrite(PT, LOW);
      digitalWrite(PU, LOW);
      digitalWrite(PS, LOW);
      Serial.println(TlbUlamp); 
      lcd.setCursor(0,1);
      lcd.print("Barat Merah");       
      }

      else if (TltUlamp == "red"){
      digitalWrite(PT, HIGH);
      digitalWrite(PB, LOW);
      digitalWrite(PU, LOW);
      digitalWrite(PS, LOW);
      Serial.println(TltUlamp);
      lcd.setCursor(0,1);
      lcd.print("Timur Merah");
      }

      else if (TluUlamp == "red"){
      digitalWrite(PU, HIGH);
      digitalWrite(PB, LOW);
      digitalWrite(PT, LOW);
      digitalWrite(PS, LOW);
      Serial.println(TluUlamp);
      lcd.setCursor(0,1);
      lcd.print("Utara Merah");
      }

      else if (TlsUlamp == "red"){
      digitalWrite(PS, HIGH);
      digitalWrite(PU, LOW);
      digitalWrite(PB, LOW);
      digitalWrite(PT, LOW);
      Serial.println(TlsUlamp);
      lcd.setCursor(0,1);
      lcd.print("Selatan Merah");
      }
     
      if (TLplaysound == true ){
        digitalWrite(SP, HIGH);
      }
      else{
        digitalWrite(SP, LOW);
      }

}
      else {
    //Serial.println("cek Otomatis");    
    datao = "Otomatis";
      if (datao!=lastdatao){
        Serial.print(datao);
        Serial.println();
        lastdatao=datao;
      }}

      
      

      
      /*
      //Serial.print("TlbUlamp nyala ");
      if (TlbUlamp == "red"){
        //Serial.println(TlbUlamp);
        //Serial.write("A1");
        TLB = "A1";
        
      } else if (TlbUlamp == "yellow") {
        //Serial.println(TlbUlamp);
        //Serial.write("A2");
        TLB = "A2";
       
      } else {
        //Serial.println(TlbUlamp); 
        //Serial.write("A3");
        TLB = "A3";
       
      }
      
      if (TltUlamp == "red"){
        //Serial.println(TlbUlamp);
        //Serial.write("B1");
        TLT = "B1";
       
      } else if (TltUlamp == "yellow") {
        //Serial.println(TlbUlamp);
        //Serial.write("B2");
        TLT = "B2";
       
      } else {
        //Serial.println(TlbUlamp); 
        //Serial.write("B3");
        TLT = "B3";
        
      }

      if (TluUlamp == "red"){
        //Serial.println(TlbUlamp);
        //Serial.write("C1");
        TLU = "C1";
        
      } else if (TluUlamp == "yellow") {
        //Serial.println(TlbUlamp);
        //Serial.write("C2");
        TLU = "C2";
        
      } else {
        //Serial.println(TlbUlamp); 
        //Serial.write("C3");
        TLU = "C3";
        
      }

      if (TlsUlamp == "red"){
        //Serial.println(TlbUlamp);
        //Serial.write("D1");
        TLS = "D1";
      } else if (TlsUlamp == "yellow") {
        //Serial.println(TlbUlamp);
        //Serial.write("D2");
        TLS = "D2";
      } else {
        //Serial.println(TlbUlamp); 
        //Serial.write("D3");
        TLS = "D3";
      }
      
      if (TLplaysound == true ){
        TLsound = "S1";
      }
      else {
        TLsound = "S0";
      }
      datam = TLB+TLT+TLU+TLS+TLsound;
      Serial.print(datam);
      Serial.println();
      Serial.print(TLplaysound);
      Serial.println();
  }
      
      /*datam = TLB+TLT+TLU+TLS+TLsound;
      if (datam!=lastdatam){
        Serial.print(datam);
        Serial.println();
        lastdatam=datam;
      }*/
/*
    //Serial.write("Otomatis");
    //Serial.println();
    //delay(500);
  
 /* 
 // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);
//*/
  

}
