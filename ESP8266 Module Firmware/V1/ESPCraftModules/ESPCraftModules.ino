/*
	Name:       ESPCraft_modules.ino
	Created:	25.10.2018 18:21:28
	Author:     MATES-PC\Mates
*/

#include <Wire.h>
#include <SPI.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>

#include "definitions.h"

void setup()
{
	Serial.begin(SERIAL_BAUD);
	//pinMode(A0, INPUT);

	/*Serial.println(neopixel_r(neopixel_color(1, 2, 3)));
	Serial.println(neopixel_g(neopixel_color(1, 2, 3)));
	Serial.println(neopixel_b(neopixel_color(1, 2, 3)));
*/
	module_setup();

	/*module_addEventListener(Events::EV_ACTION_NEARIR, [](int code, long param, String message) -> void
	{
		module_fireEvent(Events::EV_CHANGE_RELAY, param, NO_MESSAGE);
	});

	module_addEventListener(Events::EV_ACTION_TOUCH, [](int code, long param, String message) -> void
	{
		if (param == HIGH) {
			module_fireEvent(Events::EV_CHANGE_NEOPIXEL, neopixel_color(0, 255, 0), NO_MESSAGE);
		}
		else {
			module_fireEvent(Events::EV_CHANGE_NEOPIXEL, neopixel_color(255, 0, 0), NO_MESSAGE);
		}
	});*/
}

void loop()
{
	module_loop();

	//static unsigned long ms_last = 0;
	//if (millis() - ms_last > 250) {
	//	ms_last = millis();
	//	module_fireEvent(Events::EV_CHANGE_DISPLAY, 0, String("Analog:\n") + String(analogRead(A0)));
	//}

}

