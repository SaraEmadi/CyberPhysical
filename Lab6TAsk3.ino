#include <Wire.h>  // For I2C communication

// MPU6050 I2C address (most common)
const uint8_t MPU6050_ADDR = 0x68;

// Fan PWM pin
const int FAN_PIN = 9;

void mpu6050_init() {
  Wire.begin();
  // Wake up MPU6050 (exit sleep mode)
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);      // PWR_MGMT_1 register
  Wire.write(0x00);      // Set to 0 -> wake up
  Wire.endTransmission();
}

int16_t read_gyro_y() {
  // Read two bytes from GYRO_YOUT_H and GYRO_YOUT_L
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x45);  // GYRO_YOUT_H register
  Wire.endTransmission(false);

  Wire.requestFrom(MPU6050_ADDR, (uint8_t)2);
  while (Wire.available() < 2) {
    // wait
  }

  int16_t highByte = Wire.read();
  int16_t lowByte  = Wire.read();
  int16_t value    = (highByte << 8) | lowByte;

  return value;
}

float gyro_raw_to_dps(int16_t raw) {
  // Assuming default full scale ±250 °/s => 131 LSB/(°/s)
  return (float)raw / 131.0;
}

void set_fan_speed(float angular_velocity_dps) {
  int pwm_value = 0;

  if (angular_velocity_dps >= 0 && angular_velocity_dps <= 30) {
    // OFF
    pwm_value = 0;
  } else if (angular_velocity_dps > 30 && angular_velocity_dps <= 100) {
    // LOW
    pwm_value = 85;
  } else if (angular_velocity_dps > 100 && angular_velocity_dps <= 200) {
    // MEDIUM
    pwm_value = 170;
  } else if (angular_velocity_dps > 200) {
    // HIGH
    pwm_value = 255;
  }

  analogWrite(FAN_PIN, pwm_value);
}

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 0); // Start with fan off

  Wire.begin();
  mpu6050_init();

  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial on some boards
  }

  Serial.println("CPS Fan Control using MPU6050 initialized");
}

void loop() {
  int16_t gyro_y_raw = read_gyro_y();
  float gyro_y_dps = gyro_raw_to_dps(gyro_y_raw);

  set_fan_speed(gyro_y_dps);

  // Debug output
  Serial.print("Gyro Y: ");
  Serial.print(gyro_y_dps);
  Serial.println(" dps");

  delay(200);
}