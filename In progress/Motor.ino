
void drive_manual(int speed,int strafe, int turn) {
  
  int motor1Speed,motor2Speed,motor3Speed,motor4Speed;


  if (slow_mode==1){
  motor1Speed = (speed + strafe + turn)/3;    // LF
  motor2Speed = (speed - strafe - turn)/3;    // RF
  motor3Speed = (speed - strafe + turn)/3;    // LB
  motor4Speed = (speed + strafe - turn)/3; 
  }else{
    // Calculate motor speeds
  motor1Speed = speed + strafe + turn;    // LF
  motor2Speed = speed - strafe - turn;    // RF
  motor3Speed = speed - strafe + turn;    // LB
  motor4Speed = speed + strafe - turn;    // RB
  }

  // Normalize speeds
  motor1Speed = adjust_speed(motor1Speed);
  motor2Speed = adjust_speed(motor2Speed);
  motor3Speed = adjust_speed(motor3Speed);
  motor4Speed = adjust_speed(motor4Speed);

  int maxMotorSpeed = max(max(abs(motor1Speed), abs(motor2Speed)), max(abs(motor3Speed), abs(motor4Speed)));
  if (maxMotorSpeed > 128) {
    motor1Speed = (motor1Speed * 128) / maxMotorSpeed;
    motor2Speed = (motor2Speed * 128) / maxMotorSpeed;
    motor3Speed = (motor3Speed * 128) / maxMotorSpeed;
    motor4Speed = (motor4Speed * 128) / maxMotorSpeed;
  }

  // Control motors
  ControlMotor(motor1Speed, motorLF1, motorLFPMW);
  ControlMotor(motor2Speed, motorRF1, motorRFPMW);
  ControlMotor(motor3Speed, motorLB1, motorLBPMW);
  ControlMotor(motor4Speed, motorRB1, motorRBPMW);
  // กด manual → ใช้ manual_rack แทน auto_racking ทันที
if (manual_rack_up == 1 || manual_rack_down == 1) {
  isManualLock = true;

}
//ถ้ากดปุ่มปลด manual → กลับไป auto ได้
if (manual_unlock_button == 1) {
  isManualLock = false;
}
//ตัดสินใจว่าต้องใช้ฟังก์ชันไหน
if (isManualLock) {
  manual_rack(manual_rack_up, manual_rack_down);
  Serial.println("manual");
} else {
  auto_racking(auto_up);
  Serial.println("auto_racking");
}
  // spreading(Spread);
  //Serial.println(speed);
  delay(25);
}

void ControlMotor(int speed, int A, int PWM) {
  if (speed > 0) { 
    digitalWrite(A, HIGH);
  } else if (speed < 0) {
    digitalWrite(A, LOW);
  } else { 
    digitalWrite(A, LOW);
  }

  int frequency = map(abs(speed), 0, 128, 0, 500);
  if (frequency > 255) {
    frequency = 255;
  }
  analogWrite(PWM, frequency);
}

int adjust_speed(int speed) {
  if (abs(speed) < 10) { 
    return 0;
  }
  return speed;
}

