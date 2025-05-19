// bool rackUpReached = false;

// void auto_racking(int uk){
//   bool upState = digitalRead(limitUp);       // HIGH = ไม่ชน / LOW = ชน
//   bool downState = digitalRead(limitDown);
//   Serial.print(uk);

//   if (uk == 1 && !rackUpReached && upState == 0) {
//     digitalWrite(motorRACK1,HIGH);
//     digitalWrite(motorRACK2,LOW);
//     analogWrite(motorPWM,120);
//     Serial.print("  1");
//   }
//   else if (uk == 1 && upState == 1) {
//     rackUpReached = true;
//     digitalWrite(motorRACK1, LOW);
//     digitalWrite(motorRACK2, LOW);
//     analogWrite(motorPWM, HIGH);
//     Serial.print("2");
//   }
//   else if (uk == 0 && downState == 0) {
//     rackUpReached = false;
//     digitalWrite(motorRACK1,LOW);
//     digitalWrite(motorRACK2,HIGH);
//     analogWrite(motorPWM, 20);
//     Serial.print("3");
//   }
//   else if (uk == 0 && downState == 1) {
//     digitalWrite(motorRACK1, HIGH);
//     digitalWrite(motorRACK2, HIGH);
//     analogWrite(motorPWM, 0);
//     Serial.print("4");
//   }
// }
void manual_rack(int mu, int md){
  bool upState = digitalRead(limitUp);       // HIGH = ไม่ชน / LOW = ชน
  bool downState = digitalRead(limitDown);

  // Serial.print(mu);
  // Serial.print("  ");
  // Serial.print(md);
  // Serial.print("  ");
  // Serial.print(upState);
  // Serial.print("  ");
  // Serial.println(downState);
  if(mu ==1 and upState==1){
    digitalWrite(motorRACK1, HIGH);
    digitalWrite(motorRACK2, HIGH);
    analogWrite(motorPWM, 0);
    Serial.print("5");
  }else if(md ==1 and downState==1){
    digitalWrite(motorRACK1, HIGH);
    digitalWrite(motorRACK2, HIGH);
    analogWrite(motorPWM, 0);
    Serial.print("6");
  }else if(mu == 1){
    digitalWrite(motorRACK1,HIGH);
    digitalWrite(motorRACK2,LOW);
    analogWrite(motorPWM,180);
    Serial.print("7");
  }else if(md ==1){
    digitalWrite(motorRACK1,LOW);
    digitalWrite(motorRACK2,HIGH);
    analogWrite(motorPWM, 40);
    Serial.print("8");
  }
  else {
  digitalWrite(motorRACK1, HIGH);
  digitalWrite(motorRACK2, HIGH);
  analogWrite(motorPWM, 0);
  Serial.print("9");
}

}
