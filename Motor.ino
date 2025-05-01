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