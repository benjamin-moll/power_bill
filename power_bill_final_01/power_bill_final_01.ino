#include <Encoder.h>

int brightness1 = 0;    // how bright the LED is
int brightness2 = 0;
int brightness3 = 0;
int fadeAmount1 = 0;    // how many points to fade the LED by
int fadeAmount2 = 0;
int fadeAmount3 = 0;

unsigned long newTimer1 = 0;
bool time2fade = false;

//push button state variables
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;


unsigned long currentTime;
unsigned long loopTime;

const int E1_pin_A = 12;  // pin 12
const int E1_pin_B = 11;  // pin 11
const int E2_pin_A = 10;
const int E2_pin_B = 9;
const int E3_pin_A = 8;
const int E3_pin_B = 7;


unsigned char encoder1_A;
unsigned char encoder1_B;
unsigned char encoder1_A_prev = 0;
unsigned char encoder2_A;
unsigned char encoder2_B;
unsigned char encoder2_A_prev = 0;
unsigned char encoder3_A;
unsigned char encoder3_B;
unsigned char encoder3_A_prev = 0;

void setup()  {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(E1_pin_A, INPUT);
  pinMode(E1_pin_B, INPUT);
  pinMode(E2_pin_A, INPUT);
  pinMode(E2_pin_B, INPUT);
  pinMode(E3_pin_A, INPUT);
  pinMode(E3_pin_B, INPUT);
  currentTime = millis();
  loopTime = currentTime;
}

void loop()  {
  // get the current elapsed time
  buttonState = digitalRead(A0);
  currentTime = millis();
  Serial.println(buttonPushCounter);

  if (buttonState != lastButtonState) {

    if (buttonState == LOW) {
      buttonPushCounter++;
      //Serial.println(buttonPushCounter);
    }
  }

  else {
    if (currentTime >= (loopTime + 5)) {

      encoder1();
      encoder2();
      encoder3();

      loopTime = currentTime;  // Updates loopTime
    }
  }
  lastButtonState = buttonState;

  if (buttonPushCounter == 1) {
    fadeAmount1 = 20;    // how many points to fade the LED by
    fadeAmount2 = 20;
    fadeAmount3 = 20;

    analogWrite(2, brightness1);
    analogWrite(3, brightness1);
    analogWrite(5, brightness1);
  }
  else if (buttonPushCounter > 1) {
    buttonPushCounter = 0;
  }


}

void encoder1() {
  //  buttonPushCounter = 0;
  fadeAmount1 = 20;
  encoder1_A = digitalRead(E1_pin_A);    // Read encoder pins
  encoder1_B = digitalRead(E1_pin_B);
  if ((!encoder1_A) && (encoder1_A_prev)) {
    // A has gone from high to low
    if (encoder1_B) {
      // B is high so clockwise
      // increase the brightness, dont go over 255
      if (brightness1 + fadeAmount1 <= 255) brightness1 += fadeAmount1;
    }
    else {
      // B is low so counter-clockwise
      // decrease the brightness, dont go below 0
      if (brightness1 - fadeAmount1 >= 0) brightness1 -= fadeAmount1;
    }

  }
  encoder1_A_prev = encoder1_A;     // Store value of A for next time

  // set the brightness of pin 2:
  analogWrite(2, brightness1);
}

void encoder2() {
  fadeAmount2 = 1;
  //  buttonPushCounter = 0;
  encoder2_A = digitalRead(E2_pin_A);    // Read encoder pins
  encoder2_B = digitalRead(E2_pin_B);
  
  if ((!encoder2_A) && (encoder2_A_prev)) {
     unsigned long newTimer1 = millis();
    // A has gone from high to low
    if (encoder2_B) {
      // B is high so clockwise
      // increase the brightness, dont go over 150
      if (brightness2 + fadeAmount2 <= 150) brightness2 += fadeAmount2;
    }
    else {
      // B is low so counter-clockwise
      // decrease the brightness, dont go below 0
      if (brightness2 - fadeAmount2 >= 0) brightness2 -= fadeAmount2;
    }

  }
  if (millis() - newTimer1 >= 5000) {
    newTimer1 = millis();
    time2fade = !time2fade;
    
  }
  else if ((encoder2_A) && (encoder2_A_prev)) {
    if (time2fade) {
      if (brightness2 - 1 >= 0) brightness2 --;

      if (brightness2 - fadeAmount2 >= 0) brightness2 --;

    }
  }
    encoder2_A_prev = encoder2_A;     // Store value of A for next time

  analogWrite(3, brightness2);
}






void encoder3() {
  //  buttonPushCounter = 0;
  fadeAmount3 = 1;
  encoder3_A = digitalRead(E3_pin_A);    // Read encoder pins
  encoder3_B = digitalRead(E3_pin_B);
  if ((!encoder3_A) && (encoder3_A_prev)) {
    // A has gone from high to low
    if (encoder3_B) {
      // B is high so clockwise
      // increase the brightness, dont go over 255
      if (brightness3 + fadeAmount3 <= 80) brightness3 += fadeAmount3;
    }
    else {
      // B is low so counter-clockwise
      // decrease the brightness, dont go below 0
      if (brightness3 - fadeAmount3 >= 0) brightness3 -= fadeAmount3;
    }

  }
  else if ((encoder3_A) && (encoder3_A_prev)) {
    if (brightness3 - fadeAmount3 >= 0) brightness3 --;
  }
  encoder3_A_prev = encoder3_A;     // Store value of A for next time


  analogWrite(5, brightness3);
}
