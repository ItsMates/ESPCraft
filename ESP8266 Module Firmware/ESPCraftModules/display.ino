#ifdef DISPLAY_ADRESS

#include "Adafruit_SSD1306.h"

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void display_setup() {
	display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADRESS);
	display.display();

	mqtt_subscribe(MQTT_DISPLAY_TOPIC);

	module_addEventListener(Events::EV_CHANGE_DISPLAY, [](int code, long param, String message)->void
	{
		display.clearDisplay();
		display.setTextSize(0);
		display.setTextColor(WHITE);
		display.setCursor(0, 0);
		display.println(String(message));
		display.display();
	});
}

void display_setState(String message) {
	module_fireEvent(Events::EV_CHANGE_DISPLAY, 0, message);
}

#else

void display_setup() {}
void display_setState(char* message) {}

#endif // DISPLAY_PIN