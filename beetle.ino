// Define Arduino pins
const int PIR_A = A0;
const int MOTOR_PIN = 3;

// Global variables
const int WAIT_TIME = 5000;
int motor_speed = 255;
int last_move = 0;
int motor_run_time = 10000;
bool motor_on = false;

void setup() {
  pinMode(PIR_A, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  if (motor_on == false && ((last_move + WAIT_TIME) < millis())) {
    if (check_motion()) {
      run_motor();
    }
  }
}

bool check_motion() {
    unsigned int analogPIR = analogRead(PIR_A); // read in analog value
    // Convert 10-bit analog value to a voltage
    // (Assume high voltage is 5.0V.)
    float voltage = (float) analogPIR / 1024.0 * 5.0;
    if (voltage > 4) {
      return true; 
    } else {
      return false;
    }
}

void run_motor() {
  // run motor for X seconds
  motor_on = true;
  analogWrite(MOTOR_PIN, motor_speed);
  delay(motor_run_time);
  analogWrite(MOTOR_PIN, 0);
  motor_on = false;
  last_move = millis();
}

