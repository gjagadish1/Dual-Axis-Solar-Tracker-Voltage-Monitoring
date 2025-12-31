#include <Servo.h>

// Define the pin to which the dust sensor is connected
const int dustSensorPin = A1;

// Threshold for dust detection (adjust as needed)
const int dustThreshold = 4;  // Change this value based on your sensor's readings

// Define the pin to which the servo motor is connected
const int servoPin = 9;

// Create a Servo object
Servo myServo;

void setup() {
  // Attach the servo to the specified pin
  myServo.attach(servoPin);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  int ana_volt = analogRead(A2);
  int bat_volt = analogRead(A0);

  // Calculate the voltage values in Volts
  float voltage = ((ana_volt * 5.0) / 1023.0) * 2;   

  // Calculate battery voltage and percentage
  float bat_voltage = ((bat_volt * 5.0) / 1023.0) * 2 - 0.2;  // Convert to voltage (assuming 5V reference) the 0.13 is the calibrated value
  int bat_percentage = map(bat_voltage, 2.8, 4.2, 0, 100);  // Map battery voltage to percentage

  // Print both voltage and percentage on the same line
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V, Battery voltage: ");
  Serial.print(bat_voltage, 2);  // Print with 2 decimal places
  Serial.print("V, Battery percentage: ");
  Serial.print(bat_percentage);
  Serial.println("%");

  // Read the dust sensor value
  int dustValue = analogRead(dustSensorPin);

  // Print the dust value to the serial monitor
  Serial.print("Dust Value: ");
  Serial.println(dustValue);

  // Check if dust value exceeds the threshold
  if (dustValue > dustThreshold) {
    Serial.println("Dust detected!");

    // Rotate servo clockwise 2 times
    for (int i = 0; i < 2; i++) {
      rotateServoClockwise();
      delay(1000); // Adjust delay as needed
    }

    // Rotate servo counterclockwise 2 times
    for (int i = 0; i < 2; i++) {
      rotateServoCounterclockwise();
      delay(1000); // Adjust delay as needed
    }
  }

  delay(2000);
}

// Function to rotate the servo clockwise
void rotateServoClockwise() {
  for (int angle = 30; angle <= 130; angle++) {
    myServo.write(angle);
    delay(15); // Adjust speed of rotation
  }
}

// Function to rotate the servo counterclockwise
void rotateServoCounterclockwise() {
  for (int angle = 130; angle >= 30; angle--) {
    myServo.write(angle);
    delay(15); // Adjust speed of rotation
  }
}
