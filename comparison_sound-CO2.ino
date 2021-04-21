/* Definitions */

// SOUND SENSOR Definitions
const int OUT_PIN = 8;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

// CO2 SENSOR Definitions
const int pwmpin = 7;
const int range = 5000;

// LCD Panel Definitions
#include <Wire.h> 
#include <LiquidCrystal.h>

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

    pinMode(pwmpin, INPUT);
    Serial.begin(9600)

// initialize the LCD and allocate the 5 arrays to a number.
    lcd.begin(16, 2);
    lcd.createChar(0, zero);
    lcd.createChar(1, one);
    lcd.createChar(2, two);
    lcd.createChar(3, three);
    lcd.createChar(4, four);
    lcd.createChar(5, five);
}



void loop() {

  // __SOUND SENSOR
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

    if (digitalRead(OUT_PIN) == HIGH) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }


  // __CO2 SENSOR
  int ppm_pwm = readCO2PWM();
  
  Serial.print("PPM PWM: ");
  Serial.println(ppm_pwm);

  delay(3000);


  // __ LCD SCREEN
  for(int i=0; i <= 100; i++)
  {
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1); 
    delay(200);
  }
  delay(1000);
  for(int i=100; i >= 0; i--)
  {
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1);   
    delay(50);
  }
  delay(1000);
}


// __ MAIN FUNCTION
if (sampleBufferValue > 50 && ppm_pwm > 800){}

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

//LCD Screen
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn)
 {
    double factor = totalCount/80.0;          //See note above!
    int percent = (count+1)/factor;
    int number = percent/5;
    int remainder = percent%5;
    if(number > 0)
    {
       lcd.setCursor(number-1,lineToPrintOn);
       lcd.write(5);
    }
   
       lcd.setCursor(number,lineToPrintOn);
       lcd.write(remainder);   
 }