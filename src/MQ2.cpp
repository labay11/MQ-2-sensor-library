#include "Arduino.h"
#include "MQ2.h"

MQ2::MQ2(int pin) {
  _pin = pin;
  Ro = -1.0;
}

void MQ2::begin(){
    Ro = MQCalibration();
    Serial.print("Ro: ");
    Serial.print(Ro);
    Serial.println(" kohm");
}

void MQ2::close(){
	Ro = -1.0;
	values[0] = 0.0;
	values[1] = 0.0;
	values[2] = 0.0;
}

bool MQ2::checkCalibration() {
	if (Ro < 0.0) {
		Serial.println("Device not calibrated, call MQ2::begin before reading any value.");
		return false;
	}

	return true;
}

float* MQ2::read(bool print){
	if (!checkCalibration()) return NULL;

   values[0] = MQGetPercentage(LPGCurve);
   values[1] = MQGetPercentage(COCurve);
   values[2] = MQGetPercentage(SmokeCurve);

   lastReadTime = millis();

   if (print){
       Serial.print("LPG:");
       Serial.print(values[0]);
       Serial.print("ppm\t");
       Serial.print("CO:");
       Serial.print(values[1]);
       Serial.print("ppm\t");
       Serial.print("SMOKE:");
       Serial.print(values[2]);
       Serial.print("ppm\n");
   }
   return values;
}

float MQ2::readLPG(){
	if (!checkCalibration()) return 0.0;

    if (millis()<(lastReadTime + READ_DELAY) && values[0] > 0)
        return values[0];
    else
        return (values[0] = MQGetPercentage(LPGCurve));
}

float MQ2::readCO(){
	if (!checkCalibration()) return 0.0;

    if (millis()<(lastReadTime + READ_DELAY) && values[1] > 0)
        return values[1];
    else
        return (values[1] = MQGetPercentage(COCurve));
}

float MQ2::readSmoke(){
	if (!checkCalibration()) return 0.0;

    if (millis()<(lastReadTime + READ_DELAY) && values[2] > 0)
        return values[2];
    else
        return (values[2] = MQGetPercentage(SmokeCurve));
}

float MQ2::MQResistanceCalculation(int raw_adc) {
   return (((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQ2::MQCalibration() {
	float val=0.0;

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
	float rs=0.0;
	int val = analogRead(_pin);

	for (i=0;i<READ_SAMPLE_TIMES;i++) {
		rs += MQResistanceCalculation(val);
		delay(READ_SAMPLE_INTERVAL);
	}

	rs = rs/READ_SAMPLE_TIMES;
	return rs;  
}

int MQ2::MQGetPercentage(float *pcurve) {
	float rs_ro_ratio = MQRead() / Ro;
	return (pow(10.0,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
