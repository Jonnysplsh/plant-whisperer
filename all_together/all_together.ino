/*
   Bas on Tech
   This course is part of the courses on https://arduino-tutorials.net
   (c) Copyright 2020 - Bas van Dijk / Bas on Tech
   This code and course is copyrighted. It is not allowed to use these courses commercially
   without explicit written approval
   YouTube:    https://www.youtube.com/c/BasOnTech
   Facebook:   https://www.facebook.com/BasOnTechChannel
   Instagram:  https://www.instagram.com/BasOnTech
   Twitter:    https://twitter.com/BasOnTech

*/

const int OUT_PIN = 2;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;


// CO2 SENSOR Definitions
const int pwmpin = 4;
const int range = 7000;


// LCD Panel Definitions
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//These 5 arrays paint the bars that go across the screen.
byte zero[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte one[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

byte two[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};

byte three[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};

byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  Serial.begin(9600);
  pinMode(pwmpin, INPUT);

  // initialize the LCD and allocate the 5 arrays to a number.
  lcd.begin(16, 2);
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
}

int readCO2PWM() {

  unsigned long th;
  int ppm_pwm = 0;
  float pulsepercent;


  do {

    th = pulseIn(pwmpin, HIGH, 2500000) / 1000;

    float pulsepercent = th / 1004.0;

    ppm_pwm = range * pulsepercent;

  } while (th == 0);


  return ppm_pwm;
}

void loop() {

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;
  int ppm_pwm_2 = readCO2PWM();
  Serial.println(ppm_pwm_2);


  //
//  if (digitalRead(OUT_PIN) == HIGH) {
//    sampleBufferValue++;
//    //      Serial.println(ppm_pwm_2);
//
//    if (millisElapsed > SAMPLE_TIME) {
//      //      Serial.println(ppm_pwm_2);
//
//      Serial.println(sampleBufferValue);
//      sampleBufferValue = 0;
//
//      millisLast = millisCurrent;
//    }
//  }


  //  int ppm_pwm = readCO2PWM();

  //  Serial.print("PPM PWM: ");
  //  Serial.println(ppm_pwm);

  //    delay(1000);

};

void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn)
{
  double factor = totalCount / 80.0;        //See note above!
  int percent = (count + 1) / factor;
  int number = percent / 5;
  int remainder = percent % 5;
  if (number > 0)
  {
    lcd.setCursor(number - 1, lineToPrintOn);
    lcd.write(5);
  }

  lcd.setCursor(number, lineToPrintOn);
  lcd.write(remainder);
}
