//The Power Bill Code with Distribute Button option

//set the pins for the LEDs and distribute button
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 5;
const int buttonPin = 6;

//push button state variables
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

//initializing potentiometer read-in values
int analogValue1 = 0;
int analogValue2 = 0;
int analogValue3 = 0;

//initializing potentiometer out values
int crank1 = 0;
int crank2 = 0;
int crank3 = 0;


void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);


}

void loop() {

  //read states of pots and button
  buttonState = digitalRead(buttonPin);
  analogValue1 = analogRead(A0);
  analogValue2 = analogRead(A1);
  analogValue3 = analogRead(A2);

  //if there's been a button press, increment counter
  if (buttonState != lastButtonState) {
    //increment the counter
    if (buttonState == LOW) {
      buttonPushCounter++;

    }
  }
  //otherwise, each crank controls its respective LED, crank2 and 3 are scaled down to be "unfair"
  else {

    crank1 = analogValue1 / 4;
    crank2 = (analogValue2 / 4) * 0.2;
    crank3 = (analogValue3 / 4) * 0.1;

    analogWrite(ledPin1, crank1);
    analogWrite(ledPin2, crank2);
    analogWrite(ledPin3, crank3);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;



  //if button pressed, "distribute" power evenly to all LEDs
  if (buttonPushCounter == 1) {
    analogWrite(ledPin1, crank1);
    analogWrite(ledPin2, crank1);
    analogWrite(ledPin3, crank1);

  }
  //otherwise, continue allowing individual crank control and reset button counter
  else {
    crank1 = analogValue1 / 4;
    crank2 = (analogValue2 / 4) * 0.2;
    crank3 = (analogValue3 / 4) * 0.1;

    analogWrite(ledPin1, crank1);
    analogWrite(ledPin2, crank2);
    analogWrite(ledPin3, crank3);
    buttonPushCounter = 0;

  }

}
