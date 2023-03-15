#include <AccelStepper.h>

// Define the stepper motor connections for screw receiver (skrue arm)
#define STEP_PIN 8
#define DIR_PIN 7
#define ENABLE_PIN 5

// Define the stepper motor connections for screw drum wheel (skruehjul)
#define STEP_PIN2 3
#define DIR_PIN2 2
#define ENABLE_PIN2 11

#define SWITCH_PIN 50 //Limit switch til armen

#define HOME_STEPS 1 // Kor mange steps fram den skal gå etter å ha gått bak i home posisjon, for å ikkje ligge å presse på bryteren.

// Create an instance of the AccelStepper class
AccelStepper skruearm(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
AccelStepper skruehjul(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);

void setup() {
  // Set up the enable pin as an output and disable the driver
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, HIGH);

   pinMode(ENABLE_PIN2, OUTPUT);
  digitalWrite(ENABLE_PIN2, LOW);


  // Set the maximum speed and acceleration
  skruearm.setMaxSpeed(700);
  skruearm.setAcceleration(900);

  skruehjul.setMaxSpeed(800);
  skruehjul.setAcceleration(800);

      // Set the switch pin as an input
  pinMode(SWITCH_PIN, INPUT_PULLUP);


}

//////////////////////////////////////////////////////////////////////////
void home() {
digitalWrite(ENABLE_PIN, HIGH);

  // Når motoren skal kalibreres.
    while (digitalRead(SWITCH_PIN) == HIGH) {
    skruearm.setSpeed(-200);
    skruearm.runSpeed();
  }
 

  // Set the position of the motor to zero
  skruearm.setCurrentPosition(0);

  // Move the motor forwards to the home position
  skruearm.move(HOME_STEPS);
  skruearm.runToPosition();
}
  

/////////////////////////////////////////////////////////////////////////
//Kjører skrue arm til posisjonen den skal hente skruen
void henteskrue() {
  // Kjører armen opp til å hente skrue
 skruearm.move(2*(200*5)/8);

  // Run the motor until it reaches the target position
  while (skruearm.distanceToGo() != 0) {
    skruearm.run();
}
}

//////////////////////////////////////////////////////////////////////////
//Kjører skrue arm til posisjonen den skal skru inn skruen
void skruinn() {
  // Kjører armen opp til å hente skrue
 skruearm.move(-(140*5)/8);
  // Run the motor until it reaches the target position
  while (skruearm.distanceToGo() != 0) {
    skruearm.run();
}
}

////////////////////////////////////////////////////////////////////////////
//Funksjon for å kjøret skruehjulet en runde

void skruehjule() {

  // Kjører skruehjulet en runde for å hente en skrue
 digitalWrite(ENABLE_PIN2, HIGH);
 skruehjul.move(400*5);
  // Run the motor until it reaches the target position
  while (skruehjul.distanceToGo() != 0) {
    skruehjul.run();

  
}
//Skrur av motoren igjen etter at skruehjulet har tatt en runde
 digitalWrite(ENABLE_PIN2, LOW);
}

////////////////////////////////////////////////////////////////////////////
//Programmet
void loop() {
  // Enable the driver
  
  home();

  delay(3000);

  henteskrue();

skruehjule();

//delay(2000);  

  skruinn();

delay(3000);

  // Disable the driver
  digitalWrite(ENABLE_PIN, LOW);

  // Wait for 1 second before repeating
  delay(5000);
}
