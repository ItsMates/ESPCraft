// 
// 
// 

#include "universal.h"

PinMQTT::PinMQTT(Control * c, int gpio) {
	control = c;
	pin = gpio;
}

String PinMQTT::getPinName(int pin) {
	switch (pin)
	{
	case 5:
		return "D1";
		break;
	case 4:
		return "D2";
		break;
	case 0:
		return "D3";
		break;
	case 2:
		return "D4";
		break;
	case 14:
		return "D5";
		break;
	case 12:
		return "D6";
		break;
	case 13:
		return "D7";
		break;
	case 15:
		return "D8";
		break;
	case 3:
		return "RX";
		break;
	case 1:
		return "TX";
		break;
	default:
		return "";
		break;
	}
}

String PinMQTT::_getPin() {
	return getPinName(pin);
}

String PinMQTT::_getPinTopic() {
	return String(MQTT_TOPIC_ROOT) + String("/") + String(_getPin());
}