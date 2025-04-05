#include <FreqMeasure.h>

void setup() {
  Serial.begin(9600);
  FreqMeasure.begin(); // Start frequency measurement
}

void loop() {
  if (FreqMeasure.available()) {
    float frequency = FreqMeasure.read(); // Read frequency
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");
  }
  delay(500);
}
