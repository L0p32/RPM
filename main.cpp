#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

#define hall 2

float rps;
float rpm;
volatile byte pulsos;
unsigned long timeold;
unsigned long timereport;

void contador(){
  pulsos++;
}

void setup() {
  pinMode(hall, INPUT);

  lcd.begin(16,2);
  lcd.clear();

  attachInterrupt(0, contador, RISING);

  pulsos = 0;
  rpm = 0;
  rps = 0;
  timeold = 0;
}

void loop() {
  if (pulsos>=1){
    detachInterrupt(hall);
    rpm = (60000.0/ (millis()-timeold)*pulsos)/4;
    rps = rpm/60.0;
    timeold = millis();
    pulsos=0;
    if(millis()-timereport >= 100){
    lcd.setCursor(0,1);
    lcd.print(rpm);
    timereport = millis();
    }
    attachInterrupt(0, contador, RISING);

    /*if(millis()-timereport >= 500){
    lcd.setCursor(0,1);
    lcd.print(rpm);
    timereport = millis();
    }*/
  }
}