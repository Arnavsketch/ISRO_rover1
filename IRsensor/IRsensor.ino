const int irSensorPin = 9; // IR sensor connected to pin 9

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int irValue = digitalRead(irSensorPin); // Read IR sensor value
  if (irValue == LOW) {
    Serial.println("Object Detected!");
  } else {
    Serial.println("No Object.");
  }
  delay(500);
}
