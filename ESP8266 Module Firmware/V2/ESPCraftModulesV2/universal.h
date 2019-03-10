// universal.h

#ifndef _UNIVERSAL_h
#define _UNIVERSAL_h

#include <FastLED.h>
#include "module.h"




class PinMQTT
{

private:

protected:
	Control * control;
	int pin;

	static String getPinName(int pin) {
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

public:

	PinMQTT(Control * c, int gpio) {
		control = c;
		pin = gpio;
	}


};




class InputPinMQTT : PinMQTT
{
private:
	
	boolean _state = LOW;
	boolean _stateLast = LOW;

	void _update(bool state)
	{
		_state = state;

		if (_state != _stateLast) {
			_stateLast = _state;

			if (_state == HIGH) {
				log_debug("INPUT "); log_debug(getPinName(pin)); log_debugln(" HIGH");
				control->fireEvent(Events::EV_INPUTPIN_CHANGE, HIGH, getPinName(pin));
			}
			else {
				log_debug("INPUT "); log_debug(getPinName(pin)); log_debugln(" LOW");
				control->fireEvent(Events::EV_INPUTPIN_CHANGE, LOW, getPinName(pin));
			}
		}
	}

	bool _read() {
		return !digitalRead(pin);
	}

public:
	InputPinMQTT(Control * c, int pin) : PinMQTT( c,  pin) {
	}

	void begin() {
		pinMode(pin, INPUT_PULLUP);
	}

	bool get() {
		return _state;
	}

	void loop() {
		_update(_read());
	}

	String getPin() {
		return getPinName(pin);
	}

	String getTopic() {
		return String(MQTT_TOPIC_ROOT) + String("/") + String(getPin());
	}
};




class OutputPinMQTT : PinMQTT
{
private:
	
public:
	OutputPinMQTT(Control * c, int pin) : PinMQTT(c, pin) {
	
	}

	

	void begin() {
		pinMode(pin, OUTPUT);
	}

	void set(bool state) {
		digitalWrite(pin, state);
	}

	String getTopic() {
		return String(MQTT_TOPIC_ROOT) + String("/") + String(getPin());
	}

	String getPin() {
		return getPinName(pin);
	}

	
};




class NeopixelPinMQTT : PinMQTT
{
private:
	static const int _count = 32;
	CRGB _pixels[_count];

public:

	NeopixelPinMQTT(Control * c) : PinMQTT(c, PIXELS_PIN) {

	}

	void begin() {		
		FastLED.addLeds<LED_TYPE, PIXELS_PIN, COLOR_ORDER>(_pixels, NUM_LEDS);
	}

	//RRGBX
	void set(String code) {
		for (unsigned int i = 0; i < code.length(); i++)
		{
			char c = code.charAt(i);
			switch (c)
			{
			case 'R': 
				_pixels[i] = CRGB::Red;
				break;
			case 'G':
				_pixels[i] = CRGB::Green;
				break;
			case 'B':
				_pixels[i] = CRGB::Blue;
				break;
			case 'W':
				_pixels[i] = CRGB::White;
				break;
			case 'X':
				_pixels[i] = CRGB::Black;
				break;
			default:
				break;
			}			
		}
		FastLED.show();
	}

	void clear() {
		for (int i = 0; i < NUM_LEDS; i++)
		{
			_pixels[i] = CRGB::Black;
		}
		FastLED.show();
	}

	String getPin() {
		return getPinName(pin);
	}

	String getTopic() {
		return String(MQTT_TOPIC_ROOT) + String("/") + String(getPin());
	}
};


#endif
