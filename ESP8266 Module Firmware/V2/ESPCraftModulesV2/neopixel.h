#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "module.h"

#include <FastLED.h>

class Neopixel {

private:
	CRGB _pixel[1];

	bool _blinking = false;
	unsigned long _blink_delay = ALARM_BLINK_DELAY;

	CRGB _color = CRGB::Black;

	void _updatePixel(CRGB _color) {
		static CRGB col = 0;

		if (_color != col) {
			col = _color;
			_pixel[0] = _color;
			FastLED.show();
		}
	}

protected:
	Control * control;

public:
	Neopixel(Control *c) {
		control = c;
		FastLED.addLeds<NEOPIXEL, NEOPIXEL_PIN>(_pixel, 1);
		_updatePixel(CRGB::Black);
	}

	void forceColor(CRGB rgb) {
		_pixel[0] = rgb;
		FastLED.show();
	}

	void setColor(CRGB rgb) {
		_color = rgb;
	}

	CRGB getColor() {
		return _color;
	}

	void setBlink(bool blink) {
		_blinking = blink;
		_blink_delay = ALARM_BLINK_DELAY;
	}

	void setBlink(bool blink, int dylej) {
		_blinking = blink;
		_blink_delay = dylej;
	}

	void loop() {
		static unsigned long last_millis = 0;
		static bool blink = LOW;

		if (_blinking) {
			if (millis() - last_millis > _blink_delay) {
				last_millis = millis();

				blink = !blink;

				if (blink) {
					_updatePixel(CRGB::Black);
				}
				else {
					_updatePixel(_color);
				}
			}
		}
		else {
			_updatePixel(_color);
		}
	}
};

#endif