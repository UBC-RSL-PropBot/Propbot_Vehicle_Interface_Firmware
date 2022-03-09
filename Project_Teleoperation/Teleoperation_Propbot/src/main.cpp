
#include "main.h"
#include "fetch_rc.h"
#include "motor.h"

int current_speed = 85;


void setup(){
  pinMode(R_F_motorPin , OUTPUT);
  pinMode(R_F_DirectionPin , OUTPUT);
  pinMode(R_F_BrakePin , OUTPUT);
  pinMode(L_F_motorPin , OUTPUT);
  pinMode(L_F_DirectionPin , OUTPUT);
  pinMode(L_F_BrakePin , OUTPUT);
  digitalWrite(L_F_BrakePin, HIGH);
  digitalWrite(R_F_BrakePin, HIGH);
}

void loop()
{
  RC_Vals rc_commands;
  rc_commands = fetch_rc_commands();
  if (rc_commands.rc_left < RC_LEFT_SET_FW_MAX && rc_commands.rc_left > RC_LEFT_SET_FW_MIN) //Forward
  {
    digitalWrite(L_F_DirectionPin, LOW);
    digitalWrite(R_F_DirectionPin, LOW);
    int updated_speed = update_speed(current_speed, FWD_MAX_SPEED);
    current_speed = updated_speed;
    motor_write(updated_speed,L_F_motorPin);
    motor_write(updated_speed,R_F_motorPin);    
  }
  else if (rc_commands.rc_left < RC_LEFT_SET_BW_MAX && rc_commands.rc_left > RC_LEFT_SET_BW_MIN) //Backward
  {
    digitalWrite(L_F_DirectionPin, HIGH);
    digitalWrite(R_F_DirectionPin, HIGH);
    int updated_speed = update_speed(current_speed, BKWD_MAX_SPEED);
    current_speed = updated_speed;
    motor_write(updated_speed,L_F_motorPin);
    motor_write(updated_speed,R_F_motorPin);     
  }

  else if (rc_commands.rc_right < RC_RIGHT_SET_FW_MAX && rc_commands.rc_right > RC_RIGHT_SET_FW_MIN) //Right Turn
  {
    digitalWrite(L_F_DirectionPin, LOW);
    digitalWrite(R_F_DirectionPin, HIGH);
    motor_write(RIGHT_SPEED,L_F_motorPin);
    motor_write(RIGHT_SPEED,R_F_motorPin);
  }
  else if (rc_commands.rc_right < RC_RIGHT_SET_BW_MAX && rc_commands.rc_right > RC_RIGHT_SET_BW_MIN) //Left Turn
  {
    digitalWrite(L_F_DirectionPin, HIGH);
    digitalWrite(R_F_DirectionPin, LOW);
    motor_write(LEFT_SPEED,L_F_motorPin);
    motor_write(LEFT_SPEED,R_F_motorPin);
  }
  else //0 Position RC Joysticks
  {
    current_speed = 85;
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }

  if (rc_commands.sw_a < RC_SWA_HIGH_MAX && rc_commands.sw_a > RC_SWA_HIGH_MIN) //Swa triggered
  {
    current_speed = 85;
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }

}
