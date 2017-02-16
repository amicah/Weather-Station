/* Cal Poly Pomona Robotics Club
 * Weather Station Workshop
 * February 11, 2017
 */

// Libraries
#include <DHT.h> // Digital Humidity/Temperature Sensor Library
#include<LiquidCrystal.h> // LCD Screen Library

// Definitions
#define soilPin A0 // Soil Probe input set to Analog 0
#define dhtPin A1 // DHT input set to Analog 1
#define dhtType DHT11 // Type of DHT being used
#define lowMoisture 300 // "Dry" value read by soilPin - May need adjusting
#define medMoisture 700 // "Damp" value
#define highMoisture 950 // "Wet" value

// Objects
DHT dht(dhtPin, dhtType); // DHT object named dht
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Connected to LCD Pins (4, 6, 11, 12, 13, 14)

void setup() {
  dht.begin(); // Initialize DHT
  lcd.begin(16, 2); // Initialize LCD -> 16 Columns (0-15), 2 Rows (0-1)
  // Begin "Welcome Message"
  lcd.setCursor(0, 0); // Set intial position to print on LCD -> (Column, Row)
  lcd.print("Robotics Club");
  lcd.setCursor(0, 1);
  lcd.print("Weather Station");
  delay(3000); // 3 second delay
  lcd.clear();
  // End "Welcome Message"
}

void loop() {
  float temperature = dht.readTemperature(true); // Read Temperature: false -> Celsius, true -> Farenheit
  float humidity = dht.readHumidity(); // Read Humidity
  int soilMoisture = analogRead(soilPin); // Read Moisture Level from soilPin
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(4, 0);
  lcd.print((char)223); // Print the 'degree' character
  lcd.setCursor(5, 0);
  // Print C for Celsius or F for Farenheit
  lcd.print("F");
  lcd.setCursor(11, 0);
  lcd.print(humidity);
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);  
  if(soilMoisture < lowMoisture) {
    lcd.print("Soil is dry."); // Too little water
  }
  if((soilMoisture >= lowMoisture) && (soilMoisture < medMoisture)) {
    lcd.print("Soil is damp."); // Good amount of water
  }
  if((soilMoisture >= medMoisture) && (soilMoisture < highMoisture)) {
    lcd.print("Soil is wet."); // Too much water
  }
  delay(2000); // 2 second delay
}
