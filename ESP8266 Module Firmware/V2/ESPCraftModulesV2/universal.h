// universal.h

#ifndef _UNIVERSAL_h
#define _UNIVERSAL_h

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include "module.h"

class PinMQTT
{

private:

protected:
	Control * control;
	int pin;

	static String getPinName(int pin);

	PinMQTT(Control * c, int gpio);
	String _getPin();
	String _getPinTopic();

public:
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
				control->fireEvent(Events::EV_INPUTPIN_CHANGE, !HIGH, getPinName(pin));
			}
			else {
				log_debug("INPUT "); log_debug(getPinName(pin)); log_debugln(" LOW");
				control->fireEvent(Events::EV_INPUTPIN_CHANGE, !LOW, getPinName(pin));
			}
		}
	}

	bool _read() {
		return !digitalRead(pin);
	}

public:
	InputPinMQTT(Control * c, int pin) : PinMQTT( c,  pin) {
		pinMode(pin, INPUT_PULLUP);
	}

	void begin() {
		loop();
	}

	bool get() {
		return _state;
	}

	void loop() {
		_update(_read());
	}

	String getPin() {
		return _getPin();
	}

	String getPinTopic() {
		return _getPinTopic();
	}
};




class OutputPinMQTT : PinMQTT
{
private:
	
public:
	OutputPinMQTT(Control * c, int pin) : PinMQTT(c, pin) {
		pinMode(pin, OUTPUT);
	}

	void begin() {
		set(false);
	}

	void set(bool state) {
		digitalWrite(pin, state);
	}

	String getPin() {
		return _getPin();
	}

	String getPinTopic() {
		return _getPinTopic();
	}
};




class NeopixelPinMQTT : PinMQTT
{

private:
	static const int _count = NUM_LEDS;
	CRGB _pixels[_count];

public:

	NeopixelPinMQTT(Control * c) : PinMQTT(c, PIXELS_PIN) {
		FastLED.addLeds<LED_TYPE, PIXELS_PIN, COLOR_ORDER>(_pixels, NUM_LEDS);
	}

	void begin() {		
		for (int i = 0; i < _count; i++) {
			_pixels[i] = CRGB(0,25,0);
		}
		FastLED.show();
	}

	//RRGBX
	void set(String code) {

		log_debug("Setting pixels: ");
		log_debugln(code);

		//log_debugln("Decoding..");
		for (unsigned int i = 0; i < code.length(); i++)
		{
			char c = code.charAt(i);
			//log_debugln(c);
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
		//log_debugln("Showing");
		FastLED.show();
	}

	void clear() {
		for (int i = 0; i < _count; i++) {
			_pixels[i] = CRGB::Black;
		}
		FastLED.show();
	}

	String getPin() {
		return _getPin();
	}

	String getPinTopic() {
		return _getPinTopic();
	}
};


#endif
