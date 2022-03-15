#ifndef SONAR_H
#define SONAR_H


#include <stdio.h>
#include <Arduino.h>

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

boolean start_sensor(byte bit8address);
int read_sensor(byte bit8address);
boolean change_address(byte oldaddress,byte newaddress);
void read_the_sensor_example(int addr);

#endif