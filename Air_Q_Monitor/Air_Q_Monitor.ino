#include<SPI.h>
#include<Wire.h>
#include<LiquidCrystal.h>
#include "DHT.h"

#define DHTTYPE DHT11 
const int DHTPIN = 2; 
const int mq135LED = 4;
const int mq9LED = 5;
const int mq2LED = 6;
const int buzzer = 0;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);

const int mx135 = 400; //400
const int mx9 = 300; //500
const int mx2 = 300; //300


//LCD Display
void resetLCD(){
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(1000);
}

int f = 0;

void check_condition(int m, int n, int o){
    if(m>=mx135){
      digitalWrite(mq135LED, HIGH); delay(200);
      digitalWrite(mq135LED, LOW); delay(200);
      
        tone(buzzer, 1500); delay(1000); 
        noTone(buzzer); delay(1000);

      // for(int i = 0; i<10; i++){
      //   tone(buzzer, 1500); delay(1000); 
      //   noTone(buzzer); delay(1000);
      // }
    }
    else{
      digitalWrite(mq135LED, HIGH); 
    }
    if(n>=mx9){
      digitalWrite(mq9LED, HIGH); delay(200);
      digitalWrite(mq9LED, LOW); delay(200);

      tone(buzzer, 1500); delay(1000); 
      noTone(buzzer); delay(1000);
    }
    else{
      digitalWrite(mq9LED, HIGH); 
    }
    if(o>=mx2){
      digitalWrite(mq2LED, HIGH); delay(200);
      digitalWrite(mq2LED, LOW); delay(200);
      
      tone(buzzer, 1500); delay(1000); 
      noTone(buzzer); delay(1000);
    }
    else{
      digitalWrite(mq2LED, HIGH); 
    }
    if(m<mx135 && n<mx9 && o<mx2){
      tone(buzzer, 1500); delay(1000); 
      noTone(buzzer); delay(1000);
    }
}
void setup(){

  //LCD 16x2 Display
  lcd.begin(16, 2);

  //Gas sensors
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  //Buzzer
  pinMode(buzzer, OUTPUT);

  //LED's
  pinMode(mq135LED, OUTPUT);
  pinMode(mq9LED, OUTPUT);
  pinMode(mq2LED, OUTPUT);

  //Temp and Humidity
  dht.begin();

  // //Analog serial
  // Serial.begin(9600);


  lcd.setCursor(0, 0); lcd.print("Hello World!    ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(1500); resetLCD(); 
  lcd.setCursor(0, 0); lcd.print("Air Quality     ");
  lcd.setCursor(0, 1); lcd.print("Monitoring      ");
  delay(1500); resetLCD();
  lcd.setCursor(0, 0); lcd.print("System          ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(1500); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Project by      ");
  lcd.setCursor(0, 1); lcd.print("Sanaullah Shovon");
  delay(1500); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Jannatul Mim    ");
  lcd.setCursor(0, 1); lcd.print("Abdur Rahman    ");
  delay(1500); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Jubaiya Moushi &");
  lcd.setCursor(0, 1); lcd.print("Kazi Amir Hamza ");
  delay(1500); resetLCD(); delay(2000);

}

void loop() {

  // tone(buzzer, 1500); delay(1000);
  // noTone(buzzer);  delay(1000);

  if(f==0){
    // digitalWrite(mq135LED, HIGH); delay(500);
    digitalWrite(mq135LED, LOW);
    // digitalWrite(mq9LED, HIGH); delay(500);
    digitalWrite(mq9LED, LOW);
    // digitalWrite(mq2LED, HIGH); delay(500);
    digitalWrite(mq2LED, LOW);

    for(int i = 0; i<5; i++){
      tone(buzzer, 1500); delay(1000); 
      noTone(buzzer); delay(1000);
    }
    f=1;
  }

  digitalWrite(mq135LED, HIGH);
  digitalWrite(mq9LED, HIGH);
  digitalWrite(mq2LED, HIGH);
  // noTone(buzzer);
  tone(buzzer, 1500); 

  lcd.setCursor(0, 0);
  lcd.print("Monitoring...   ");
  delay(1000); resetLCD();
  int n, m, o;
  while(1){
    m = analogRead(A0);
    Serial.print("MQ-135: "); Serial.println(m);
    n = analogRead(A1);
    Serial.print("MQ-9: "); Serial.println(n);
    o = analogRead(A2);
    Serial.print("MQ-2: "); Serial.println(o);

    if(m<mx135 && n<mx9 && o<mx2){
      digitalWrite(mq135LED, HIGH);
      digitalWrite(mq9LED, HIGH);
      digitalWrite(mq2LED, HIGH);
      // tone(buzzer, 1500);
      noTone(buzzer); 
      break;
    }

    check_condition(m, n, o);
    // check_condition(100, 0, 0);


    lcd.setCursor(0, 0);
    lcd.print("MQ-135"); lcd.setCursor(6, 0);  lcd.print(": "); lcd.setCursor(8, 0);
    lcd.print(m); lcd.setCursor(12, 0); lcd.print(" ppm");

    check_condition(m, n, o);

    if(m>=mx135){
      lcd.setCursor(0, 1); lcd.print("CO2, NH3 or     "); delay(2000);
      lcd.setCursor(0, 1); lcd.print("                "); delay(500);
      lcd.setCursor(0, 1); lcd.print("smoke detected. "); delay(2000);
      resetLCD();
    }
    else{
      lcd.setCursor(0, 1); lcd.print("                "); delay(2000); resetLCD();
    }

    m = analogRead(A0);
    Serial.print("MQ-135: "); Serial.println(m);
    n = analogRead(A1);
    Serial.print("MQ-9: "); Serial.println(n);
    o = analogRead(A2);
    Serial.print("MQ-2: "); Serial.println(o);

    check_condition(m, n, o);

    lcd.setCursor(0, 0);
    lcd.print("MQ-9"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
    lcd.print(n); lcd.setCursor(10, 0); lcd.print(" ppm  ");

    check_condition(m, n, o);
    if(n>=mx9){
      lcd.setCursor(0, 1); lcd.print("Carbon monoxide "); delay(2000);
      lcd.setCursor(0, 1); lcd.print("                "); delay(2000);
      lcd.setCursor(0, 1); lcd.print("or LPG detected."); delay(2000);
      resetLCD();
    }
    else{
      lcd.setCursor(0, 1); lcd.print("                "); delay(2000); resetLCD();
    }
    check_condition(m, n, o);

    m = analogRead(A0);
    Serial.print("MQ-135: "); Serial.println(m);
    n = analogRead(A1);
    Serial.print("MQ-9: "); Serial.println(n);
    o = analogRead(A2);
    Serial.print("MQ-2: "); Serial.println(o);

    lcd.setCursor(0, 0);
    lcd.print("MQ-2"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
    lcd.print(o); lcd.setCursor(10, 0); lcd.print(" ppm  ");
    
    check_condition(m, n, o);

    if(o>=mx2){
      lcd.setCursor(0, 1); lcd.print("Flamable Gas or "); delay(2000);
      lcd.setCursor(0, 1); lcd.print("                "); delay(2000);
      lcd.setCursor(0, 1); lcd.print("Smoke detected. "); delay(2000);
      resetLCD();
    }
    else{
      lcd.setCursor(0, 1); lcd.print("                "); delay(2000); resetLCD();
    }

    check_condition(m, n, o);

  }

  lcd.setCursor(0, 0);
  lcd.print("MQ-135"); lcd.setCursor(6, 0);  lcd.print(": "); lcd.setCursor(8, 0);
  lcd.print(m); lcd.setCursor(12, 0); lcd.print(" ppm");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(2000); resetLCD();
  lcd.setCursor(0, 0);
  lcd.print("MQ-9"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
  lcd.print(n); lcd.setCursor(10, 0); lcd.print(" ppm  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(2000); resetLCD();
  lcd.setCursor(0, 0);
  lcd.print("MQ-2"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
  lcd.print(o); lcd.setCursor(10, 0); lcd.print(" ppm  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(2000); resetLCD();

  resetLCD();
  lcd.print("Reading Temp    ");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temp: "); Serial.print(t); Serial.print(" *C\n");
  Serial.print("Humi: "); Serial.print(h); Serial.print(" %\n");
  resetLCD(); delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0); lcd.print(t); lcd.setCursor(13, 0); lcd.print("*C  ");
  delay(2000); resetLCD(); delay(1500);
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");

  lcd.setCursor(10, 0); lcd.print(h);  lcd.print("%   ");
  delay(2000); resetLCD(); delay(1500);

  digitalWrite(mq135LED, LOW);
  digitalWrite(mq9LED, LOW);
  digitalWrite(mq2LED, LOW);
}


