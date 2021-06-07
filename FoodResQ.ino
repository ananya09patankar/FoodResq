#include<SoftwareSerial.h>
#include <Arduino.h>
#include<LiquidCrystal.h>

#define TOUCHPIN 2
#define FORCEPIN A0
#define ECHOPIN 12 
#define PINGPIN 13

LiquidCrystal lcd(4,5,6,7,8,9);


void setup() {

  Serial.begin(9600);
  lcd.begin(16,2);  
  lcd.print("Food ResQ System");
  delay(2000);
  lcd.clear();
  lcd.print("Initializing");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  delay(1000);
  pinMode(TOUCHPIN, INPUT);
  pinMode(FORCEPIN, INPUT);
  pinMode(PINGPIN, OUTPUT); 
  pinMode(ECHOPIN, INPUT);
  lcd.clear();
  lcd.print("Initialized");
  lcd.setCursor(0,1);
  lcd.print("Successfully");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  Serial.println("System Ready..");

}

void loop() {
  int fingerSensor = digitalRead(TOUCHPIN);
  int force;
  long duration, inches, cm;  
  digitalWrite(PINGPIN, LOW);
  delayMicroseconds(2);  
  digitalWrite(PINGPIN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(PINGPIN, LOW);
  
  duration = pulseIn(ECHOPIN, HIGH);
  cm = (duration/ 29 / 2);

  if(cm==4){
    lcd.clear();
    lcd.print("Dustbin is Full!");
    Serial.println("Dustbin is Full!");
    while(cm<=4){
      digitalWrite(PINGPIN, LOW);
      delayMicroseconds(2);  
      digitalWrite(PINGPIN, HIGH);
      delayMicroseconds(10);  
      digitalWrite(PINGPIN, LOW);
      duration = pulseIn(ECHOPIN, HIGH);
      cm = (duration/ 29 / 2);
    }
    lcd.clear();
    lcd.print("System Ready");
    Serial.println("System is ready..");
  }
  
  if(fingerSensor==1){
    lcd.clear();
    lcd.print("User Authenticated..");
    lcd.clear();
    Serial.println("User Authenticated..");

    while(fingerSensor==1 && cm>4){
      fingerSensor = digitalRead(TOUCHPIN);
      force = analogRead(FORCEPIN);
      lcd.print("Weight of Waste:");
      lcd.setCursor(6,1);
      lcd.print(force);
      lcd.setCursor(10,1);
      lcd.print("Kg");
      delay(500);
      lcd.clear();
      
    }

    Serial.print("Amount of food wasted: ");
    Serial.print(force);
    Serial.println("Kg");
    Serial.print("Fine charged: ");
    Serial.print(force * 2);
    Serial.println("Rs");
    lcd.setCursor(0,0);
    lcd.print("Fine :");
    lcd.setCursor(7,0);
    lcd.print(force * 2);
    lcd.setCursor(11,0);
    lcd.print("Rs");
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
    Serial.println("System is ready..");
       

  }
  
}
