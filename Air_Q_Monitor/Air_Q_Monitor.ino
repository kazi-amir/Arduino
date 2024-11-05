#include<SPI.h>
#include<Wire.h>

//DHT11 (Temperature and Humidity)
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//  for DHT11,
//  VCC: 5V or 3V
//  GND: GND
//  Data: 2 (digital)






//LCD Display
#include<LiquidCrystal.h>
const int rs = 7, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void resetLCD(){
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(1000);
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); lcd.print("Hello World!    ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(1500); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Air Quality     ");
  lcd.setCursor(0, 1); lcd.print("Monitoring      ");
  delay(3000); resetLCD();
  lcd.setCursor(0, 0); lcd.print("System          ");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(3000); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Project by      ");
  lcd.setCursor(0, 1); lcd.print("Sanaullah Shovon");
  delay(3000); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Jannatul Mim    ");
  lcd.setCursor(0, 1); lcd.print("Abdur Rahman    ");
  delay(3000); resetLCD();
  lcd.setCursor(0, 0); lcd.print("Jubaiya Moushi &");
  lcd.setCursor(0, 1); lcd.print("Kazi Amir Hamza ");
  delay(4000); resetLCD(); delay(2000);

  Serial.begin(9600);

  //Gas sensors
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  //Temp and Humidity
  dht.begin();

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Monitoring...   ");
  delay(2000); resetLCD();
  int m = analogRead(A0);
  Serial.print("MQ-135: ");
  Serial.println(m);
  lcd.setCursor(0, 0);
  lcd.print("MQ-135"); lcd.setCursor(6, 0);  lcd.print(": "); lcd.setCursor(8, 0);
  lcd.print(m); lcd.setCursor(12, 0); lcd.print(" ppm");
  lcd.setCursor(0, 1);
  if(m<400){
    lcd.print("Air is Normal.. ");
  }else{
    lcd.print("Gas detected..  ");
  }
  delay(4000);
  resetLCD();
  int n = analogRead(A1);
  Serial.print("MQ-9: ");
  Serial.println(n);
  lcd.setCursor(0, 0);
  lcd.print("MQ-9"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
  lcd.print(n); lcd.setCursor(10, 0); lcd.print(" ppm  ");
  lcd.setCursor(0, 1);
  if(n<=400){
    lcd.print("Air is Normal.. ");
  }else{
    lcd.print("Gas detected..  ");
  }
  delay(4000);
  resetLCD();
  delay(2000);
  int o = analogRead(A2);
  Serial.print("MQ-2: ");
  Serial.println(o);
  lcd.setCursor(0, 0);
  lcd.print("MQ-2"); lcd.setCursor(4, 0);  lcd.print(": "); lcd.setCursor(6, 0);
  lcd.print(o); lcd.setCursor(10, 0); lcd.print(" ppm  ");
  lcd.setCursor(0, 1);
  if(o<=400){
    lcd.print("Air is Normal.. ");
  }else{
    lcd.print("Gas detected..  ");
  }
  delay(4000);
  resetLCD();
  lcd.setCursor(0, 0);
  lcd.print("Reading Temp..    ");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temp: "); Serial.print(t); Serial.print(" *C\n");
  Serial.print("Humi: "); Serial.print(h); Serial.print(" %\n");
  while(isnan(h) || isnan(t)){
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.print("Temp: "); Serial.print(t); Serial.print(" *C");
    Serial.print("Humi: "); Serial.print(h); Serial.print(" %");
  }
  resetLCD();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0); lcd.print(t); lcd.setCursor(13, 1); lcd.print("°C  ");
  delay(4000); resetLCD(); delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");

  lcd.setCursor(10, 0); lcd.print(h);  lcd.print("%   ");
  // lcd.setCursor(0, 1); lcd.print(h); lcd.setCursor(5, 1); lcd.print(" %          ");
  delay(4000); resetLCD(); delay(2000);
}
