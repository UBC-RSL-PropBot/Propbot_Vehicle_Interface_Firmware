#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <stdio.h>

#define FWD_MIN_SPEED      85
#define FWD_MAX_SPEED      105
#define BKWD_MIN_SPEED     85
#define BKWD_MAX_SPEED     105
#define RIGHT_SPEED        105
#define LEFT_SPEED         105

int update_speed (int current_speed , int target_speed);
void motor_write(int speed, uint8_t motor_pin);


#endif