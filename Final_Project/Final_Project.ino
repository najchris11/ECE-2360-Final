//Starting point is the Sunfounder LCD Program
#include <LiquidCrystal.h>// include the library code
#include "DHT.h"
/**********************************************************/
#define DHTPIN 4       // Set the pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
char array1[]=" SunFounder               ";  //the string to print on the LCD
char array2[]="hello, world!             ";  //the string to print on the LCD
int tim = 250;  //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int redPin = 7;  // R petal on RGB LED module connected to digital pin 11 
const int greenPin = 6;  // G petal on RGB LED module connected to digital pin 10 
const int bluePin = 5;  // B petal on RGB LED module connected to digital pin 9 
const int photocellPin = A0;  //photoresistor attach to A0
int sensorValue = 0;        // value read from the sensor
/*********************************************************/
void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
}
/*********************************************************/
void loop() 
{
    lcd.setCursor(15,0);  // set the cursor to column 15, line 0
    for ( int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    lcd.clear();  //Clears the LCD screen.
    lcd.setCursor(15,1);  // set the cursor to column 15, line 1
    for (int positionCounter2 = 0; positionCounter2 < 26; positionCounter2++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array2[positionCounter2]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
}
/************************************************************/
