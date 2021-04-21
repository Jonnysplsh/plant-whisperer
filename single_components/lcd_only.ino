/*
 * Simple progress bar to show the progress of time or other suitable count.
 * 
 */



//Including these 2 libraries as these work with my LCD, which is an I2C LCD.
//If your LCD is different, change the code accordingly.
#include <Wire.h> 
#include <LiquidCrystal.h>

// Set the LCD address to 0x27 (or 0x3F) for a 16 chars and 2 line display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//LiquidCrystal_I2C lcd(0x27, 20, 4);       //If using a 20 x 4 display, uncomment this line and comment out the line above


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


  // initialize the LCD and allocate the 5 arrays to a number.
  lcd.begin(16, 2);
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);

}

//This simple loop code prints a number from 0 to 100 on the top line and displays the progress bar on the bottom line.
// The loop counts up, pauses for 1 second, then counts down again.
void loop() {
  for(int i=0; i <= 100; i++)
  {
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1);   //This line calls the subroutine that displays the progress bar.  The 3 arguments are the current count, the total count and the line you want to print on.
    delay(200);
  }
  delay(1000);
  for(int i=100; i >= 0; i--)
  {
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1);    //This line calls the subroutine that displays the progress bar.  The 3 arguments are the current count, the total count and the line you want to print on.
    delay(50);
  }
  delay(1000);
}


/*
 * This is the method that does all the work on the progress bar.
 * Please feel free to use this in your own code.
 * @param count = the current number in the count progress
 * @param totalCount = the total number to count to
 * @param lineToPrintOn = the line of the LCD to print on.
 * 
 * Because I am using a 16 x 2 display, I have 16 characters.  Each character has 5 sections.  Therefore, I need to declare the number 80.0.
 * If you had a 20 x 4 display, you would have 25 x 5 = 100 columns.  Therefore you would change the 80.0 to 100.0
 * You MUST have the .0 in the number.  If not, it will be treated as an int and will not calculate correctly
 * 
 * The factor is the totalCount/divided by the number of columns.
 * The percentage is the count divided by the factor (so for 80 columns, this will give you a number between 0 and 80)
 * the number gives you the character number (so for a 16 x 2 display, this will be between 0 and 16)
 * the remainder gives you the part character number, so returns a number between 0 and 4
 * 
 * Based on the number and remainder values, the appropriate character is drawn on the screen to show progress.
 * This only works for a steady count up or down.  This will not work as is for fluctuating values, such as from an analogue input.
 */
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