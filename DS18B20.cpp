// 
// 
// 

#include "DS18B20.h"


bool DS18B20Class::search()
{
	Serial.println();
	for(int id=0; id<8; id++)
	{
		if (devices.search(addrs[id])) {
			printDevice(id);
			if (OneWire::crc8(addrs[id], 7) != addrs[id][7]) 
				Serial.println("CRC is not valid!");

			//
		}
		else {
			//Serial.println();
			Serial.println("No more addresses.");
			devices.reset_search();
			delay(250);

			break;
		}
	}
	//return false;
}

void DS18B20Class::getModel(byte value)
{
	switch (value) {
	case 0x10:
		Serial.print("  Chip = DS18S20  ");  // or old DS1820
		type_s = 1;
		break;
	case 0x28:
		Serial.print("  Chip = DS18B20  ");
		type_s = 0;
		break;
	case 0x22:
		Serial.print("  Chip = DS1822  ");
		type_s = 0;
		break;
	default:
		Serial.println("  Device is not a DS18x20 family device.  ");
		return;
	}
}

void DS18B20Class::requestConvert()
{
	devices.reset();
	devices.select(addr);
	devices.write(0x44, 1);         // start conversion, with parasite power on at the end

	delay(1000);     // maybe 750ms is enough, maybe not
					 // we might do a ds.depower() here, but the reset will take care of it.
}

void DS18B20Class::readTemperature(int id)
{
	devices.reset();
	devices.select(addrs[id]);
	devices.write(0x44, 1);         // start conversion, with parasite power on at the end

	delay(1000);     // maybe 750ms is enough, maybe not
					 // we might do a ds.depower() here, but the reset will take care of it.

	present = devices.reset();
	devices.select(addrs[id]);
	devices.write(0xBE);         // Read Scratchpad

	//Serial.print("  Data = ");
	//Serial.print(present, HEX);
	//Serial.print(" ");
	for (index = 0; index < 9; index++) {           // we need 9 bytes
		data[index] = devices.read();
		//Serial.print(data[index], HEX);
		//Serial.print(" ");
	}
	//Serial.print(" CRC=");
	//Serial.print(OneWire::crc8(data, 8), HEX);
	//Serial.println();

	// convert the data to actual temperature

	unsigned int raw = (data[1] << 8) | data[0];
	if (type_s) {
		raw = raw << 3; // 9 bit resolution default
		if (data[7] == 0x10) {
			// count remain gives full 12 bit resolution
			raw = (raw & 0xFFF0) + 12 - data[6];
		}
	}
	else {
		byte cfg = (data[4] & 0x60);
		if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
		else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
		else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
											  // default is 12 bit resolution, 750 ms conversion time
	}

	celsius = (float)raw / 16.0;
	//fahrenheit = celsius * 1.8 + 32.0;
}

void DS18B20Class::printTemp(int id)
{
	
	readTemperature(id);
	printDevice(id, celsius);
	//Serial.print("   Temperature = ");
	//Serial.print(celsius);
	//Serial.println(" C ");
	//Serial.print(fahrenheit);
	//Serial.println(" �H");
}

void DS18B20Class::printDevice(int id, float t)
{
	Serial.print("ID:");
	Serial.print(id);
	getModel(addrs[id][0]);
	Serial.print("Address: ");
	for (index = 0; index < 8; index++) {
		Serial.print(addrs[id][index], HEX);
		if (index<7) Serial.write('-');
	}

	if (t != 666.0)
	{
		Serial.print("   Temperature = ");
		Serial.print(t);
		Serial.print(" C ");
	}
	Serial.println();
}


DS18B20Class DS18B20;
