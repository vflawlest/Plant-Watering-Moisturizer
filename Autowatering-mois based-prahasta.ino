#include <Wire.h>  // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD with I2C interface

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int sensorPin = A0;  // Pin for soil moisture sensor
const int pumpPin = 8;     // Pin for pump relay

int moistureValue = 0;
int minMoisture = 65;  // Minimum moisture level for watering
int maxMoisture = 80;  // Maximum moisture level for watering

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  
  lcd.begin(16, 2);  // Initialize the LCD
  lcd.backlight();   // Turn on backlight
  lcd.setCursor(0,0);
  lcd.print("Moisture: ");
}

void loop() {
  moistureValue = analogRead(sensorPin);
  int moisturePercentage = map(moistureValue, 0, 1023, 0, 100);  // Map sensor value to percentage
  
  lcd.setCursor(10,0);
  lcd.print(moisturePercentage);
  lcd.print("%   ");
  
  if (moisturePercentage < minMoisture) {
    digitalWrite(pumpPin, HIGH);  // Turn on the pump
  } else if (moisturePercentage > maxMoisture) {
    digitalWrite(pumpPin, LOW);   // Turn off the pump
  }
  
  delay(1000);  // Delay for stability
}