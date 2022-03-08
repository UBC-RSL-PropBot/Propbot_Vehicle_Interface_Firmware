void MoveLeftTurn() {
      digitalWrite(L_F_DirectionPin, LOW);
      digitalWrite(R_F_DirectionPin, HIGH);
      delay(DelayTimeBackwardLeft);
      analogWrite(L_F_motorPin, TurningSpeed);
      analogWrite(R_F_motorPin, TurningSpeed);
}
