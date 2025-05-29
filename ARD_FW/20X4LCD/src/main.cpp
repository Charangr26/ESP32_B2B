#include <Arduino.h>
#include <LiquidCrystal.h>

// Pin mapping: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(21, 22, 18, 19, 23, 5);

void setup() {
  lcd.begin(20, 4);       // 20 columns, 4 rows
  lcd.setCursor(0, 0);    // column 0, row 
  lcd.print("Hello, Guys!");
  lcd.setCursor(0, 1);    // column 0, row 1
  lcd.print("I'm Gurucharan.G.R");
  lcd.setCursor(0, 2);    // column 0, row 1
  lcd.print("Let's connect and");
  lcd.setCursor(0, 3);    // column 0, row 1
  lcd.print("      grow....");
}

void loop() {
  // You can update text here
}
