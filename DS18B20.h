// DS18B20.h
#include <OneWire.h>

#ifndef _DS18B20_h
#define _DS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DS18B20Class
{
public:
	OneWire devices;
private:

	 byte index;
	 byte present = 0;
	 byte type_s;
	 byte data[12];
	 byte addr[8];
	 byte addrs[8][8];
	 float celsius, fahrenheit;


 public:
	DS18B20Class(){}
	DS18B20Class(uint8_t pin) { devices.begin(pin); }
	//void init(uint8_t pin);
	bool search(); //example search(newAddr);
	void getModel(byte value); //example  getModel(newAddr[0])
	void requestConvert();
	void readTemperature(int id);
	void printTemp(int id);
	void printDevice(int id, float t= 666);
};

extern DS18B20Class DS18B20;

#endif

