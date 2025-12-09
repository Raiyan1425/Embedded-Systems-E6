  // Pedestrian
int redPed = 7;
int greenPed = 6;
int button = 5;  // button connected between pin 5 and GND

void setup() {
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
  pinMode(button, INPUT_PULLUP); // internal pull-up resistor enabled
 
  Serial.begin(9600); // TX/RX communication
}

void loop() {
  // Default pedestrian light: red
  digitalWrite(redPed, HIGH);
  digitalWrite(greenPed, LOW);

  // Check if button is pressed (reads LOW when pressed)
  if (digitalRead(button) == LOW) {
    // Send pedestrian request to Arduino 1
    Serial.write('1');

    // Turn pedestrian green after Arduino 1 stops cars
    delay(5000); // wait for car red signal
    digitalWrite(redPed, LOW);
    digitalWrite(greenPed, HIGH);
    delay(5000); // pedestrian crossing time

    // Reset pedestrian light
    digitalWrite(greenPed, LOW);
    digitalWrite(redPed, HIGH);
  }
}
