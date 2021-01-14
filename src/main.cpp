#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

// based on
// https://www.instructables.com/28BYJ-48-Stepper-Motor-Control-System-Based-On-Ard/

int Iint1 = 0;
int Iint2 = 1;
int anjian1 = 2;
int anjian2 = 3;
int motorSpeed;

// don't update the speed all the time
unsigned long next_update;
const int update_every = 100;

// button variables and debounce
bool cw = true;
bool pause = true;
unsigned long lastCwDebounceTime = 0;
unsigned long lastPauseDebounceTime = 0;
const int debounceDelay = update_every;

// int step = 0;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3,
                      POSITIVE);  // Set the LCD I2C address

// const int stepsPerRevolution = 200;
const int stepsPerRevolution = 2038;
// const int stepsPerRevolution = 2048;
// const int stepsPerRevolution = 768;
// const int stepsPerRevolution = 4095;
// const int stepsPerRevolution = 48;

// Here set the stepper motor rotation step how much is a circle
// int dim = stepsPerRevolution;

// Set the step motor number and pin
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void changeDirection() {
  if (lastCwDebounceTime < millis()) {
    if (cw) {
      cw = false;
    } else {
      cw = true;
    }
    lastCwDebounceTime = millis() + debounceDelay;
  }
}

void togglePause() {
  if (lastPauseDebounceTime < millis()) {
    if (pause) {
      pause = false;
    } else {
      pause = true;
    }
    lastPauseDebounceTime = millis() + debounceDelay;
  }
}

void setup() {
  // Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Speed      u/min");
  // lcd.setCursor(11, 0);
  // lcd.print("u/min");
  lcd.setCursor(0, 1);
  lcd.print("Direction ------");

  // Set the motor speed of 60 steps per minute
  myStepper.setSpeed(10);
  pinMode(anjian1, INPUT_PULLUP);
  pinMode(anjian2, INPUT_PULLUP);
  attachInterrupt(Iint1, changeDirection, FALLING);
  attachInterrupt(Iint2, togglePause, FALLING);
}

void loop() {
  // if (!pause) {
  //   if (cw) {
  //     myStepper.step(stepsPerRevolution / 100);
  //   } else {
  //     myStepper.step(stepsPerRevolution / -100);
  //   }
  // }

  // if (millis() > next_update) {
  //   next_update = millis() + update_every;

  // Read the sensor values:
  int sensorReading = analogRead(A0);

  // Map it to a range of 0-100:
  int motorSpeed = map(sensorReading, 1023, 0, 1, 10);
  // Serial.print("motorSpeed: ");
  // Serial.println(motorSpeed);

  // Set the motor speed:
  // if (motorSpeed > 0) {
  myStepper.setSpeed(motorSpeed);
  lcd.setCursor(6, 0);
  // lcd.print(float(float(motorSpeed) / float(stepsPerRevolution)));
  lcd.print(motorSpeed);

  lcd.setCursor(10, 1);
  // lcd.setCursor(0, 1);
  if (pause) {
    lcd.print("||||||");
  } else {
    if (cw) {
      lcd.print(">>>>>>");
      myStepper.step(stepsPerRevolution / 100);
      // lcd.print("Direction >>>>>>");
    } else {
      lcd.print("<<<<<<");
      myStepper.step(stepsPerRevolution / -100);
      // lcd.print("Direction <<<<<<");
    }
    // }

    // Serial.print("speed: ");
    // Serial.print(float(float(motorSpeed) / float(200)));
    // Serial.println(" n/min");
    // }
  }
}
