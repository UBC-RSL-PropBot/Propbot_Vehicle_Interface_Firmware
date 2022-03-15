#ifndef MAIN_H
#define MAIN_H


#include <Wire.h>
#include <math.h>


uint8_t R_F_motorPin         = 13;
uint8_t R_F_DirectionPin     = 53;
uint8_t R_F_BrakePin         = 52;

uint8_t L_F_motorPin         = 4;
uint8_t L_F_DirectionPin     = 50;
uint8_t L_F_BrakePin         = 51;

#define SCL_PIN 0              //Default SDA is Pin5 PORTC for the UNO -- you can set this to any tristate pin
#define SCL_PORT PORTD 
#define SDA_PIN 1              //Default SCL is Pin4 PORTC for the UNO -- you can set this to any tristate pin
#define SDA_PORT PORTD
#define I2C_TIMEOUT 100        //Define a timeout of 100 ms -- do not wait for clock stretching longer than this time
/*
#define I2C_FASTMODE 1         //Run in fast mode (400 kHz)
#define I2C_SLOWMODE 1         //If you do not define the mode it will run at 100kHz with this define set to 1 it will run at 25kHz
*/
#include <SoftI2CMaster.h>

// CH2 - right longitudinal wheel set
#define RC_RIGHT_SET_FW_MAX         2200
#define RC_RIGHT_SET_FW_MIN         1900
#define RC_RIGHT_SET_BW_MAX         1100
#define RC_RIGHT_SET_BW_MIN         500
// CH3 - left longitudinal wheel set
#define RC_LEFT_SET_FW_MAX          2200
#define RC_LEFT_SET_FW_MIN          1900
#define RC_LEFT_SET_BW_MAX          1100
#define RC_LEFT_SET_BW_MIN          500
// CH5 - SwA range
#define RC_SWA_HIGH_MAX             2000
#define RC_SWA_HIGH_MIN             1900

#define DelayTimeForwardRight   = 200
#define DelayTimeBackwardRight  = 200
#define DelayTimeForwardLeft    = 400
#define DelayTimeBackwardLeft   = 400

#endif
