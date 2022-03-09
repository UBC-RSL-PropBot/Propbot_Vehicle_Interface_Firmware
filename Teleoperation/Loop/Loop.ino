void loop()  {

  uint16_t sw_a       = pulseIn(RC_SWA_CHANNEL_PIN,   HIGH);
  uint16_t sw_b       = pulseIn(RC_SWB_CHANNEL_PIN,   HIGH);
  uint16_t rc_left    = pulseIn(RC_LEFT_CHANNEL_PIN,  HIGH);
  uint16_t rc_right   = pulseIn(RC_RIGHT_CHANNEL_PIN, HIGH);

  if (rc_left < RC_LEFT_SET_FW_MAX && rc_left > RC_LEFT_SET_FW_MIN)
  {
    if (ForwardMaxSpeedFlag == 1) { //Forward
      analogWrite(L_F_motorPin,MoveForwardMaxSpeed);
      analogWrite(R_F_motorPin,MoveForwardMaxSpeed);
    }
    else{
    MoveForward();
    }

  }
  else if (rc_left < RC_LEFT_SET_BW_MAX && rc_left > RC_LEFT_SET_BW_MIN) { //Backward
    if (BackwardMaxSpeedFlag == 1) {
      analogWrite(L_F_motorPin,MoveBackwardMaxSpeed);
      analogWrite(R_F_motorPin,MoveBackwardMaxSpeed);
    }
    else{
    MoveBackward();
    }
  }

  else if (rc_right < RC_RIGHT_SET_FW_MAX && rc_right > RC_RIGHT_SET_FW_MIN) //Right Turn
  {

    if (RightTurnMaxSpeedFlag == 1) {
      analogWrite(L_F_motorPin,TurningSpeed);
      analogWrite(R_F_motorPin,TurningSpeed);
    }
    else{
    MoveRightTurn();
    }

  }
  else if (rc_right < RC_RIGHT_SET_BW_MAX && rc_right > RC_RIGHT_SET_BW_MIN) { //Left Turn
    if (LeftTurnMaxSpeedFlag == 1) {
      analogWrite(L_F_motorPin,TurningSpeed);
      analogWrite(R_F_motorPin,TurningSpeed);
    }
    else{
    MoveLeftTurn();
    }
  }
  else {
    analogWrite(L_F_motorPin, 0);
    analogWrite(R_F_motorPin, 0);
      ForwardMaxSpeedFlag = 0;
      BackwardMaxSpeedFlag = 0;
      LeftTurnMaxSpeedFlag = 0;
      RightTurnMaxSpeedFlag = 0;

  }

  if (sw_a < RC_SWA_HIGH_MAX && sw_a > RC_SWA_HIGH_MIN)
  {
    analogWrite(L_F_motorPin, 0);
    analogWrite(R_F_motorPin, 0);
      ForwardMaxSpeedFlag = 0;
      BackwardMaxSpeedFlag = 0;
      LeftTurnMaxSpeedFlag = 0;
      RightTurnMaxSpeedFlag = 0;
  }
  
  int range;
  start_sensor(214);
  delay(100);
  range = read_sensor(214);
  Serial.print("R:");Serial.println(range);
}

//Needs to be in a seperate file

///////////////////////////////////////////////////
// Function: Start a range reading on the sensor //
///////////////////////////////////////////////////
boolean start_sensor(byte bit8address){
  boolean errorlevel = 0;
  bit8address = bit8address & B11111110;               //Do a bitwise 'and' operation to force the last bit to be zero -- we are writing to the address.
  errorlevel = !i2c_start(bit8address) | errorlevel;   //Run i2c_start(address) while doing so, collect any errors where 1 = there was an error.
  errorlevel = !i2c_write(81) | errorlevel;            //Send the 'take range reading' command. (notice how the library has error = 0 so I had to use "!" (not) to invert the error)
  i2c_stop();
  return errorlevel;
}

///////////////////////////////////////////////////////////////////////
// Function: Read the range from the sensor at the specified address //
///////////////////////////////////////////////////////////////////////
//Uses the I2C library to read a sensor at the given address
//Collects errors and reports an invalid range of "0" if there was a problem.
//INPUTS: byte  bit8address = the address of the sensor to read from
//OUPUTS: int   range = the distance in cm that the sensor reported; if "0" there was a communication error
int read_sensor(byte bit8address){
  boolean errorlevel = 0;
  int range = 0;
  byte range_highbyte = 0;
  byte range_lowbyte = 0;
  bit8address = bit8address | B00000001;  //Do a bitwise 'or' operation to force the last bit to be 'one' -- we are reading from the address.
  errorlevel = !i2c_start(bit8address) | errorlevel;
  range_highbyte = i2c_read(0);           //Read a byte and send an ACK (acknowledge)
  range_lowbyte  = i2c_read(1);           //Read a byte and send a NACK to terminate the transmission
  i2c_stop();
  range = (range_highbyte * 256) + range_lowbyte;  //compile the range integer from the two bytes received.
  if(errorlevel){
    return 0;
  }
  else{
    return range;
  }
}
