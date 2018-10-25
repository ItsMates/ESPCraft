

//// the event queue
//EventQueue module_events;
//
//// the event dispatcher
//EventDispatcher module_eventDispatcher(&module_events);

void module_setup() 
{
	neopixel_setup();
	touch_setup();
	nearir_setup();
	relay_setup();

	wifi_setup();
	mqtt_setup();
	ota_setup();
}


void module_loop() 
{
	mqtt_loop();
	ota_loop();

	//module_eventDispatcher.run();
}