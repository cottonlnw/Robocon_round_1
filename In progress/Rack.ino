bool rackUpReached = false;

void auto_racking(int uk){
  bool upState = digitalRead(limitUp);       // HIGH = ไม่ชน / LOW = ชน
  bool downState = digitalRead(limitDown);

  if (uk == 1 && !rackUpReached && upState == 0) {
    digitalWrite(motorRACK1,HIGH);
    digitalWrite(motorRACK2,LOW);
    analogWrite(motorPWM,120);
  }
  else if (uk == 1 && upState == 1) {
    rackUpReached = true;
    digitalWrite(motorRACK1, HIGH);
    digitalWrite(motorRACK2, HIGH);
    analogWrite(motorPWM, 0);
  }
  else if (uk == 0 && downState == 0) {
    rackUpReached = false;
    digitalWrite(motorRACK1,LOW);
    digitalWrite(motorRACK2,HIGH);
    analogWrite(motorPWM, 30);
  }
  else if (uk == 0 && downState == 1) {
    digitalWrite(motorRACK1, HIGH);
    digitalWrite(motorRACK2, HIGH);
    analogWrite(motorPWM, 0);
  }
}
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
  }else if(md ==1 and downState==1){
    digitalWrite(motorRACK1, HIGH);
    digitalWrite(motorRACK2, HIGH);
    analogWrite(motorPWM, 0);
  }else if(mu == 1){
    digitalWrite(motorRACK1,HIGH);
    digitalWrite(motorRACK2,LOW);
    analogWrite(motorPWM,100);
  }else if(md ==1){
    digitalWrite(motorRACK1,LOW);
    digitalWrite(motorRACK2,HIGH);
    analogWrite(motorPWM, 20);
  }
  else {
  digitalWrite(motorRACK1, HIGH);
  digitalWrite(motorRACK2, HIGH);
  analogWrite(motorPWM, 0);
}

}
