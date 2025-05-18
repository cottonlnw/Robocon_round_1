#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050_tockn.h>
#include <TFMPlus.h>

//ปุ่ม set ตำแหน่ง
#define trigger1 76
#define trigger2 77

//AnalogWrite
#define speed 78
#define strafe 79
#define turn 80

// กำหนดการเชื่อมต่อ MPU6050
MPU6050 mpu(Wire);

// กำหนดการเชื่อมต่อ Lidar ทั้ง 3 ตัว
TFMPlus lidar_f; // Lidar ด้านหน้า
TFMPlus lidar_l; // Lidar ด้านซ้าย
TFMPlus lidar_r; // Lidar ด้านขวา

const char terminator = '\0';

// ตัวแปรเก็บค่าจากเซ็นเซอร์ต่างๆ
int gx = 0;
int gy = 0;
int gz = 0;
int degree = 0;
int degree_y = 0;
int degree_x = 0;
int distance_f = 0;
int distance_l = 0;
int distance_r = 0;

int16_t dis_f = 0;     // ระยะห่างจากวัตถุในเซ็นเซอร์ Lidar ด้านหน้า
int16_t Flux_f = 0;    // คุณภาพของสัญญาณจาก Lidar ด้านหน้า
int16_t Temp_f = 0;    // อุณหภูมิของ Lidar ด้านหน้า

int16_t dis_l = 0;     // ระยะห่างจากวัตถุในเซ็นเซอร์ Lidar ด้านซ้าย
int16_t Flux_l = 0;    // คุณภาพของสัญญาณจาก Lidar ด้านซ้าย
int16_t Temp_l = 0;    // อุณหภูมิของ Lidar ด้านซ้าย

int16_t dis_r = 0;     // ระยะห่างจากวัตถุในเซ็นเซอร์ Lidar ด้านขวา
int16_t Flux_r = 0;    // คุณภาพของสัญญาณจาก Lidar ด้านขวา
int16_t Temp_r = 0;    // อุณหภูมิของ Lidar ด้านขวา

const long lidar_read_interval = 25; // อ่านค่า Lidar ทุก 50 ms
unsigned long start_lidar = 0;

int force[3] = {0,0,0}; // {speed, strafe, turn}
int Sensor[4] = {distance_f,distance_l,distance_r,degree};
int shoot_spot1[3] = {100,200,20};
int shoot_spot2[3] = {100,200,-20};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // เปิด Serial Monitor
  Serial2.begin(115200); // เปิด Serial2 สำหรับ Lidar ด้านหน้า
  Serial3.begin(115200); // เปิด Serial3 สำหรับ Lidar ด้านขวา
  Serial4.begin(115200); // เปิด Serial4 สำหรับ Lidar ด้านซ้าย
  Wire.begin();   // เริ่มการเชื่อมต่อ I2C

  lidar_f.begin(&Serial2);   // เริ่มการเชื่อมต่อกับ Lidar ด้านหน้า
  lidar_l.begin(&Serial4);   // เริ่มการเชื่อมต่อกับ Lidar ด้านซ้าย
  lidar_r.begin(&Serial3);   // เริ่มการเชื่อมต่อกับ Lidar ด้านขวา
  set_lidar();   // ตั้งค่า Lidar
  start_lidar = millis();
  
  setgyro();
  set_pin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - start_lidar >= lidar_read_interval) {
    read_lidar_f();
    read_lidar_l();
    read_lidar_r();
    start_lidar = millis(); 
  }
  read_gyro();
  //String sensor = String(Sensor[0]) + " " + String(Sensor[1])+ " " + String(Sensor[2])+ " " + String(Sensor[3])+ " " + String(Sensor[4]);
  //Serial.print(sensor);
  
  //Sensor[4] = {distance_f,distance_l,distance_r,degree};
  if (trigger1 == 1 && trigger2 == 0){
    force[0] = pid(Sensor[0],shoot_spot1[0],5,0.5,0); //pid(int value,int target,float kp,float kd,float ki)
    force[1] = pid(Sensor[1],shoot_spot1[1],5,0.5,0);
    force[2] = pid(Sensor[3],shoot_spot1[2],5,0.5,0);
    write_data(force[0],force[1],force[2]);
  }
  else if (trigger1 == 0 && trigger2 == 1){
    force[0] = pid(Sensor[0],shoot_spot2[0],5,0.5,0); //pid(int value,int target,float kp,float kd,float ki)
    force[1] = pid(Sensor[2],shoot_spot2[1],5,0.5,0);
    force[2] = pid(Sensor[3],shoot_spot2[2],5,0.5,0);
    write_data(force[0],force[1],force[2]);
  }else{
    write_data(0,0,0);
  }
}
