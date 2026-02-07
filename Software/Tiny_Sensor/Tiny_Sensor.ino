/*
  Tiny Sensor.

  Measure the output of a voltage divider on ATtiny85 pin 2 (Arduino A3).  Flash a red LED connected to
  ATtiny85 pin 5 (Arduino digital 0) at the following rate:

    - analogRead() value of 150: flash at 0.5 second on and 0.5 second off
    - analogread() value of 1000: flash at 50 ms on and 50 ms off

  Flash a green LED connected to ATtiny85 pin 6 (Arduino digital 1) at the opposite phase of the red LED.

  written by: Bob Glicksman
  released under open source, non-coomercial license
  (c) 2026 by Bob Glicksman, Jim Schrempp, Team Practical projects.  All rights reserved.

  version 1.0: initial release.  2/06/26

*/

#define MIN_FLASH_TIME 50  // fastest flash is 50 ms on and 50 ms off
#define MAX_FLASH_TIME 500  // slowest flask is 0.5 second on and 0.5 second off

#define MIN_ANALOG_VALUE 150  // sensor is at its highest resistance
#define MAX_ANALOG_VALUE 1000 // sensor is at its lowest resistance

unsigned long ledTime;
bool redLEDstate;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins 0 and 1 (ATtiny85 physical pins 5 and 6 as an output for the LEDs)
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  ledTime - millis(); // initialize the led flashing time
  redLEDstate = false;  // start off with red lED off and green LED on

  // Flash both LEDs three times before entering loop
  for(int i = 0; i < 3; i++) {
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    delay(300);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    delay(300);
  }

  // Initialize with RED LED off and GREEN LED on
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);

  delay(1000);

  
} // send of setup()

// the loop function runs over and over again forever
void loop() {
  int sensorValue;
  long flashTime;

  sensorValue = analogRead(A3);
  flashTime = map(sensorValue, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, MAX_FLASH_TIME, MIN_FLASH_TIME);

  nbFlashLEDs(flashTime);
} // end of loop()

void nbFlashLEDs(long interval) {
  if(millis() >= (ledTime + interval)) {  // time to flip states
    redLEDstate = !redLEDstate;
    ledTime = millis(); // update the time
  }

  if(redLEDstate == true) { // turn on red LED and off green LED
    digitalWrite(0, HIGH);
    digitalWrite(1, LOW);

  } else {  // turn off red LED and on green LED
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
  }
} // end of nbFlashLEDs()



