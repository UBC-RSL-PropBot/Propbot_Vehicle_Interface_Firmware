
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
int counter = 0;
int max_count =0;
int AVG_VAL =2;
int sensor_val_1=0;
int sensor_val_2=0;
int sensor_val_3=0;
int sensor_val_4=0;
int sensor_val_5=0;
int sensor_val_6=0;

void setup(){
  // Initialize both the serial and I2C bus
  Serial.begin(9600);  
  i2c_init();   
  pinMode(2,OUTPUT);
  
}

void loop()
{
  // (OPTIONAL) Read a sensor at the default address
  sensor_val_1 = read_the_sensor_example(218);
  digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  //Serial.print("BOOL:");Serial.println(sensor_val_1);
  sensor_val_2 = 0;// read_the_sensor_example(208);
  digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  //Serial.print("BOOL:");Serial.println(sensor_val_2);
  sensor_val_3 = read_the_sensor_example(204);
  //Serial.print("BOOL:");Serial.println(sensor_val_3);
  digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  sensor_val_4 = 0; //read_the_sensor_example(200);
  //Serial.print("BOOL:");Serial.println(sensor_val_4);
  digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  sensor_val_5 = 0;// read_the_sensor_example(212);
  //Serial.print("BOOL:");Serial.println(sensor_val_5);
  //digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  sensor_val_6 = read_the_sensor_example(214);
  //Serial.print("BOOL:");Serial.println(sensor_val_6);
  digitalWrite(2,(sensor_val_1|sensor_val_2|sensor_val_3|sensor_val_4|sensor_val_5|sensor_val_6));
  //200 / 204/ 208/218
  //delay(200);
  //test_read(200);
 
  
  // Your code here

}



///////////////////////////////////////////////////
// Function: Start a range reading on the sensor //
///////////////////////////////////////////////////
boolean start_sensor(byte bit8address){
  boolean errorlevel = 0;
  bit8address = bit8address & B11111110;               //Do a bitwise 'and' operation to force the last bit to be zero -- we are writing to the address.
  errorlevel = !i2c_start(bit8address) | errorlevel;   //Run i2c_start(address) while doing so, collect any errors where 1 = there was an error.
  errorlevel = !i2c_write(81) | errorlevel;            //Send the 'take range reading' command. (notice how the library has error = 0 so I had to use "!" (not) to invert the error)
  i2c_stop();
  return errorlevel;
}

///////////////////////////////////////////////////////////////////////
// Function: Read the range from the sensor at the specified address //
///////////////////////////////////////////////////////////////////////
//Uses the I2C library to read a sensor at the given address
//Collects errors and reports an invalid range of "0" if there was a problem.
//INPUTS: byte  bit8address = the address of the sensor to read from
//OUPUTS: int   range = the distance in cm that the sensor reported; if "0" there was a communication error
int read_sensor(byte bit8address){
  boolean errorlevel = 0;
  int range = 0;
  byte range_highbyte = 0;
  byte range_lowbyte = 0;
  bit8address = bit8address | B00000001;  //Do a bitwise 'or' operation to force the last bit to be 'one' -- we are reading from the address.
  errorlevel = !i2c_start(bit8address) | errorlevel;
  range_highbyte = i2c_read(0);           //Read a byte and send an ACK (acknowledge)
  range_lowbyte  = i2c_read(1);           //Read a byte and send a NACK to terminate the transmission
  i2c_stop();
  range = (range_highbyte * 256) + range_lowbyte;  //compile the range integer from the two bytes received.
  if(errorlevel){
    return 0;
  }
  else{
    return range;
  }
}

/////////////////////////////////////////
// Function: Change the sensor address //
/////////////////////////////////////////
boolean change_address(byte oldaddress,byte newaddress){
  //note that the new address will only work as an even number (odd numbers will round down)
  boolean errorlevel = 0;
  oldaddress = oldaddress & B11111110;  //Do a bitwise 'and' operation to force the last bit to be zero -- we are writing to the address.
  errorlevel = !i2c_start(oldaddress) | errorlevel; //Start communication at the new address and track error codes
  errorlevel = !i2c_write(170) | errorlevel;        //Send the unlock code and track the error codes
  errorlevel = !i2c_write(165) | errorlevel;        //Send the unlock code and track the error codes
  errorlevel = !i2c_write(newaddress) | errorlevel; //Send the new address
  i2c_stop();
  return errorlevel;
}

//////////////////////////////////////////////////////////
// Read the sensor at the default address //
//////////////////////////////////////////////////////////
bool read_the_sensor_example(int addr){
  boolean error = 0;  //Create a bit to check for catch errors as needed.
  int range;
  int sensor_range = 0 ;  
  //Take a range reading at the default address of 224
  for(int i =0; i < AVG_VAL; i++){
    error = start_sensor(addr);    //Start the sensor and collect any error codes.
    if (!error){                  //If you had an error starting the sensor there is little point in reading it as you will get old data.
      delay(100);
      range = read_sensor(addr);   //reading the sensor will return an integer value -- if this value is 0 there was an error
      sensor_range += range;
      //Serial.print("R:");Serial.println(range);
    }
  }
  if ((sensor_range/AVG_VAL)<60 && (sensor_range/AVG_VAL)>20){
   Serial.print("AVG_VAL:");Serial.print(addr);Serial.print("    ");Serial.println(sensor_range/AVG_VAL);
    return 1;
  }
  else {
    Serial.print("AVG_VAL:");Serial.print(addr);Serial.print("    ");Serial.println(sensor_range/AVG_VAL);
    return 0;}
  }

void test_read(int addr){
  start_sensor(addr);
  delay(100);
  int range;
  while(1){
    range = read_sensor(addr);   //reading the sensor will return an integer value -- if this value is 0 there was an error
    Serial.print("R:");Serial.println(range);
  }
  }
