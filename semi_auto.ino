// void semi_rotate(int ro){
//   if(ro ==1){
//     turn = 128;
//     delay(2000);
// }
// //delay
// void semi_auto1(int x){
//   if(x == 1){
//     analogWrite(speed,150);
//     //backward
//     digitalWrite(ccfr_dc,HIGH);
//     digitalWrite(cwfr_dc,LOW);
//     digitalWrite(ccfl_dc,LOW);
//     digitalWrite(cwfl_dc,HIGH);
//     digitalWrite(ccbr_dc,HIGH);
//     digitalWrite(cwbr_dc,LOW);
//     digitalWrite(ccbl_dc,LOW);
//     digitalWrite(cwbl_dc,HIGH);
//     delay(400);
//     //45degree
//     digitalWrite(ccfl_dc,LOW);
//     digitalWrite(cwfl_dc,LOW);
//     digitalWrite(ccfr_dc,LOW);
//     digitalWrite(cwfr_dc,HIGH);
//     digitalWrite(ccbl_dc,HIGH);
//     digitalWrite(cwbl_dc,LOW);
//     digitalWrite(ccbr_dc,LOW);
//     digitalWrite(cwbr_dc,LOW);
//     delay(350);
//   }}

//   //millis
//   void semi_auto2(int x){
//     unsigned long currentMillis = millis();
//     if(x == 1){
//       switch (currentState) {
//         case FOR:
//           if (currentMillis - previousMillis >= intervalFor) {
//             previousMillis = currentMillis;
//             currentState = LEFT;
//             digitalWrite(ccfl_dc,LOW);
//             digitalWrite(cwfl_dc,LOW);
//             digitalWrite(ccfr_dc,LOW);
//             digitalWrite(cwfr_dc,HIGH);
//             digitalWrite(ccbl_dc,HIGH);
//             digitalWrite(cwbl_dc,LOW);
//             digitalWrite(ccbr_dc,LOW);
//             digitalWrite(cwbr_dc,LOW);
//           } else {
//             digitalWrite(ccfr_dc,HIGH);
//             digitalWrite(cwfr_dc,LOW);
//             digitalWrite(ccfl_dc,LOW);
//             digitalWrite(cwfl_dc,HIGH);
//             digitalWrite(ccbr_dc,HIGH);
//             digitalWrite(cwbr_dc,LOW);
//             digitalWrite(ccbl_dc,LOW);
//             digitalWrite(cwbl_dc,HIGH);
//           }
//           break;

//         case LEFT:
//           if (currentMillis - previousMillis >= intervalLeft) {
//             previousMillis = currentMillis;
//             currentState = STOP;
//             digitalWrite(cwfr_dc,LOW); //stop
//             digitalWrite(ccfr_dc,LOW);
//             digitalWrite(cwfl_dc,LOW);
//             digitalWrite(ccfl_dc,LOW);
//             digitalWrite(cwbr_dc,LOW);
//             digitalWrite(ccbr_dc,LOW);
//             digitalWrite(cwbl_dc,LOW);
//             digitalWrite(ccbl_dc,LOW);
//           } else {
//             digitalWrite(ccfl_dc,LOW);
//             digitalWrite(cwfl_dc,LOW);
//             digitalWrite(ccfr_dc,LOW);
//             digitalWrite(cwfr_dc,HIGH);
//             digitalWrite(ccbl_dc,HIGH);
//             digitalWrite(cwbl_dc,LOW);
//             digitalWrite(ccbr_dc,LOW);
//             digitalWrite(cwbr_dc,LOW);
//           }
//           break;

//         case STOP:
//           // ไม่ทำอะไรเมื่ออยู่ในสถานะหยุด
//           break;
//       }}
//     else{
//       digitalWrite(cwfr_dc,LOW); //stop
//       digitalWrite(ccfr_dc,LOW);
//       digitalWrite(cwfl_dc,LOW);
//       digitalWrite(ccfl_dc,LOW);
//       digitalWrite(cwbr_dc,LOW);
//       digitalWrite(ccbr_dc,LOW);
//       digitalWrite(cwbl_dc,LOW);
//       digitalWrite(ccbl_dc,LOW);
//     }
//   }

