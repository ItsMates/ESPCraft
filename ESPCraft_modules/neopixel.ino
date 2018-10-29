#ifdef NEOPIXEL_PIN

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void neopixel_setup() {
	pixels.begin();
	mqtt_subscribe(MQTT_NEOPIXEL_TOPIC);

	module_addEventListener(Events::EV_CHANGE_NEOPIXEL, [](int code, long param, char* message)->void
	{
		pixels.setPixelColor(0, param);
		pixels.show();
	});
}

void neopixel_setState(long color) {
	module_fireEvent(Events::EV_CHANGE_NEOPIXEL, color, NO_MESSAGE);
}

long neopixel_color(int r, int g, int b) {
	return pixels.Color(r, g, b);
}

#else

void neopixel_setup() {}
void neopixel_setState(long color) {}
long neopixel_color(int r, int g, int b) {return 0;}

#endif // NEOPIXEL_PIN