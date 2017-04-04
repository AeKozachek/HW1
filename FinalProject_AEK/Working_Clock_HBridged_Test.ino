
#include <Wire.h>
#include "RTClib.h"

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


void setup () {
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
  delay(3000);

  /* compare dayOfWeek, year, month, day, hour, minute, or second */
  if (now.second() +10 >= 30) {
    Serial.print("\nhello, we have a match. \n");
    digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
    digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
  }
  else {
    Serial.print("\nSorry, your numbers don't match. \n");
    digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
    digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
  }

}
