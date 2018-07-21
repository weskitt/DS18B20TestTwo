// DS18B20.h
#include <OneWire.h>

#ifndef _DS18B20_h
#define _DS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct DS18B20Struct
{
	uint8_t index; //索引
	byte type_s;
	byte addr[8];
	//byte romData[12];
	uint8_t interval; //采样时间间隔
	float data[4]; //16 byte
	//total 1+8+1+16= 26 byte
};


class DS18B20Class
{
public:
	OneWire devices;
	byte devicesCount = 0;
	//byte DevicesCount() { return devicesCount; }
private:
	 byte present = 0;
	 DS18B20Struct ds18b20[4]; //26*4= 104 byte
	 float celsius;


 public:
	DS18B20Class(){}
	DS18B20Class(uint8_t pin) { devices.begin(pin); }
	void init(uint8_t pin);
	byte search(); //example search(newAddr);
	void getModel(uint8_t id); //example  getModel(newAddr[0])
	void readTemperature(uint8_t id);
	void printTemp(uint8_t id);
	void printAll();
	void printDevice(uint8_t id, float t= 666);
	//bool crcCheck();
};

extern DS18B20Class DS18B20;

#endif

