#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions for Ultrasonic Sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// Pin definitions for LEDs
#define RED_LED_PIN 11
#define YELLOW_LED_PIN 12

// Tank and sensor configuration
const int containerHeight = 13;  // Height of the container (in cm)
const int sensorOffset = 4;     // Distance of the sensor from the maximum water level (in cm)

// Create LCD object with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to get filtered distance from the ultrasonic sensor
long getFilteredDistance() {
  long totalDistance = 0;
  int numReadings = 10;  // Increase the number of readings to average for better stability
  for (int i = 0; i < numReadings; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = (duration / 2) * 0.0344;  // Calculate the distance
    totalDistance += distance;
    delay(10);  // Short delay between readings
  }
  return totalDistance / numReadings;  // Return the average distance
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes for Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set pin modes for LEDs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  // Initialize LCD
  lcd.begin(16,5);
  lcd.print("Intializing");
  lcd.backlight();  // Turn on LCD backlight
  delay(2000);  // Wait to display initial message
}

void loop() {
  long distance = getFilteredDistance();

  // Calculate water level
  int waterLevel = containerHeight + sensorOffset - distance;
  if (waterLevel > containerHeight) waterLevel = containerHeight;
  if (waterLevel < 0) waterLevel = 0;

  // Calculate percentage
  int percentage = map(waterLevel, 0, containerHeight, 0, 100);
  if (waterLevel <= 0) {
    percentage = 0;
  } else if (waterLevel >= containerHeight) {
    percentage = 100;
  }

  // Debugging output
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Water Level: ");
  Serial.print(waterLevel);
  Serial.print(" cm, Percentage: ");
  Serial.println(percentage);

  // Display percentage on LCD
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Water Level:");
  lcd.print(percentage);
  lcd.print("%");

  // Control LEDs based on water level percentage
  if (percentage >= 90) {
    // Both Red and Yellow LEDs turn ON
    digitalWrite(RED_LED_PIN, HIGH);   // Red LED ON
    digitalWrite(YELLOW_LED_PIN, LOW); // Yellow LED ON
  } else if (percentage >= 70) {
    // Only Yellow LED turns ON
    digitalWrite(RED_LED_PIN, LOW);    // Red LED OFF
    digitalWrite(YELLOW_LED_PIN, HIGH); // Yellow LED ON
  } else {
    // Both LEDs turn OFF
    digitalWrite(RED_LED_PIN, LOW);    // Red LED OFF
    digitalWrite(YELLOW_LED_PIN, LOW); // Yellow LED OFF
  }

  // Wait for 1 second before next measurement
  delay(1000);
}
