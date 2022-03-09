#ifndef FETCH_RC_H
#define FETCH_RC_H
#include <string.h>
#include <stdio.h>
#include <Arduino.h>


#define RC_RIGHT_CHANNEL_PIN    24
#define RC_LEFT_CHANNEL_PIN     25
#define RC_SWA_CHANNEL_PIN      23
#define RC_SWB_CHANNEL_PIN      22

#define RC_SWA_HIGH_MAX             2000
#define RC_SWA_HIGH_MIN             1900

struct RC_Vals{
    uint16_t sw_a;
    uint16_t sw_b;
    uint16_t rc_left;
    uint16_t rc_right;
}; 


RC_Vals fetch_rc_commands( );
void check_RC_status();

#endif // !FETCH_RC_H
