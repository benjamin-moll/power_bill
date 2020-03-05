//The Power Bill Code

const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 5;
int analogValue1 = 0;
int analogValue2 = 0;
int analogValue3 = 0;
int crank1 = 0;
int crank2 = 0;
int crank3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);


}

void loop() {
  analogValue1 = analogRead(A0);
  analogValue2 = analogRead(A1);
  analogValue3 = analogRead(A2);
  crank1 = analogValue1 / 4;
  crank2 = analogValue2 / 4;
  crank3 = analogValue3 / 4;

  analogWrite(ledPin1, crank1);
  analogWrite(ledPin2, crank2);
  analogWrite(ledPin3, crank3);



}
