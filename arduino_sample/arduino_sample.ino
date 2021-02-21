#include <MQ2.h>

//change this with the pin that you use
int pin = A0;
float lpg, co, smoke;

MQ2 mq2(pin);

void setup(){
  Serial.begin(9600);
  
  // calibrate the device
  mq2.begin();
}

void loop(){
  
  /*
   * read the values from the sensor, it returns
   * an array which contains 3 values.
   * 0 : LPG in ppm
   * 1 : CO in ppm
   * 2 : SMOKE in ppm
   */
  float* values= mq2.read(true); //set it false if you don't want to print the values to the Serial
  
  // lpg = values[0];
  lpg = mq2.readLPG();
  // co = values[1];
  co = mq2.readCO();
  // smoke = values[2];
  smoke = mq2.readSmoke();
  
  delay(1000);
}

