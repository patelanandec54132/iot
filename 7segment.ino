/*
// Define the segment pins
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Connect to segments a, b, c, d, e, f, g
const int numSegments = 7;

// Define the digit patterns for 0-9
const byte digitPatterns[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

int sensorPin = 9; // Connected to pushbutton
int objectCount = 0; // Variable to store the count of objects detected
bool objectDetected = false; // Flag to track object detection
bool initialized = false; // Flag to check if initialization has occurred

void setup() {
  for (int i = 0; i < numSegments; i++) {
    pinMode(segmentPins[i], OUTPUT); // Set segment pins as OUTPUT
  }
  
  pinMode(sensorPin, INPUT); // Set pin 9 as INPUT for the pushbutton
  Serial.begin(9600); // Initialize serial communication for debugging

  // Initialize display to show 0
  displayNumber(objectCount);
}

void loop() {
  int sensorValue = digitalRead(sensorPin); // Read the sensor value

  // Check if initialization flag is not set
  if (!initialized) {
    // Set initialization flag if button is not pressed
    if (sensorValue == HIGH) {
      initialized = true; // Set the flag to true
      Serial.println("System initialized. Ready to count.");
    }
  } else {
    // If the button is pressed (LOW signal), and an object wasn't detected before
    if (sensorValue == LOW && !objectDetected) {
      objectCount++; // Increment the count
      
      // Reset count to 0 if it reaches 10
      if (objectCount > 9) {
        objectCount = 0;
      }

      objectDetected = true; // Set the flag to true
      Serial.print("Object detected. Count: ");
      Serial.println(objectCount); // Print the count

      // Display the count on the 7-segment display
      displayNumber(objectCount);
    }
    
    // If the button is no longer pressed (HIGH signal)
    if (sensorValue == HIGH && objectDetected) {
      objectDetected = false; // Reset the flag
    }
  }
  
  delay(100); // Short delay for stability
}

void displayNumber(int num) {
  byte pattern = digitPatterns[num];
  
  for (int i = 0; i < numSegments; i++) {
    // Write to segment pin according to pattern
    digitalWrite(segmentPins[i], (pattern >> i) & 1);
  }
}
*/

// Define the segment pins
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Connect to segments a, b, c, d, e, f, g
const int buttonPin = 9; // Connect to pushbutton

int count = 0; // Counter value
bool lastButtonState = HIGH; // Previous button state
bool currentButtonState; // Current button state
unsigned long lastDebounceTime = 0; // Last debounce time
unsigned long debounceDelay = 50; // Debounce delay time

void setup() {
  // Initialize all segment pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Initialize button pin as INPUT
  //pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(buttonPin, INPUT); // Use internal pull-up resistor
  Serial.begin(9600); // Initialize serial communication for debugging

  // Initialize the counter to 0
  count = 0;
  displayNumber(count); // Show initial count on the 7-segment display
}

void loop() {
  // Read the button state
  currentButtonState = digitalRead(buttonPin);

  // Check if button is pressed and was not pressed before
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    // Debounce the button press
    if ((millis() - lastDebounceTime) > debounceDelay) {
      count++;
      if (count > 9) {
        count = 0; // Reset count to 0 if it exceeds 9
      }
      Serial.print("Button pressed. Count: ");
      Serial.println(count);
      displayNumber(count); // Update display with the new count
    }
    lastDebounceTime = millis(); // Update last debounce time
  }

  // Update the last button state
  lastButtonState = currentButtonState;
}

void displayNumber(int num) {
  // Turn off all segments
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  // Set segments to display the number on the 7-segment display
  switch (num) {
    case 0:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], LOW);  // g
      break;
    case 1:
      digitalWrite(segmentPins[0], LOW);  // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], LOW);  // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], LOW);  // f
      digitalWrite(segmentPins[6], LOW);  // g
      break;
    case 2:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], LOW);  // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], LOW);  // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 3:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], LOW);  // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 4:
      digitalWrite(segmentPins[0], LOW);  // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], LOW);  // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 5:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], LOW);  // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 6:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], LOW);  // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 7:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], LOW);  // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], LOW);  // f
      digitalWrite(segmentPins[6], LOW);  // g
      break;
    case 8:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 9:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], LOW);  // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
  }
}
