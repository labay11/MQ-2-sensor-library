#ifndef MQ2_h
#define MQ2_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#endif

class MQ2 {
	public: 
		/*
		 * Creates the sensor by giving the pin where it is attached.
		 */
		MQ2(int pin);

		/*
		 * Initialises the sensor before getting any data.
		 * This step is necessary as it needs to be calibrated based on
		 * current air and temperature conditions.
		 */
		void begin();

		/*
		 * Stops the sensor, calibration and any read data is deleted.
		 *
		 * Pin information is kept, so just call `begin()` again
		 * to read new values, no need to create a new object.
		 */
		void close();

		/*
		 * Reads the LPG, CO and smoke data from the sensor and returns and
		 * array with the values in this order.
		 *
		 * The read procedure takes `READ_SAMPLE_TIMES` samples from the sensor
		 * every `READ_SAMPLE_INTERVAL` ms and returns the average.
		 */
		float* read(bool print);

		/*
		 * Same as before but only return the data from the specified gas.
		 */
		float readLPG();
		float readCO();
		float readSmoke();

	private:
		int _pin;
		
		int RL_VALUE = 5;     //define the load resistance on the board, in kilo ohms
		int RO_CLEAN_AIR_FACTOR = 9.83;  
		int CALIBARAION_SAMPLE_TIMES = 5; 
		int CALIBRATION_SAMPLE_INTERVAL = 50;

		int READ_SAMPLE_TIMES = 5;
		int READ_SAMPLE_INTERVAL = 50;

		float LPGCurve[3]  =  {2.3,0.21,-0.47}; 
		float COCurve[3]  =  {2.3,0.72,-0.34};   
		float SmokeCurve[3] = {2.3,0.53,-0.44};                                                       
		float Ro = -1.0;

		float values[3];  // array with the measured values in the order: lpg, CO and smoke
		
		float MQRead();
		int MQGetPercentage(float rs_ro_ratio, float *pcurve);
		float MQCalibration();
		float MQResistanceCalculation(int raw_adc);
		bool checkCalibration();

		int lastReadTime = 0;
};

//#endif
