void Drive_train(int speed,int strafe, int turn) {
  int motor1Speed = speed + strafe + turn;    // LF
  int motor2Speed = speed - strafe - turn;    // RF
  int motor3Speed = speed - strafe + turn;    // LB
  int motor4Speed = speed + strafe - turn;    // RB

  ControlMotor_semi(motor1Speed, motorLF1, motorLFPMW);
  ControlMotor_semi(motor2Speed, motorRF1, motorRFPMW);
  ControlMotor_semi(motor3Speed, motorLB1, motorLBPMW);
  ControlMotor_semi(motor4Speed, motorRB1, motorRBPMW);
}
void ControlMotor_semi(int speed, int pinA, int pinB) {
  int pwm = abs(speed);
  if (speed > 0) {
    analogWrite(pinA, 0); analogWrite(pinB, pwm);
  } else if (speed < 0) {
    analogWrite(pinA, pwm); analogWrite(pinB, 0);
  } else {
    analogWrite(pinA, 0); analogWrite(pinB, 0);
  }
}

int adjust_speed_semi(int s) {
  if (abs(s) < 25) return 0;
  return constrain(s, -255, 255);
}

void automode(){
  if (lock_position_left == 0 && lock_position_right ==0){
    digitalWrite(trigger_left, LOW);
    digitalWrite(trigger_mid, LOW);
    digitalWrite(trigger_right, LOW);
    drive_manual(ry,rx,lx);
  }else if(lock_position_left == 1 && lock_position_right == 0){
    digitalWrite(trigger_left, HIGH);
    digitalWrite(trigger_mid, LOW);
    digitalWrite(trigger_right, LOW);
    Drive_train(speed,strafe,turn);
  }else if (lock_position_right == 1 && lock_position_left == 0){
    digitalWrite(trigger_right, HIGH);
    digitalWrite(trigger_mid, LOW);
    digitalWrite(trigger_left, LOW);
    Drive_train(speed,strafe,turn);
  }else if (lock_position_right == 1 && lock_position_left == 1){
    digitalWrite(trigger_mid, HIGH);
    digitalWrite(trigger_left, LOW);
    digitalWrite(trigger_right, LOW);
    Drive_train(speed,strafe,turn);
  }else{
    drive_train(0,0,0);
}
}
