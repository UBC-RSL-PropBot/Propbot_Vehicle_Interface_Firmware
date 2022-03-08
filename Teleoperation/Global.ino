//Global variables and functions used throughout the code and libraries needed//

#include <Wire.h>
#include <math.h>
#define SCL_PIN 0              //Default SDA is Pin5 PORTC for the UNO -- you can set this to any tristate pin
#define SCL_PORT PORTD
#define SDA_PIN 1              //Default SCL is Pin4 PORTC for the UNO -- you can set this to any tristate pin
#define SDA_PORT PORTD
#define I2C_TIMEOUT 100        //Define a timeout of 100 ms -- do not wait for clock stretching longer than this time
/*
  #define I2C_FASTMODE 1         //Run in fast mode (400 kHz)
  #define I2C_SLOWMODE 1         //If you do not define the mode it will run at 100kHz with this define set to 1 it will run at 25kHz
*/
#include <SoftI2CMaster.h>     //You will need to install this library

int R_F_motorPin         = 13;
int R_F_DirectionPin     = 53;
int R_F_BrakePin         = 52;

int L_F_motorPin         = 4;
int L_F_DirectionPin     = 50;
int L_F_BrakePin         = 51;

int DelayTimeForwardRight   = 200;
int DelayTimeBackwardRight  = 200;
int DelayTimeForwardLeft    = 400;
int DelayTimeBackwardLeft   = 400;

int MoveForwardMinSpeed   = 85;
int MoveForwardMaxSpeed   = 110;
int MoveBackwardMinSpeed  = 85;
int MoveBackwardMaxSpeed  = 110;
int MoveTurnRightMinSpeed = 85;
int MoveTurnRightMaxSpeed = 110;
int MoveTurnLeftMinSpeed  = 85;
int MoveTurnLeftMaxSpeed  = 110;

int ForwardMaxSpeedFlag;
int BackwardMaxSpeedFlag;
int RightTurnMaxSpeedFlag;
int LeftTurnMaxSpeedFlag;


#define RC_RIGHT_CHANNEL_PIN    24
#define RC_LEFT_CHANNEL_PIN     25
#define RC_SWA_CHANNEL_PIN      23
#define RC_SWB_CHANNEL_PIN      22

// CH2 - right longitudinal wheel set
#define RC_RIGHT_SET_FW_MAX         1985
#define RC_RIGHT_SET_FW_MIN         1638
#define RC_RIGHT_SET_BW_MAX         1310
#define RC_RIGHT_SET_BW_MIN         980
// CH3 - left longitudinal wheel set
#define RC_LEFT_SET_FW_MAX          1972
#define RC_LEFT_SET_FW_MIN          1632
#define RC_LEFT_SET_BW_MAX          1320
#define RC_LEFT_SET_BW_MIN          997//1007
// CH5 - SwA range
#define RC_SWA_HIGH_MAX             2000
#define RC_SWA_HIGH_MIN             1900

//Functions
void MoveForward();
void MoveBackward();
void MoveRightTurn();
void MoveLeftTurn();
