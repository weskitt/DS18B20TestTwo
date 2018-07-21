#include "DS18B20.h"
#include <Wire.h>

enum COMMANDS { ReqTemp, ReqTempByAddr, ReqTempPack, Req_DS18B20_Count };
String IndexCommands[4]{ "ReqTemp", "ReqTempByAddr", "ReqTempPack", "Req_DS18B20_Count" };
//OneWire  ds18b20(5);  // 连接arduino5引脚
DS18B20Class ds;
uint8_t command;

void setup(void) {
	Wire.begin(4);  // 加入I2C总线，设置从机4
	Wire.onReceive(receiveEvent); //接收主机发来的数据
	Wire.onRequest(requestEvent); //向主机发送数据
	Serial.begin(115200);
	ds.init(4);
}

void loop(void) {
	ds.printAll();
	//ds.printTemp(1);
	//Serial.println("Wati command ...");
	delay(500);
}

void receiveEvent(int count)  //读取指令
{
	readCommand();
	Serial.print("Recived command : ");
	Serial.println(IndexCommands[command]);
}

void readCommand()
{
	if ( Wire.available()>1 || Wire.available()<0 ){
		Serial.print("Erro Command:");
		Serial.println(Wire.readString());
	}
	else if(Wire.available() == 0)
		Serial.println("  No data online! ");
		
	else
		command = Wire.read(); //读取主机发来的指令
}

void requestEvent()
{
	//String RequestedContent;
	char tempt;

	switch (command)
	{
	case Req_DS18B20_Count:
		//itoa(ds.devicesCount, &tempt, 10);
		//RequestedContent = "  ---Reply : DS18b20 count is ";
		//RequestedContent += tempt;
		Wire.write(ds.devicesCount);
		break;
	case ReqTemp:
		//RequestedContent = "  ---Reply : ";
		//ds.printAll();
		//Wire.write(RequestedContent.c_str());
		break;
		
	default:
		break;
	}
}