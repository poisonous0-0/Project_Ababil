// MQ2 Gas Sensor Test Code

// Define the analog pin the sensor is connected to
const int sensorPin = A0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);

  // Print the sensor value to the serial monitor
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);

  // A delay to make the output readable
  delay(500);
}
