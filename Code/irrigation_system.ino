#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 10
#define DHTTYPE DHT11

#define SOIL_MOISTURE_PIN A0
#define GREEN_LED 6
#define RED_LED 7
#define WATER_PUMP 9

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
DHT dht(DHTPIN, DHTTYPE);

bool pumpState = false;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(WATER_PUMP, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();

  lcd.setCursor(0, 0);
  String message1 = "Automated Plant";
  String message2 = "Watering System";

  for (int i = 0; i < message1.length(); i++) {
    lcd.print(message1.charAt(i));
    delay(100);
  }

  lcd.setCursor(0, 1);
  for (int i = 0; i < message2.length(); i++) {
    lcd.print(message2.charAt(i));
    delay(100);
  }

  delay(1500);
  lcd.clear();
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawMoisture = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercent = constrain(map(rawMoisture, 1024, 220, 0, 100), 0, 100);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Pump logic using moisture percentage
  if (moisturePercent < 30) { // Too dry
    pumpState = true;
  } else if (moisturePercent >= 50) { // Moist enough
    pumpState = false;
  }

  digitalWrite(WATER_PUMP, pumpState ? LOW : HIGH);  // Assuming LOW turns ON the pump
  digitalWrite(GREEN_LED, pumpState ? LOW : HIGH);
  digitalWrite(RED_LED, pumpState ? HIGH : LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moist:");
  lcd.print(moisturePercent);
  lcd.print("% T:");
  lcd.print(temperature, 1);

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 0);
  lcd.print("% Pump:");
  lcd.print(pumpState ? "ON " : "OFF");

  Serial.print("Raw Moisture: ");
  Serial.print(rawMoisture);
  Serial.print(" | Moisture %: ");
  Serial.println(moisturePercent);

  delay(2000);
}
