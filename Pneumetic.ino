// void spreading(int sd) {
//   static unsigned long obstacleStartTime = 0;
//   static bool isTooClose = false;
//   static bool speedTriggered = false;

//   bool tooClose = (distance1 < 50) || (distance2 < 50);

//   // spread ทำงานตามคำสั่ง sd ได้ตลอด (แม้เจอวัตถุ)
//   if (sd == 0) {
//     digitalWrite(spread, LOW);
//   } else if (sd == 1) {
//     digitalWrite(spread, HIGH);
//   }

//   // ถ้ามีวัตถุใกล้เข้ามา
//   if (tooClose) {
//     if (!isTooClose) {
//       obstacleStartTime = millis();   // เริ่มจับเวลา
//       isTooClose = true;
//       speedTriggered = false;
//     }

//     // หลังจากเจอวัตถุใกล้ > 1 วิ → หุบ และสั่งถอย 1 ครั้ง
//     if (millis() - obstacleStartTime >= 500) {
//       digitalWrite(spread, LOW);

//       if (!speedTriggered) {
//         speed = -128;
//         delay(500);
//         speedTriggered = true;
//         Serial.println("⚠️ หุบ + ถอย 1 ครั้ง (speed = -128)");
//       }
//     }

//   } else {
//     // รีเซ็ตสถานะเมื่อปลอดภัย
//     isTooClose = false;
//     speedTriggered = false;
//   }
// }