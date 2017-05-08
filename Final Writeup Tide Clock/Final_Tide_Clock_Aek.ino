
#include <Wire.h>
#include "RTClib.h"
// the value of the 'other' resistor
#define SERIESRESISTOR 560
// What pin to connect the sensor to
#define SENSORPIN A0


RTC_DS1307 RTC;

//int second = 0;
//int minute = 0;
//int hour = 0;
//int day = 0;
//int month = 0;
//int year = 0;
//int dayOfWeek = 0;
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 9;    // H-bridge enable pin
const int HighTideLevel = 779;
const int LowTideLevel = 665;
int  DesiredWaterLevel;
int NowLevel;
int reading;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  Serial.print("\nThe current date and time will be updated every three seconds:\n\n");
  // set the switch as an input:
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, HIGH);
}

void loop() {
  DateTime now = RTC.now();

  Serial.print(now.dayOfWeek(), DEC);
  Serial.print(" day of week\n");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  reading = analogRead(SENSORPIN);

  Serial.print("Current reading ");
  Serial.print(reading);

  // convert the value to resistance
  //  reading = (1023 / reading)  - 1;
  //  reading = SERIESRESISTOR / reading;
  delay(3000);

  NowLevel = reading; //checking Resitor for current Water level.

  if (now.minute() >= 30) { //Checking what tide the clock should be at.Giving HighTideLevel a Value
    DesiredWaterLevel = HighTideLevel;
    Serial.print("\tHigh Tide. \t");
  }
  else {
    DesiredWaterLevel = LowTideLevel;
    Serial.print("\tLow Tide. \t");
  }
  Serial.print("Desired level ");
  Serial.print(DesiredWaterLevel);

  if (NowLevel < (DesiredWaterLevel - 5)) { //Activates the Pump
    draining();
    Serial.print("\tdraining \n");
  }
  else if (NowLevel > (DesiredWaterLevel + 5)) { //Stops the pump
    filling();
    Serial.print("\tfilling \n");
  }
  else {
    resting(); //stops the pump
    Serial.print("\tResting \n");
  }
  Serial.println();

}

void draining() {
  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
}

void filling() {
  digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
  digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
}

void resting() {
  digitalWrite(motor1Pin, LOW);  // set leg 1 of the H-bridge high
  digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
}

