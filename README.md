MQ-2 sensor library
===================

This is a simple library to use with the MQ-2 sensor in arduino.
Usage
======
To intall the library to use it with the Arduino IDE, download it as zip and unzip it into your 'libraries' folder and restart the Arduino IDE.

To know how to use this library view the sample inside the 'arduino_sample' folder.
Examples
=========
Setup:
<pre lang="cpp"><code>
  #include &#60;MQ2.h&#62;
  
  int pin = A0;
  
  MQ2 mq2(pin);
</code></pre>

Read all data:
<pre lang="cpp"><code>
  float* values = mq2.read(true); //true to print to values in the Serial
</code></pre>

Read specific data:
<pre lang="cpp"><code>
  float lpg = mq2.readLPG();
  
  float co = mq2.readCO();
  
  float smoke = mq2.readSmoke();
</code></pre>
