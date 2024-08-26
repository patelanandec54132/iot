// Pin for IR sensor signal
const int irPin = D2;

void setup() {
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set IR sensor pin as input
  pinMode(irPin, INPUT);
}

void loop() {
  // Read the value from the IR sensor
  int sensorValue = digitalRead(irPin);

  // Display the sensor value in the serial monitor
  if (sensorValue == LOW) {
    Serial.println("Object Detected");
  } else {
    Serial.println("No Object Detected");
  }

  // Small delay to make the output readable
  delay(200);
}
