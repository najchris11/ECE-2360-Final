//ECE 2360 Final - Christian Coulibaly and Emmanuel Key
#include <LiquidCrystal.h>  // include the library code
#include "DHT.h"
/**********************************************************/
#define DHTPIN 4       // Set the pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int redPin = 7;         // R petal on RGB LED module connected to digital pin 7
const int greenPin = 6;       // G petal on RGB LED module connected to digital pin 6
const int bluePin = 5;        // B petal on RGB LED module connected to digital pin 5
const int photocellPin = A0;  //photoresistor attach to A0
const int buttonPin = 3;      //the button connect to pin 3
const int buzzerPin = 16;     //the button connect to pin 16
int sensorValue = 0;          // value read from the sensor
int buttonState = 0;          // variable for reading the pushbutton status
/*********************************************************/
void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(photocellPin, INPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  lcd.begin(16, 2);    // set up the LCD's number of columns and rows:
  Serial.begin(9600);  //set the baud bit to 9600bps
  dht.begin();
}
/*********************************************************/
void loop() {
  sensorValue = analogRead(photocellPin);  //read the value of A0
  //read the state of the button value
  buttonState = digitalRead(buttonPin);
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    Alarm();  //Triggers the Buzzer if the humidity sensor fails.
    return;
  }
  // Adjust the color of the RGB LED based on temperature
  if (temperature >= 30.0) { // Hot temperature threshold
    setColor(255, 0, 0);     // Red
  } else if (temperature >= 27.5) { // Hotter than warm
    int red = map(temperature, 27.5, 30, 255, 0);
    int green = map(temperature, 27.5, 30, 0, 255);
    setColor(red, green, 0); // Orange-yellowish
  } else if (temperature >= 25.0) { // Warm temperature threshold
    int red = map(temperature, 25, 27.5, 255, 0);
    int green = map(temperature, 25, 27.5, 0, 255);
    setColor(red, green, 0); // Orange-yellowish
  } else if (temperature <= 20.0) { // Cold temperature threshold
    setColor(0, 0, 255);           // Blue
  } else if (temperature <= 22.5) { // Cooler than cool
    int blue = map(temperature, 20, 22.5, 255, 0);
    int green = map(temperature, 20, 22.5, 0, 255);
    setColor(0, green, blue); // Cyan
  } else if (temperature <= 25.0) { // Cool temperature threshold
    int blue = map(temperature, 22.5, 25, 255, 0);
    int green = map(temperature, 22.5, 25, 0, 255);
    setColor(0, green, blue); // Cyan
  } else { // Moderate temperature
    setColor(0, 255, 0);           // Green
  }

  // DISPLAY DATA
  lcd.setCursor(0, 0);
  lcd.print("Hum:");
  lcd.print(humidity, 1);  //print the humidity on lcd
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Light:");
  lcd.print(sensorValue, 1);  //print the brightness on lcd
  lcd.print("/1024   ");
  delay(200);  //wait a while
}
/************************************************************/
//buzzer sound
void Alarm() {
  for (int i = 0; i < 100; i++) {
    digitalWrite(buzzerPin, HIGH);  //the buzzer sound
    delay(2);
    digitalWrite(buzzerPin, LOW);  //without sound
    delay(2);                      //when delay time changed,the frequency changed
  }
}
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}