int limit_pid_output(int power){
    if(power > 100) return 100;
    else if(power < -100) return -100;
    return power;
}

int pid(int value, int target, float kp, float kd, float ki){
    static int integral = 0;
    static int last_error = 0;

    int error = target - value;
    integral += error;
    int derivative = error - last_error;
    int output = kp * error + ki * integral + kd * derivative;

    last_error = error;

    if(abs(error) < 2){
        output = 0;
    }

    return limit_pid_output(output);
}

void write_data(int d1,int d2,int d3){
  analogWrite(speed,d1);
  analogWrite(strafe,d2);
  analogWrite(turn,d3);
}