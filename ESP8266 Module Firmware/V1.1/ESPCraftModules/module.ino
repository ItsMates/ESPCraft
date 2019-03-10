
#include "definitions.h"

// the event queue
EventQueue _module_events;

// the event dispatcher
EventDispatcher _module_eventDispatcher(&_module_events);

void module_addEventListener(int eventCode, EventListener handler){
	_module_eventDispatcher.addEventListener(eventCode, handler);
}

void module_fireEvent(int eventCode, int eventParam, String eventMessage) {
	_module_events.enqueueEvent(eventCode, eventParam, eventMessage); 
}

void module_setup() 
{
	//button_setup();
	//touch_setup();
	//nearir_setup();
	//pir_setup();
	//gesture_setup();

	//neopixel_setup();
	//display_setup();
	//relay_setup();

	wifi_setup();
	mqtt_setup();
	ota_setup();
	//eeprom_setup();
}


void module_loop() 
{
	//button_loop();
	//neopixel_loop();
	touch_loop();
	nearir_loop();
	//relay_loop();

	//wifi_loop();
	mqtt_loop();
	ota_loop();

	//process all fired events
	_module_eventDispatcher.run();
}

void module_error(String message) 
{
	Serial.println(message);
	module_fireEvent(Events::EV_CHANGE_DISPLAY, 0, message);
	module_fireEvent(Events::EV_CHANGE_NEOPIXEL, neopixel_color(50, 0, 0), "");
}