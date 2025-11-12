// -------------------------------
// TRAFFIC + PEDESTRIAN LIGHT SYSTEM
// -------------------------------

// CAR LIGHT PINS
int carRed = 4;
int carYellow = 3;
int carGreen = 2;

// PEDESTRIAN LIGHT PINS
int pedRed = 7;
int pedGreen = 6;

// BUTTON PIN
int button = 5;

// State variable
bool buttonPressed = false;

void setup() {
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button, INPUT);

  // Initial state
  digitalWrite(carGreen, HIGH);
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, LOW);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);
}

void loop() {
  // --CAR GREEN PHASE ----
  digitalWrite(carGreen, HIGH);
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, LOW);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);

  unsigned long startTime = millis();
  while (millis() - startTime < 10000) { // 10s green time (can end early)
    if (digitalRead(button) == HIGH) {
      buttonPressed = true;
      break;
    }
  }

  // ---CAR YELLOW PHASE (TO RED) ----
  digitalWrite(carGreen, LOW);
  digitalWrite(carYellow, HIGH);
  delay(5000); // 5 seconds yellow

  // ---CAR RED / PEDESTRIAN GREEN ----
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, HIGH);
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);
  delay(7000); // pedestrian crossing time

  // ---PREPARE FOR GREEN (Sequential Red → Yellow → Green) ----
  // Step 1: Turn pedestrian green off, pedestrian red on
  digitalWrite(pedGreen, LOW);
  digitalWrite(pedRed, HIGH);
  delay(1000);

  // Step 2: Turn car red OFF before yellow comes on
  digitalWrite(carRed, LOW);
  delay(500); // short gap so red and yellow aren't on together

  // Step 3: Turn yellow ON (get ready)
  digitalWrite(carYellow, HIGH);
  delay(2000); // 2 seconds prepare time

  // Step 4: Turn yellow OFF, green ON (go)
  digitalWrite(carYellow, LOW);
  digitalWrite(carGreen, HIGH);

  buttonPressed = false;
}
