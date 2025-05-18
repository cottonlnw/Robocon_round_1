int speed = 0, strafe = 0, turn = 0;
int auto_up = 0, Spread = 0;
int rackup =0,slow_mode =0;
int manual_rack_down =0,manual_rack_up = 0;
bool isManualLock = false;  // อยู่ในโหมด manual หรือไม่
int manual_unlock_button = 0;  // ปุ่มจากจอยใช้สำหรับปลด manual lock
int lock_position_left = 0,lock_position_right = 0;
int pinA =0,pinB=0;
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
  readAndParseSerial1();
  if (lock_position_left == 0 && lock_position_right ==0){
    drive_manual(speed,strafe,turn);
  }else if(lock_position_left == 1){
    Drive_semi(speed,strafe,turn);
  }else if (lock_position_right == 1){
    Drive_semi(speed,strafe,turn);
  }else{
    drive_manual(0,0,0);
}

}



void readAndParseSerial1() {
  static String inputData = "";  

  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '\n') {
      int values[25];
      int index = 0;
      int lastIndex = 0;

      for (int i = 0; i < inputData.length(); i++) {
        if (inputData.charAt(i) == ',') {
          values[index++] = inputData.substring(lastIndex, i).toInt();
          lastIndex = i + 1;
        }
      }
      values[index] = inputData.substring(lastIndex).toInt();  // ตัวสุดท้าย

      if (index >= 2) {
        turn   = values[0];
        strafe = values[2];
        speed  = values[1];
        auto_up = values[3];
        slow_mode = values[4];
        manual_rack_up = values[5];
        manual_rack_down = values[6];
        manual_unlock_button = values[7];
        lock_position_left = values[8];
        lock_position_right = values[9];
      }

      inputData = "";  // ล้างหลังใช้เสร็จ
    } else {
      inputData += c;
    }
  }
}

