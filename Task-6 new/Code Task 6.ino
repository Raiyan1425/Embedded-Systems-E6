// ===== SIMPLE SMART TRAFFIC LIGHT (FINAL WORKING) =====

// -------- PINS --------
#define CAR_RED     4
#define CAR_YELLOW  3
#define CAR_GREEN   2

#define PED_RED     7
#define PED_GREEN   6

#define IR_SENSOR   5   // LOW when blocked

// -------- TIME (ms) --------
#define T_GREEN   10000
#define T_YELLOW   5000
#define T_RED     10000

// -------- STATES --------
int state = 0;  
// 0 = GREEN, 1 = YELLOW, 2 = RED

unsigned long lastTime = 0;

void setup() {
  pinMode(CAR_RED, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_GREEN, OUTPUT);

  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);

  pinMode(IR_SENSOR, INPUT);

  lastTime = millis();
}

void loop() {

  unsigned long now = millis();
  bool irBlocked = (digitalRead(IR_SENSOR) == LOW);
  // -------- IR OVERRIDE --------
  if (state == 0 && irBlocked) {
    // GREEN → YELLOW, Ped → GREEN
    setTraffic(1);
    setPed(1);
    state = 1;
    lastTime = now;
    return;
  }

  // -------- NORMAL CYCLE --------
  if (state == 0) {                 // GREEN
    setTraffic(0);
    setPed(0);
    if (now - lastTime >= T_GREEN) {
      state = 1;
      lastTime = now;
    }
  }
  else if (state == 1) {            // YELLOW
    setTraffic(1);
    setPed(0);
    if (now - lastTime >= T_YELLOW) {
      state = 2;
      lastTime = now;
    }
  }
  else if (state == 2) {            // RED
    setTraffic(2);
    setPed(1);
    if (now - lastTime >= T_RED) {
      state = 0;
      lastTime = now;
    }
  }
}

// -------- FUNCTIONS --------
void setTraffic(int s) {
  digitalWrite(CAR_GREEN,  s == 0);
  digitalWrite(CAR_YELLOW, s == 1);
  digitalWrite(CAR_RED,    s == 2);
}

void setPed(int s) {
  digitalWrite(PED_GREEN, s == 1);
  digitalWrite(PED_RED,   s != 1);
}