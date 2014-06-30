#include <MQ2.h>

//change this with the pin that you use
int pin = A0;
int lpg, co, smoke;

MQ2 mq2(pin);

void setup(){
}

void loop(){
  
  /*read the values from the sensor, it returns
  *an array which contains 3 values.
  * 1 = LPG in ppm
  * 2 = CO in ppm
  * 3 = SMOKE in ppm
  */
  float* values= mq2.read(true); //set it false if you don't want to print the values in the console
  
  //lpg = values[0];
  //co = values[1];
  //smoke = values[2];
  
  delay(1000);
}

