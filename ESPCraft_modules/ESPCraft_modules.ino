// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       ESPCraft_modules.ino
    Created:	25.10.2018 18:21:28
    Author:     MATES-PC\Mates
*/




#include "EventDispatcher.h"
#include "EventQueue.h"
#include "EventDispatcher.h"
#include "Events.h"

void setup()
{
	Serial.begin(115200);

	module_setup();
}

void loop()
{
	module_loop();

	if (getTouch()) 
	{
		setNeopixel(0, 255, 0);

		mqtt_publish("Touch", "true");

		while (getTouch());
	}
	else 
	{
		setNeopixel(255, 0, 0);
	}

	if (getNearir())
	{
		setRelay(true);
	}
	else
	{
		setRelay(false);
	}

	delay(10);
}

