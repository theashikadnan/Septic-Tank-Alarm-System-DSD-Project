#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQ2.h>

#define trigPin 7
#define echoPin 6
#define gassSensor A0
#define redLed 4
#define greenLed 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
MQ2 mq2(gassSensor);

long duration;
int distanceCm;
int lpg;
int co = 10;
int smoke;

void setup(){
  
	lcd.begin();
  lcd.backlight();
  mq2.begin();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);	

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  
}

void loop(){
  
    float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
    //lpg = values[0];
    lpg = mq2.readLPG();
    //co = values[1];
    //co = mq2.readCO();
    //smoke = values[2];
    smoke = mq2.readSmoke();
  
	  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceCm= duration*0.034/2; 
    
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.print(distanceCm);
    lcd.print(" cm");

    lcd.setCursor(0,1);
//    lcd.print("LPG: ");
//    lcd.print(lpg);
//    lcd.print(", ");
    lcd.print("CO: ");
    lcd.print(co);
    lcd.print(", ");
    lcd.print("Smoke: ");
    lcd.print(smoke);

    lcd.setCursor(0,2);

    if(distanceCm>300){
      lcd.print("NOT SAFE DISTANCE TO GO");
      }

    if(distanceCm<300){
      lcd.print("SAFE DISTANCE TO GO");
      }
      
    lcd.setCursor(0,3);
    
    if(co>9){
      lcd.print("HARMFUL GASS FOUND");
      }

    if(co<9){
      lcd.print("SAFE GASS DETECTED");
      }

    if(distanceCm<300 && co<9){
      digitalWrite(greenLed, HIGH);
      delay(100);
      digitalWrite(greenLed, LOW);
      delay(10);
      }
    else{
      digitalWrite(redLed, HIGH);   
      delay(100);                       
      digitalWrite(redLed, LOW);    
      delay(10); 
      }
    
}
