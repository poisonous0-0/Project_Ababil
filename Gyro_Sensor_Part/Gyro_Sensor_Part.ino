#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo servoY;
Servo servoZ;

const int servoPinY = 9; // Servo pin for Y-axis control
const int servoPinZ = 10; // Servo pin for Z-axis control

int angleY = 90; // Initial Y-axis angle
int angleZ = 90; // Initial Z-axis angle

void setup() {
  Serial.begin(115200);
  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Attach the servos
  servoY.attach(servoPinY);
  servoZ.attach(servoPinZ);

  // Set initial servo positions
  servoY.write(angleY);
  servoZ.write(angleZ);
}

void loop() {
  int16_t gyroX, gyroY, gyroZ;

  // Read the raw gyro values for all three axes
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);

  // Proportional gain for controlling the servo based on gyro input
  float kp = 0.1;
  
  int deltaY = gyroY * kp;
  int deltaZ = gyroZ * kp;

  // Update the current angles based on the change
  angleY = constrain(angleY + deltaY, 0, 180);
  angleZ = constrain(angleZ + deltaZ, 0, 180);

  // Update servo positions
  servoY.write(angleY);
  servoZ.write(angleZ);

  delay(100); // Adjust the delay for more frequent updates
}
