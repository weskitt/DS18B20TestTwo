//#include <OneWire.h>
#include "DS18B20.h"


//OneWire  ds18b20(5);  // 连接arduino5引脚
DS18B20Class ds(5);




void setup(void) {
	Serial.begin(115200);
	//ds.init(5);
	ds.search();
}

void loop(void) {
	ds.printTemp(0);
	ds.printTemp(1);
}