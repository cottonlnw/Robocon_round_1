String inputData = "";
int speed = 0, strafe = 0, turn = 0;
int auto_up = 0, Spread = 0;
int rackup =0,slow_mode =0;
int manual_rack_down =0,manual_rack_up = 0;
bool isManualLock = false;  // อยู่ในโหมด manual หรือไม่
int manual_unlock_button = 0;  // ปุ่มจากจอยใช้สำหรับปลด manual lock
//DC motor
#define motorLF1 2    // Digital (ทิศทาง)
#define motorLFPMW 3  // PWM (ความเร็ว)

// BACK LEFT MOTOR
#define motorLB1 4    // Digital
#define motorLBPMW 5  // PWM

// FRONT RIGHT MOTOR
#define motorRF1 6    // Digital
#define motorRFPMW 7  // PWM

// BACK RIGHT MOTOR
#define motorRB1 8    // Digital
#define motorRBPMW 9  // PWM

// #define up_rack 28
// #define vcc_rack 22

#define motorRACK1 28. // if high down rack
#define motorRACK2 22 //if high up rack
#define motorPWM   10  //  ต้องเป็นขา PWM เช่น D3, D5, D6, D9, D10, D11

int rackPower = 200;  // ระดับความแรง (0–255)

// #define pneup 28

#define limitUp    26    // ลิมิตบน
#define limitDown  24    // ลิมิตล่าง

void setup() {
  Serial.begin(115200);  // Start the built-in serial communication for debugging
  Serial1.begin(115200);
  pinMode(motorLF1, OUTPUT);
  pinMode(motorLFPMW, OUTPUT);
  pinMode(motorLB1, OUTPUT);
  pinMode(motorLBPMW, OUTPUT);
  pinMode(motorRF1, OUTPUT);
  pinMode(motorRFPMW, OUTPUT);
  pinMode(motorRB1, OUTPUT);
  pinMode(motorRBPMW, OUTPUT);
  pinMode(motorRACK1, OUTPUT);
  pinMode(motorRACK2, OUTPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(limitUp, INPUT_PULLUP);
  pinMode(limitDown, INPUT_PULLUP);
}

void loop() {
  // Controller inputs
  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '\n') {
      parseSerialData(inputData);
      inputData = "";
    } else {
      inputData += c;
    }
  }

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
void parseSerialData(String data) {
  // Serial.print("raw: ");
  // Serial.println(data);

  int values[25];
  int index = 0;
  int lastIndex = 0;

  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == ',') {
      values[index++] = data.substring(lastIndex, i).toInt();
      lastIndex = i + 1;
    }
  }
  values[index] = data.substring(lastIndex).toInt();  // ตัวสุดท้าย

  if (index >= 2) {
    turn   = values[0];
    strafe = values[2];
    speed  = values[1];
    auto_up = values[3];
    slow_mode = values[4];
    manual_rack_up = values[5];
    manual_rack_down = values[6];
    manual_unlock_button = values[7];
  }

  // Serial.print("Parsed → Turn: ");
  // Serial.print(turn);
  // Serial.print(" | Strafe: ");
  // Serial.print(strafe);
  // Serial.print(" | Speed: ");
  // Serial.print(speed);
  // Serial.print(" | Rack: ");
  // Serial.println(Up);
}
