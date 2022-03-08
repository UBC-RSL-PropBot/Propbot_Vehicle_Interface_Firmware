void MoveForward() {
      int range;
      start_sensor(214);
      delay(DelayTimeForwardRight);
      range = read_sensor(214);
  
      for (int i = MoveForwardMinSpeed ; i < MoveForwardMaxSpeed ; i = i + 1) {
      uint16_t rc_left   = pulseIn(RC_LEFT_CHANNEL_PIN, HIGH);
      uint16_t sw_a       = pulseIn(RC_SWA_CHANNEL_PIN,   HIGH);
      start_sensor(214);
      delay(100);
      range = read_sensor(214);
      if (sw_a < RC_SWA_HIGH_MAX && sw_a > RC_SWA_HIGH_MIN){  
        analogWrite(L_F_motorPin, 0);
        analogWrite(R_F_motorPin, 0);
        break;
        }
       if (range <200){
        analogWrite(L_F_motorPin, 0);
        analogWrite(R_F_motorPin, 0);
        break;
       }
      if (rc_left < 1900){  
        analogWrite(L_F_motorPin, 0);
        analogWrite(R_F_motorPin, 0);
        break;
        }
      digitalWrite(L_F_DirectionPin, LOW);
      digitalWrite(R_F_DirectionPin, LOW);
      
      start_sensor(214);
      delay(DelayTimeForwardRight);
      range = read_sensor(214);
      analogWrite(L_F_motorPin, i);
      analogWrite(R_F_motorPin, i);
  }
  ForwardMaxSpeedFlag = 1;
}
