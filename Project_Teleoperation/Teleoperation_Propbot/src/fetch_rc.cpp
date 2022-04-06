#include "fetch_rc.h"

bool autonomy_switch = false;

RC_Vals fetch_rc_commands( ){
    RC_Vals rc;
    rc.sw_a = pulseIn(RC_SWA_CHANNEL_PIN,HIGH);
    rc.sw_b = pulseIn(RC_SWB_CHANNEL_PIN,HIGH);
    rc.rc_left = pulseIn(RC_LEFT_CHANNEL_PIN,HIGH);
    rc.rc_right = pulseIn(RC_RIGHT_CHANNEL_PIN,HIGH);
    return rc;
}

void check_RC_status(){
    RC_Vals rc;
    rc = fetch_rc_commands();

    if (rc.sw_b < RC_SWA_HIGH_MAX && rc.sw_b > RC_SWA_HIGH_MAX) {
        autonomy_switch = true;
    } else{
        autonomy_switch = false;
    }

}