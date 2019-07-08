#include "Arduino.h"
#include "MQ2.h"

MQ2::MQ2(int pin) {
  _pin = pin;
}
void MQ2::begin(){
    Ro = MQCalibration();
    Serial.print("Ro: ");
    Serial.print(Ro);
    Serial.println(" kohm");
}

float* MQ2::read(bool print){

   lpg = MQGetGasPercentage(MQRead()/Ro,GAS_LPG);
   co = MQGetGasPercentage(MQRead()/Ro,GAS_CO);
   smoke = MQGetGasPercentage(MQRead()/Ro,GAS_SMOKE);

   if (print){
       Serial.print("LPG:");
       Serial.print(lpg);
       Serial.print( "ppm" );
       Serial.print("    ");
       Serial.print("CO:");
       Serial.print(co);
       Serial.print( "ppm" );
       Serial.print("    ");
       Serial.print("SMOKE:");
       Serial.print(smoke);
       Serial.print( "ppm" );
       Serial.print("\n");
   }
   lastReadTime = millis();
   static float values[3] = {lpg,co,smoke};
   return values;
}

float MQ2::readLPG(){
    if (millis()<(lastReadTime + 10000) && lpg != 0){
        return lpg;
    }else{
        return lpg = MQGetGasPercentage(MQRead()/10,GAS_LPG);
    }
}

float MQ2::readCO(){
    if (millis()<(lastReadTime + 10000) && co != 0){
        return co;
    }else{
        return co = MQGetGasPercentage(MQRead()/10,GAS_CO);
    }
}

float MQ2::readSmoke(){
    if (millis()<(lastReadTime + 10000) && smoke != 0){
        return smoke;
    }else{
        return smoke = MQGetGasPercentage(MQRead()/10,GAS_SMOKE);
    }
}

float MQ2::MQResistanceCalculation(int raw_adc) {
   return (((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQ2::MQCalibration() {
  float val=0;
 
  for (int i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
  return val; 
}
float MQ2::MQRead() {
  int i;
  float rs=0;
  int val = analogRead(_pin);

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(val);
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}
float MQ2::MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
  return 0;
}
int MQ2::MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
