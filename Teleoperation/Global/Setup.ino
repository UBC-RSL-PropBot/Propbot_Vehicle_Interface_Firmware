void setup()  {
  Serial.begin(9600);
  pinMode(R_F_motorPin , OUTPUT);
  pinMode(R_F_DirectionPin , OUTPUT);
  pinMode(R_F_BrakePin , OUTPUT);
  i2c_init();
  pinMode(L_F_motorPin , OUTPUT);
  pinMode(L_F_DirectionPin , OUTPUT);
  pinMode(L_F_BrakePin , OUTPUT);
  digitalWrite(L_F_BrakePin, HIGH);
  digitalWrite(R_F_BrakePin, HIGH);
}
