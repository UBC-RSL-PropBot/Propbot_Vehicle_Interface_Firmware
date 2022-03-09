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
