//#include <OneWire.h>
#include "DS18B20.h"
#include <Wire.h>


//OneWire  ds18b20(5);  // 连接arduino5引脚
DS18B20Class ds;




void setup(void) {
	Wire.begin(4);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	Serial.begin(115200);
	ds.init(12);
}

void loop(void) {
	ds.printAll();
	//ds.printTemp(1);
}

void receiveEvent(int count)
{
	while (Wire.available()>1)  // 循环执行，直到数据包只剩下最后一个字符
	{
		char c = Wire.read();  // 作为字符接收字节
		Serial.print(c);
	}

	int x = Wire.read();  // 作为整数接收字节
	Serial.println(x);
}

void requestEvent()
{
	//把接收主机发送的数据包中的最后一个字节再上传给主机
	int x = 1;
	Wire.write(x) // 响应主机的通知，向主机发送一个字节数据
}