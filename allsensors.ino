#include <Adafruit_AM2315.h>

#include <Wire.h>
#include <FreqMeasure.h>
#include <NewPing.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MPU6050_tockn.h>

const int colorSensorS0 = 2;  // S0 pin of TCS3200
const int colorSensorS1 = 3;  // S1 pin of TCS3200
const int colorSensorS2 = 4;  // S2 pin of TCS3200
const int colorSensorS3 = 5;  // S3 pin of TCS3200
const int colorSensorOut = 6; // OUT pin of TCS3200
float frequency = 0;
const int echoPin = 7;
const int triggerPin = 8;
const int irSensorPin = 9;

NewPing ultrasonicSensor(triggerPin, echoPin);
OneWire oneWire(10);
DHT dhtSensor(11, DHT11);
DallasTemperature temperatureSensor(&oneWire);
MPU6050 mpu6050(Wire);

long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Configure color sensor pin modes
  pinMode(colorSensorS0, OUTPUT);
  pinMode(colorSensorS1, OUTPUT);
  pinMode(colorSensorS2, OUTPUT);
  pinMode(colorSensorS3, OUTPUT);
  pinMode(colorSensorOut, INPUT);

  // Configure IR sensor pin mode
  pinMode(irSensorPin, INPUT);

  // Start the DHT temperature sensor
  dhtSensor.begin();

  // Initialize temperature sensor
  temperatureSensor.begin();

  // Initialize the FreqMeasure library
  FreqMeasure.begin();

  // Set TCS3200 to high sensitivity (adjust based on your requirements)
  digitalWrite(colorSensorS0, HIGH);
  digitalWrite(colorSensorS1, HIGH);

  // Initialize MPU6050
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

// Function to read color from the TCS3200 sensor
void readColor() {
  // Set the filter for the color you want to detect (e.g., Red)
  digitalWrite(colorSensorS2, LOW);
  digitalWrite(colorSensorS3, LOW);

  // Read RGB values
  int red = pulseIn(colorSensorOut, LOW);
  Serial.print("Red: ");
  Serial.print(red);

  // Set the filter for the next color (e.g., Green)
  digitalWrite(colorSensorS2, HIGH);
  digitalWrite(colorSensorS3, HIGH);

  // Read RGB values
  int green = pulseIn(colorSensorOut, LOW);
  Serial.print(" | Green: ");
  Serial.print(green);

  // Set the filter for the next color (e.g., Blue)
  digitalWrite(colorSensorS2, LOW);
  digitalWrite(colorSensorS3, HIGH);

  // Read RGB values
  int blue = pulseIn(colorSensorOut, LOW);
  Serial.print(" | Blue: ");
  Serial.println(blue);
}

void loop() {
  // Read frequency using FreqMeasure library
  if (FreqMeasure.available()) {
    frequency = FreqMeasure.read();
  }

  // Print the frequency data
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  // Read distance from HC-SR04
  unsigned int distance = ultrasonicSensor.ping_cm();

  // Print the distance data
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read IR sensor data
  int irValue = digitalRead(irSensorPin);

  // Print the IR sensor data
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  // Read color sensor data
  readColor();

  // Read gyroscope data from MPU6050
  mpu6050.update();

  if (millis() - timer > 1000) {

    Serial.println("=======================================================");
    Serial.print("temp : "); Serial.println(mpu6050.getTemp());
    Serial.print("accX : "); Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : "); Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : "); Serial.println(mpu6050.getAccZ());

    Serial.print("gyroX : "); Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : "); Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : "); Serial.println(mpu6050.getGyroZ());

    Serial.print("accAngleX : "); Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : "); Serial.println(mpu6050.getAccAngleY());

    Serial.print("gyroAngleX : "); Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : "); Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : "); Serial.println(mpu6050.getGyroAngleZ());

    Serial.print("angleX : "); Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : "); Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : "); Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    timer = millis();
  }

  // Read temperature and humidity data from DHT11
  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();

  // Print the temperature and humidity data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Read temperature sensor data
  temperatureSensor.requestTemperatures();
  float temperatureCelsius = temperatureSensor.getTempCByIndex(0);

  // Print the temperature sensor data
  //Serial.print("Temperature: ");
  //Serial.print(temperatureCelsius);
  //Serial.println(" °C");

  delay(2000);  // Add a delay to control the output rate (2 seconds)
}