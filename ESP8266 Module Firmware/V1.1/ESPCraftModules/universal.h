// universal.h

#ifndef _UNIVERSAL_h
#define _UNIVERSAL_h

#include <Adafruit_NeoPixel.h>
#include "definitions.h"


int OUTPUTS[] = { D0,D1 };
int INPUTS[] = { D0,D1 };
int NEOPIXEL[] = { D0,D1 };

class ModuleMQTT
{
public:
	ModuleMQTT() {}


private:

};


class PinMQTT
{

private:

	String _getPinName(int pin) {
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
			return "X";
			break;
		}
	}

public:
	PinMQTT() {}

protected:
	String topic(int pin) {
		return String(MQTT_ROOT_TOPIC) + String("/") + String(_getPinName(pin));
	}

};

class InputPinMQTT : PinMQTT
{
private:
	int _pin;
	boolean _state = LOW;

	void _update(bool state)
	{
		static boolean lastState = LOW;
		_state = state;

		if (_state != lastState) {
			lastState = _state;

			if (_state == HIGH) {
				log_debug("INPUT "); log_debug(_pin); log_debugln(" HIGH")
					module_fireEvent(Events::EV_MQTT_PUBLISH, HIGH, topic(_pin));
			}
			else {
				log_debug("INPUT "); log_debug(_pin); log_debugln(" LOW")
					module_fireEvent(Events::EV_MQTT_PUBLISH, LOW, topic(_pin));
			}
		}
	}

	bool _read() {
		return !digitalRead(_pin);
	}

public:
	InputPinMQTT(int pin) {
		_pin = pin;
	}

	void begin() {
		pinMode(_pin, INPUT_PULLUP);
		mqtt_subscribe(MQTT_BUTTON_TOPIC);
	}

	bool get() {
		return _state;
	}

	void loop() {
		static boolean previous = LOW;
		_update(_read());
	}




};

class OutputPinMQTT : PinMQTT
{
private:
	int _pin;

public:
	OutputPinMQTT(int pin) {
		_pin = pin;
	}

	void begin() {
	
	}


};



class NeopixelPinMQTT : PinMQTT
{
private:
	Adafruit_NeoPixel pixels;
	int _pin;

public:
	NeopixelPinMQTT(int pin) {
		_pin = pin;
		pixels = Adafruit_NeoPixel(32, _pin, NEO_GRB + NEO_KHZ800);
	}
	
	void begin() {
		module_addEventListener(Events::EV_CHANGE_NEOPIXEL, onEvent);
	}

	EventListener onEvent(int code, long param, String message) {
		pixels.setPixelColor(0, param);
		pixels.show();
	}

	void setState(long color) {
		module_fireEvent(Events::EV_CHANGE_NEOPIXEL, color, NO_MESSAGE);
	}

	long getColor(int r, int g, int b) {
		return pixels.Color(r, g, b);
	}

	byte getR(unsigned long color) {
		return (byte)(color >> 16);
	}

	byte getG(unsigned long color) {
		return (byte)(color >> 8);
	}
	byte getB(unsigned long color) {
		return (byte)color;
	}


};


#endif
