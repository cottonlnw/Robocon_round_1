void setgyro(){
  mpu.begin();   // เริ่มการเชื่อมต่อ MPU6050
  mpu.calcGyroOffsets(true); // คำนวณค่า offset สำหรับ Gyroscope เพิ่มoffsetเองได้ ไม่ต้องinit ทุกรอบ
  //mpu.setGyroOffsets(-5.97, 1.25, 3.31);
  mpu.update();   // อ่านค่าจาก MPU6050 ครั้งแรก
  degree_x_error = mpu.getAngleX();
  degree_y_error = mpu.getAngleY();
  degree_z_error = mpu.getAngleZ();

  degree = 0;
  degree_y = 0;
  degree_x = 0;
}

void read_gyro() {
  mpu.update();
  degree = mpu.getAngleZ() - degree_z_error;
  degree_x = mpu.getAngleX() - degree_x_error;
  degree_y = mpu.getAngleY() - degree_y_error;

  if (degree > 180) {
    degree -= 360;
} else if (degree < -180) {
    degree += 360;
}
}

void reset_gyro(int button){
  if(button == 1){
    mpu.update();
    degree_x_error = mpu.getAngleX();
    degree_y_error = mpu.getAngleY();
    degree_z_error = mpu.getAngleZ();
    delay(200);
  }
}

void set_lidar() {
  // ตั้งค่าให้ Lidar ทุกตัวเริ่มต้นใหม่และกำหนดอัตราการถ่ายข้อมูล
  Serial.println("Soft reset lidar_f: ");
  if (lidar_f.sendCommand(SOFT_RESET, 0)) {
    Serial.println("passed.\r\n");
  } else {
    lidar_f.printReply();
  }

  Serial.println("Soft reset lidar_l: ");
  if (lidar_l.sendCommand(SOFT_RESET, 0)) {
    Serial.println("passed.\r\n");
  } else {
    lidar_l.printReply();
  }

  Serial.println("Soft reset lidar_r: ");
  if (lidar_r.sendCommand(SOFT_RESET, 0)) {
    Serial.println("passed.\r\n");
  } else {
    lidar_r.printReply();
  }

  // ตั้งค่าอัตราการถ่ายข้อมูลของ Lidar ทุกตัว
  set_lidar_frame_rate(lidar_f);
  set_lidar_frame_rate(lidar_l);
  set_lidar_frame_rate(lidar_r);
}

void set_lidar_frame_rate(TFMPlus &lidar) {
  Serial.println("Data-Frame rate: ");
  if (lidar.sendCommand(SET_FRAME_RATE, FRAME_20)) {
    Serial.println(FRAME_20); // 20Hz
  } else {
    lidar.printReply();
  }
}

void read_lidar_f() {
  if (lidar_f.getData(dis_f, Flux_f, Temp_f)) {
    distance_f = dis_f;
  }
}

void read_lidar_l() {
  if (lidar_l.getData(dis_l, Flux_l, Temp_l)) {
    distance_l = dis_l;
  }
}

void read_lidar_r() {
  if (lidar_r.getData(dis_r, Flux_r, Temp_r)) {
    distance_r = dis_r;
  }
}

void set_pin(){
  pinMode(trigger1, INPUT);
  pinMode(trigger2, INPUT);
  pinMode(trigger3, INPUT)
  pinMode(speed, OUTPUT);
  pinMode(strafe, OUTPUT);
  pinMode(turn, OUTPUT);
  pinMode(shootball_power, OUTPUT);
}
