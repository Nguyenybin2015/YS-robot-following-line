// Motor A connections
const int enA = 7;
const int in1 = 8;
const int in2 = 9;
// Motor B connections
const int enB = 12;
const int in3 = 10;
const int in4 = 11;
// Sensor connections
const int irPins1 = 2;
const int irPins2 = 3;
const int irPins3 = 4;
const int irPins4 = 5;
const int irPins5 = 6;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Set pin sensor
  pinMode(irPins1, INPUT);
  pinMode(irPins2, INPUT);
  pinMode(irPins3, INPUT);
  pinMode(irPins4, INPUT);
  pinMode(irPins5, INPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  int ss1 = digitalRead(irPins1);
  int ss2 = digitalRead(irPins2);
  int ss3 = digitalRead(irPins3);
  int ss4 = digitalRead(irPins4);
  int ss5 = digitalRead(irPins5);


  
  if ((ss2 == 1) && (ss3 == 1) && (ss4 == 1)) {
    maxSpeed();
  }

  
  else if ((ss2 == 1) && (ss3 == 1) && (ss4 == 0)) {
    turnLeft();
  }

  else if ((ss2 == 1) && (ss3 == 0) && (ss4 == 0)) {
    turnLeft();
  }

  else if ((ss2 == 0) && (ss3 == 0) && (ss4 == 1)) {
    turnRight();
  }

  else if ((ss2 == 0) && (ss3 == 0) && (ss4 == 0)) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  
}

void maxSpeed() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void turnLeft() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void turnRight(){
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
