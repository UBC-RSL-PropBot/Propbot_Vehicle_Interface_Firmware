#include "motor.h"

int update_speed (int current_speed , int target_speed){

    int updated_speed = current_speed;

    if (current_speed < target_speed){
        updated_speed = current_speed +1;
    }
    else {
        updated_speed = target_speed;
    }
    delay(200);
    return updated_speed;
}

void motor_write(int speed, uint8_t motor_pin){
    analogWrite(motor_pin, speed);
} 