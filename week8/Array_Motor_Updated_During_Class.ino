

#include <Servo.h>

Servo myservo;
const int  buttonPin = 4;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

int numberOfPositions = 5;
int positions[] = {75, 24, 122, 90, 55};


void setup() {
  myservo.attach(10);
  Serial.begin(9600);

}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
      int index = buttonPushCounter % numberOfPositions ;
      Serial.print("moving to index = ");
      Serial. println(index);

      myservo.write(positions[index]);
      delay(1000);
    }
  } // end of loop.
  


  else {
    Serial.println("off");
  }
  delay(50);
  lastButtonState != buttonState; //Needed to keep it from moving when the button is always pushed
}


