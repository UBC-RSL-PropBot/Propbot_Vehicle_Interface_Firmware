#include "fetch_rc.h"

RC_Vals fetch_rc_commands( ){
    RC_Vals rc;
    rc.sw_a = pulseIn(RC_SWA_CHANNEL_PIN,HIGH);
    rc.sw_b = pulseIn(RC_SWB_CHANNEL_PIN,HIGH);
    rc.rc_left = pulseIn(RC_LEFT_CHANNEL_PIN,HIGH);
    rc.rc_right = pulseIn(RC_RIGHT_CHANNEL_PIN,HIGH);
    return rc;
}