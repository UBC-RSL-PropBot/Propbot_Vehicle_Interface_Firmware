
#include "main.h"
#include "fetch_rc.h"
#include "motor.h"
#include <ros.h>
#include <std_msgs/UInt8.h>


int current_speed = 80;
RC_Vals rc_task();
int state = 0;
extern volatile bool autonomy_switch;

ros::NodeHandle node;
std_msgs::UInt8 pwm_left;
std_msgs::UInt8 pwm_right;

//Defining Publisher and callback
ros::Publisher talker_left("pwm_left", &pwm_left);
ros::Publisher talker_right("pwm_right", &pwm_right);

void callback_left ( const std_msgs::UInt8& msg_left){
pwm_left.data = msg_left.data;
talker_left.publish( &pwm_left );
}

void callback_right ( const std_msgs::UInt8& msg_right){
pwm_right.data = msg_right.data;
talker_right.publish( &pwm_right );
}


ros::Subscriber<std_msgs::UInt8> listener_left("left_wheel", callback_left);
ros::Subscriber<std_msgs::UInt8> listener_right("right_wheel", callback_right);



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
  node.initNode();
//Configure Subscriber and Publisher
node.subscribe(listener_left);
node.subscribe(listener_right);
node.advertise(talker_left);
node.advertise(talker_right);
}

void loop()
{
  node.spinOnce();
  RC_Vals rc_commands;
  rc_commands = rc_task();
  int sonar_val = digitalRead(2);
  int next_state = state;
  autonomy_switch = (rc_commands.sw_b < RC_SWA_HIGH_MAX && rc_commands.sw_b > RC_SWA_HIGH_MIN);
  bool soft_estop = (rc_commands.sw_a < RC_SWA_HIGH_MAX && rc_commands.sw_a > RC_SWA_HIGH_MIN);
  pwm_left.data = 2;
  talker_left.publish( &pwm_left );

  switch(state){
    case 0: // TELEOPERATION
      if (sonar_val ==1 || soft_estop){
        next_state = -1;
      }
      else if (autonomy_switch){
        next_state = 1; 
      }
      break;
    case 1:
      if (sonar_val == 1 || soft_estop){
        next_state = -1;
      }
      else if (!autonomy_switch){
        next_state = 0; 
      }
      break;
    
    case -1:
      if (sonar_val == 0 && !soft_estop && !autonomy_switch){
          next_state = 0;
        }
        break;
  }

  bool changed_state = next_state != state;

  state = next_state;
//determine output
    switch(state){
       case 0:
        Serial.println("state 0 : rc mode");
        if (changed_state){
            node.logwarn("Switched to RC mode");
         }
        //
        pwm_left.data = 5;
        talker_left.publish( &pwm_left );
        rc_commands = rc_task();
        break;
      case 1:
         Serial.println("state 1 : autonomy mode");
         if (changed_state){
            node.loginfo("In autonomy mode");
         }
         
        analogWrite(L_F_motorPin,pwm_left.data);
        analogWrite(R_F_motorPin,pwm_right.data);
         /* Define and fill wheel motor commands */
        break;
        
      case -1:
        Serial.println("state -1 : estop");
        if (changed_state){
            node.logerror("Switched to ESTOP mode");
         }
        
        current_speed = 80;
        motor_write(0,L_F_motorPin);
        motor_write(0,R_F_motorPin);
        break;        
        
    }

    delay(100);
}

RC_Vals rc_task(){
  RC_Vals rc_commands;
  rc_commands = fetch_rc_commands();
  if (rc_commands.sw_a < RC_SWA_HIGH_MAX && rc_commands.sw_a > RC_SWA_HIGH_MIN) //Swa triggered
  {
    current_speed = 80;
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }
  else if (rc_commands.rc_left < RC_LEFT_SET_FW_MAX && rc_commands.rc_left > RC_LEFT_SET_FW_MIN) //Forward
  {
    digitalWrite(L_F_DirectionPin, LOW);
    digitalWrite(R_F_DirectionPin, LOW);
    int updated_speed = update_speed(current_speed, FWD_MAX_SPEED);
    current_speed = updated_speed;
    motor_write(updated_speed+2,L_F_motorPin);
    motor_write(updated_speed-2,R_F_motorPin);    
  }
  else if (rc_commands.rc_left < RC_LEFT_SET_BW_MAX && rc_commands.rc_left > RC_LEFT_SET_BW_MIN) //Backward
  {
    digitalWrite(L_F_DirectionPin, HIGH);
    digitalWrite(R_F_DirectionPin, HIGH);
    int updated_speed = update_speed(current_speed, BKWD_MAX_SPEED);
    current_speed = updated_speed;
    motor_write(updated_speed+3,L_F_motorPin);
    motor_write(updated_speed-4,R_F_motorPin);     
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
    current_speed = 80;
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }
  if (rc_commands.sw_a < RC_SWA_HIGH_MAX && rc_commands.sw_a > RC_SWA_HIGH_MIN) //Swa triggered
  //if (rc_commands.sw_a < RC_SWA_LOW_MAX && rc_commands.sw_a > RC_SWA_LOW_MIN) //Swa triggered INVERTED
  {
    current_speed = 80;
    motor_write(0,L_F_motorPin);
    motor_write(0,R_F_motorPin);
  }
  return rc_commands;
}



