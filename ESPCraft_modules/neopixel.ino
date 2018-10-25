#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 4, NEO_GRB + NEO_KHZ800);

void neopixel_setup() 
{
	pixels.begin(); // NEOPIXELs

	mqtt_addListener(neopixel_mqttHandler);

}


void neopixel_test()
{
	pixels.setPixelColor(0, pixels.Color(255, 0, 0));
	pixels.show();
}

void neopixel_mqttHandler(int e, int p, char* message)
{
	pixels.setPixelColor(0, pixels.Color(100, 100, 100));
	pixels.show();
	delay(500);
}

void setNeopixel(int r, int g, int b) {
	pixels.setPixelColor(0, pixels.Color(r, g, b));
	pixels.show();
}