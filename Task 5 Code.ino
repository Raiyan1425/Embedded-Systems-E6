 // Pin definitions
int redCar = 4;
int yellowCar = 3;
int greenCar = 2;

// Variables
bool pedestrianRequest = false;

void setup() {
  pinMode(redCar, OUTPUT);
  pinMode(yellowCar, OUTPUT);
  pinMode(greenCar, OUTPUT);
 
  Serial.begin(9600); // RX/TX communication
}

void loop() {
  // Check for pedestrian request
  if (Serial.available()) {
    char signal = Serial.read();
    if (signal == '1') {
      pedestrianRequest = true;
    }
  }

  if (pedestrianRequest) {
    // Stop cars (Red)
    digitalWrite(greenCar, LOW);
    digitalWrite(yellowCar, LOW);
    digitalWrite(redCar, HIGH);
    delay(5000); // time for pedestrian crossing
   
    pedestrianRequest = false; // reset
  } else {
    // Normal traffic light sequence
    digitalWrite(greenCar, HIGH);
    digitalWrite(redCar, LOW);
    delay(5000);
   
    digitalWrite(greenCar, LOW);
    digitalWrite(yellowCar, HIGH);
    delay(5000);
   
    digitalWrite(yellowCar, LOW);
    digitalWrite(redCar, HIGH);
    delay(5000);
  }
}