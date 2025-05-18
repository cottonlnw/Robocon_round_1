int limit_pid_output(int power){
    if(power > 100) return 100;
    else if(power < -100) return -100;
    return power;
}

int pid_calc(PID &pid, int value, int target, float kp, float kd, float ki) {
  int error = target - value;
  pid.integral += error;
  int derivative = error - pid.last_error;
  int output = kp * error + ki * pid.integral + kd * derivative;

  pid.last_error = error;

  if (abs(error) < 2) {
    output = 0;
  }

  return limit_pid_output(output);
}

void write_data(int d1,int d2,int d3){
  analogWrite(speed,d1);
  analogWrite(strafe,d2);
  analogWrite(turn,d3);
}