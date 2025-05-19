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

void runStage(int& stage, int* target, bool trigger, int strafeIndex = 1) {
  if (!trigger) {
    stage = 0;
    return;
  }

  switch (stage) {
    case 0:
      if (abs(Sensor[3]) >= 1) {
        force[0] = 0;
        force[1] = 0;
        force[2] = pid_calc(pid_turn, Sensor[3], 0, 5, 0.5, 0);
      } else {
        stage = 1;
      }
      break;

    case 1:
      if (abs(Sensor[0] - target[0]) >= 2 && abs(Sensor[1] - target[1]) >= 2) {
        force[0] = pid_calc(pid_speed, Sensor[0], target[0], 5, 0.5, 0);
        force[1] = pid_calc(pid_strafe, Sensor[strafeIndex], target[1], 5, 0.5, 0);
        force[2] = pid_calc(pid_turn, Sensor[3], 0, 5, 0.5, 0);
      } else {
        stage = 2;
      }
      break;

    case 2:
      if (abs(Sensor[3] - target[2]) >= 1) {
        force[0] = 0;
        force[1] = 0;
        force[2] = pid_calc(pid_turn, Sensor[3], target[2], 5, 0.5, 0);
      } else {
        force[0] = 0;
        force[1] = 0;
        force[2] = 0;
      }
      break;
  }
}

void marking() {
  bool trig1 = digitalRead(trigger1);
  bool trig2 = digitalRead(trigger2);

  if (trig1 && !trig2) {
    runStage(stage1, shoot_spot1, true, 1); // Sensor[1] ใช้สำหรับ strafe
    analogWrite(shootball_power,200);
  } else if (!trig1 && trig2) {
    analogWrite(shootball_power,200);
    runStage(stage2, shoot_spot2, true, 2); // Sensor[2] ใช้สำหรับ strafe
  } else {
    // ไม่มี trigger ใดทำงาน รีเซต stage และหยุดแรง
    runStage(stage1, shoot_spot1, false);
    runStage(stage2, shoot_spot2, false);
    force[0] = 0;
    force[1] = 0;
    force[2] = 0;
  }
}

void write_data(int d1,int d2,int d3){
  analogWrite(speed,d1);
  analogWrite(strafe,d2);
  analogWrite(turn,d3);
}