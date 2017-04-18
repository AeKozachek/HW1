
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
const int HighTideLevel = 700;
const int LowTideLevel = 715;
int  DesiredWaterLevel;
int NowLevel;
int reading;




void setup() {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  Serial.print("\nThe current date and time will be updated every three seconds:\n\n");
  // set the switch as an input:


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


  Serial.print("Analog reading ");
  Serial.println(reading);

  // convert the value to resistance
//  reading = (1023 / reading)  - 1;
//  reading = SERIESRESISTOR / reading;
delay(3000);

  NowLevel = (reading); //checking Resitor for current Water level.

  if (now.second() >= 30) { //Checking what tide the clock should be at.Giving HighTideLevel a Value
    DesiredWaterLevel = HighTideLevel;
    Serial.print("\nHigh Tide. \n");
  }
  else {
    DesiredWaterLevel = LowTideLevel;
    Serial.print("\nLow Tide. \n");
  }
  if (NowLevel < DesiredWaterLevel) {
    digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
    digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
    Serial.print("\nDraining \n");
  }
  else if (NowLevel > DesiredWaterLevel) {
    digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
    digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
    Serial.print("\nFilling \n");
  }
  else {
    digitalWrite(motor1Pin, LOW);  // set leg 1 of the H-bridge high
    digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low

  }


}
