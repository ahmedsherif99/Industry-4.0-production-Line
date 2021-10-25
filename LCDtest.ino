/* Basic Arduino example code for displaying text on 16x2, 20x4 etc. character LCDs. More info: www.makerguides.com */

// Include the library:
#include <LiquidCrystal.h>

// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

void setup() {
  // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4 LCD:
  lcd.begin(16, 2);
// lcd.print("scrollDisplayLeft() example");
}

void loop() {
 /* // Set the cursor on the third column and the first row, counting starts at 0:
  lcd.setCursor(2, 0);
  // Print the string 'Hello World!':
  lcd.print("Hello World!");
  // Set the cursor on the third column and the second row:
  lcd.setCursor(2, 1);
  // Print the string 'LCD tutorial':
  lcd.print("LCD tutorial");
  */
  int x= millis();
  while(millis()-x<5000){
  lcd.setCursor(2,0);
      lcd.print("Nonmetal in feeding");
        lcd.setCursor(2,1);
        lcd.print("metal in feeding");
        lcd.setCursor(0,0);
  lcd.scrollDisplayLeft();
  delay(600);
  }
  lcd.clear();
}
