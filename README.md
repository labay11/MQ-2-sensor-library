MQ-2 sensor library
===================

This is a simple library to use with the MQ-2 sensor in arduino.

Based on this page: <a href="http://sandboxelectronics.com/?p=165" target="_blank">Sandbox electronics</a>

The following page it's also useful if you want to know how to calibrate the sensor (it's for MQ-6 sensor but it works as the MQ-2 does):
<a href="http://www.savvymicrocontrollersolutions.com/index.php?sensor=mq-6-gas-sensors" target="_blank">http://www.savvymicrocontrollersolutions.com/index.php?sensor=mq-6-gas-sensors</a>

Usage
======
To intall the library to use it with the Arduino IDE, download it as zip and unzip it into your 'libraries' folder and restart the Arduino IDE.

To know how to use this library view the [sample](/arduino_sample/arduino_sample.ino).
Examples
=========
Setup:
<pre lang="cpp"><code>
  #include &#60;MQ2.h&#62;
  
  int pin = A0;
  
  MQ2 mq2(pin);
  
  void setup(){
    mq2.begin();
  }
</code></pre>

Read all data:
<pre lang="cpp"><code>
  float* values = mq2.read(true); //true to print the values in the Serial
</code></pre>

Read specific data:
<pre lang="cpp"><code>
  float lpg = mq2.readLPG();
  
  float co = mq2.readCO();
  
  float smoke = mq2.readSmoke();
</code></pre>

License
=========
Copyright 2015 labay11

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
