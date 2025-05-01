
// void Ultrasonic() {
//   readUltrasonic(Serial3, data1, distance1, "📏 เซ็นเซอร์ 1");
//   readUltrasonic(Serial2, data2, distance2, "📏 เซ็นเซอร์ 2");
// }

// void readUltrasonic(HardwareSerial &port, unsigned char *data, float &distance, const char* label) {
//   if (port.available() >= 4) {
//     for (int i = 0; i < 4; i++) {
//       data[i] = port.read();
//     }

//     if (data[0] == 0xFF) {
//       int sum = (data[0] + data[1] + data[2]) & 0xFF;
//       if (sum == data[3]) {
//         distance = (data[1] << 8) + data[2];
//         distance = distance / 10.0;

//         // Serial.print(label);
//         // Serial.print(": ");
//         // Serial.print(distance, 1);
//         // Serial.println(" cm");
//       } else {
//         // Serial.print(label);
//         // Serial.println(" ⚠️ เช็กซัมไม่ตรง");
//       }
//     }
//   }
//   // Serial.print(distance1);
//   // Serial.print(".    |.  ");
//   // Serial.println(distance2);

// }