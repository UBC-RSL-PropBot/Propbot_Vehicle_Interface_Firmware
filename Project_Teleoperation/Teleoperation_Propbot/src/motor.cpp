#include "motor.h"

const int motor_delay = 100;
unsigned long prev_motor_millis = 0;

int update_speed (int current_speed , int target_speed){
    int updated_speed = current_speed;
    if (millis() - prev_motor_millis >= motor_delay){       

        if (current_speed < target_speed){
            updated_speed = current_speed +1;
        }
        else {
            updated_speed = target_speed;
        }
        prev_motor_millis += motor_delay;
    }    
    return updated_speed;
}

void motor_write(int speed, uint8_t motor_pin){
    analogWrite(motor_pin, speed);
} 