int in1 = 10; //out the board into L293D channel 1 pin
int in2 = 9; //out the board into L293D channel 2 pin

int enable1 = 11; //out the board into L293D enable 2 pin
bool rot_dir; 

int rot_speed;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enable1, OUTPUT);
}
void loop() {
  int dial_val = analogRead(A0); //value of dial
  rot_speed = abs(dial_val - 512);// 1024/2 half of the range of analog values
  if (dial_val>512)
    rot_dir = true; //positive
  else
    rot_dir = false; //negative
  //control motor with input received
  rot_speed = map(rot_speed, 0, 512, 0, 255);
  if (rot_speed > 150) {//check if functional amount
    driveMotor(rot_dir, rot_speed);// map range of speeds to range of outputs
  }
  else{//if not motor isoff
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void driveMotor(bool dir, int speed){
  //logic for motor direction
  if (rot_dir){//positive rotation
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  //logic for motor speed
  analogWrite(enable1, constrain(speed, 0, 255));
}
