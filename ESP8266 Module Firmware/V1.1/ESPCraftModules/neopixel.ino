#ifdef NEOPIXEL_PIN

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void neopixel_setup() {
	pixels.begin();
	//mqtt_subscribe(MQTT_NEOPIXEL_TOPIC);
	mqtt_subscribe(MQTT_NEOPIXEL_R_TOPIC);
	mqtt_subscribe(MQTT_NEOPIXEL_G_TOPIC);
	mqtt_subscribe(MQTT_NEOPIXEL_B_TOPIC);

	module_addEventListener(Events::EV_CHANGE_NEOPIXEL, [](int code, long param, String message)->void
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

byte neopixel_r(unsigned long color) {
	return (byte)(color >> 16);
}

byte neopixel_g(unsigned long color) {
	return (byte)(color >> 8);
}
byte neopixel_b(unsigned long color) {
	return (byte)color;
}

#else

void neopixel_setup() {}
void neopixel_setState(long color) {}
long neopixel_color(int r, int g, int b) {return 0;}
byte neopixel_r(unsigned long color) {return 0;}
byte neopixel_g(unsigned long color) {return 0;}
byte neopixel_b(unsigned long color) {return 0;}

#endif // NEOPIXEL_PIN