
#include "main.h"
#include "fetch_rc.h"
#include "motor.h"

int current_speed = 85;
RC_Vals rc_task();
int state =0;
extern volatile bool autonomy_switch;


void setup(){
  Serial.begin(9600);
  Serial.println("Init");
  pinMode(2, INPUT_PULLUP);
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
  rc_commands = rc_task();
//   int sonar_val = digitalRead(2);
//   int next_state = state;
//   bool soft_estop = (rc_commands.sw_a < RC_SWA_HIGH_MAX && rc_commands.sw_a > RC_SWA_HIGH_MIN);
//   switch(state){
//     case 0:
//       if (sonar_val ==0 || soft_estop){
//         next_state = -1;
//       }
//       else if (autonomy_switch){
//         next_state = 1; 
//       }
//       break;
//     case 1:
//       if (sonar_val ==0 || soft_estop){
//         next_state = -1;
//       }
//       else if (autonomy_switch){
//         next_state = 0; 
//       }
//       break;
    
//     case -1:
//       if (sonar_val ==1 && !soft_estop && !autonomy_switch){
//           next_state = 0;
//         }
//         break;
//   }
//   state = next_state;
// //determine output
//     switch(state){
//        case 0:
//         Serial.println("state 0 : rc mode");
//         rc_commands = rc_task();
//         break;
//       case 1:
//          Serial.println("state 1 : autonomy mode");

//          /* Define and fill wheel motor commands */
//         break;
        
//       case -1:
//         Serial.println("state -1 : estop");
//         motor_write(0,L_F_motorPin);
//         motor_write(0,R_F_motorPin);
//         break;        
        
//     }

//     delay(100);
}

RC_Vals rc_task(){
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
    digitalWrite(0,L_F_BrakePin)
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }
  // if (!digitalRead(2)) //Swa triggeredardu
  // {
    
  //   motor_write(0,L_F_motorPin);
  //   motor_write(0,R_F_motorPin);
  // }
  return rc_commands;
}
