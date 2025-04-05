#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // Auto-calibrate gyroscope
}

void loop() {
  mpu6050.update();

  Serial.println("=== MPU6050 Data ===");
  Serial.print("Temperature: "); Serial.print(mpu6050.getTemp()); Serial.println(" °C");

  Serial.print("AccX: "); Serial.print(mpu6050.getAccX());
  Serial.print(" | AccY: "); Serial.print(mpu6050.getAccY());
  Serial.print(" | AccZ: "); Serial.println(mpu6050.getAccZ());

  Serial.print("GyroX: "); Serial.print(mpu6050.getGyroX());
  Serial.print(" | GyroY: "); Serial.print(mpu6050.getGyroY());
  Serial.print(" | GyroZ: "); Serial.println(mpu6050.getGyroZ());

  Serial.println("======================");
  delay(1000);
}
