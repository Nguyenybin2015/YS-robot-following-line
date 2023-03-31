int stop_distance = 22;

int sensor1 = A3;
int sensor2 = A2;
int sensor3 = A1;
int sensor4 = A0;
int sensor[4] = { 0, 0, 0, 0 };

int ENA = 9;  
int motorInput1 = 8;
int motorInput2 = 7;
int motorInput3 = 12;
int motorInput4 = 11;
int ENB = 10;  

int initial_motor_speed = 100;

float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);  
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  read_sensor_values();
  if (error == 100) { 
    do {// Quay sang trai cho toi khi phat hien ngay giua line
      analogWrite(ENA, 80);  
      analogWrite(ENB, 80); 
      left();
      // sharpLeftTurn();
      read_sensor_values();
    } while (error == 0);
  } else if (error == 101) {
    do {// Quay sang phai cho toi khi phat hien ngay giua line
      analogWrite(ENA, 80);  
      analogWrite(ENB, 80);  
      sharpRightTurn();
      read_sensor_values();
    } while (error == 0);
  } else if (error == 102) {  
    do {  // Quay sang trai cho toi khi phat hien ngay giua line
      read_sensor_values();
      analogWrite(ENA, 80);  
      analogWrite(ENB, 80);  
      sharpLeftTurn();
    } while (error == 0);
  } else if (error == 103) {  
    stop_bot();
    if (flag == 0) {
      analogWrite(ENA, 80);  
      analogWrite(ENB, 80);  
      forward();
      delay(100);
      read_sensor_values();
      if (error == 103) { 
        stop_bot();
        delay(200);
        flag = 1;
      } else {
        do {// Quay sang trai cho toi khi phat hien ngay giua line
          analogWrite(ENA, 80);  
          analogWrite(ENB, 80);  
          sharpLeftTurn();
          read_sensor_values();
        } while (error == 0 || error == 1 || error == -1);
      }
    }
  } else {
    calculate_pid();  // Tinh gia tri PID
    motor_control();  // Dieu chinh motor theo gia tri PID, cho xe chay thang
  }
   if (distance < stop_distance) // Neu khoang cach nho hon gioi han
  {

    digitalWrite (motorA1, HIGH); 
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    delay(350);

    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(300);


    digitalWrite (motorA1, HIGH); (motorA2, LOW);
    digitalWrite (motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    delay(400);
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(200);

    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite (motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    delay(600);
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(200);


    digitalWrite (motorA1, LOW); 
    digitalWrite(motorA2, HIGH);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(550);
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(200);

    ///////////////////
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite (motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    delay(600); 
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(200);

    ////////////////////////
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(500);
    digitalWrite (motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite (motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(200);

    digitalWrite (motorA1, LOW); 
    digitalWrite(motorA2, HIGH);
    digitalWrite (motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }
}

void read_sensor_values() {
  sensor[0] = digitalRead(sensor1);
  sensor[1] = digitalRead(sensor2);
  sensor[2] = digitalRead(sensor3);
  sensor[3] = digitalRead(sensor4);

  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0))  
    error = -3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
    error = -1;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0))  
    error = 0;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1))  
    error = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0))  
    error = 100;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1))  
    error = 101;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0))  
    error = 102;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) 
    error = 103;
}

void calculate_pid() {
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);  // error = 3; PID = 120 motor phai chay nhanh hon

  previous_I = I;
  previous_error = error;
}

void motor_control() {

  int left_motor_speed = initial_motor_speed - PID_value;   
  int right_motor_speed = initial_motor_speed + PID_value;  

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);  

  analogWrite(ENA, left_motor_speed - 30);
  analogWrite(ENB, right_motor_speed);

  forward();
}

void forward() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void reverse() {
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void right() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void left() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
void sharpRightTurn() {
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void sharpLeftTurn() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void stop_bot() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}