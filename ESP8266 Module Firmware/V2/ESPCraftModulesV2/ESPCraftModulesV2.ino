#include "universal.h"
#include "ErrorHandler.h"
#include "definitions.h"

#include "module.h"
#include "wifi_.h"
#include "mqtt_.h"
#include "neopixel.h"
#include "universal.h"
//#include "button.h"
//#include "ota_.h"

struct ModuleControl {
public:
	bool Running = false;
};

ModuleControl status;

Control control;
ModuleWifi wifi(&control);
ModuleMqtt mqtt(&control);
Neopixel neopixel(&control);
InputPinMQTT input_D5(&control, PIN_D5);
InputPinMQTT input_D6(&control, PIN_D6);
InputPinMQTT input_D7(&control, PIN_D7);
InputPinMQTT input_D8(&control, PIN_D8);
OutputPinMQTT output_D0(&control, PIN_D0);
OutputPinMQTT output_D1(&control, PIN_D1);
NeopixelPinMQTT pixels(&control);

InputPinMQTT inputs[] = {input_D5, input_D6, input_D7 , input_D8, };
OutputPinMQTT outputs[] = { output_D0, output_D1 };

//Button button(&control);
//ModuleOta ota;

void setup()
{
	delay(1000);

	Serial.begin(SERIAL_BAUD);

	neopixel.begin();
	neopixel.setBlink(false);
	neopixel.forceColor(CRGB::White);

	ErrorHandler().setErrorHandler(onError);

	pixels.begin();
	pixels.set("GXXXXXXX");

	for (int i = 0; i < 4; i++) {
		inputs[i].begin();
	}

	for (int i = 0; i < 2; i++) {
		outputs[i].begin();
	}

	wifi.begin();

	//#ifdef OTA_ENABLE
	//
	//	if (button.read()) {
	//		neopixel.setBlink(true);
	//		neopixel.setColor(CRGB::White);
	//
	//		ota.setup();
	//		while (true) {
	//			ota.loop();
	//			neopixel.loop();
	//		}
	//	}
	//	else {
	//		//ota.setup();
	//	}
	//
	//#endif // OTA_ENABLE

	//sending

	control.addEventListener(Events::EV_INPUTPIN_CHANGE, [](int code, long param, String msg) -> void {
		String pin = msg;
		String topic = String(MQTT_TOPIC_ROOT) + "/" + pin;
		String payload;

		if (param) {
			payload = "1";
		}
		else {
			payload = "0";
		}
		mqtt.publish(topic, payload);
	});

	//receiving

	mqtt.setOnMessageHandler([](String topic, String message) -> void {

		for (int i = 0; i < 2; i++)
		{
			if (topic == outputs[i].getPinTopic()) {
				if (message == "1" || message == "ON" || message == "TRUE" || message == "HIGH") {
					outputs[i].set(HIGH);
					return;
				}
				if (message == "0" || message == "OFF" || message == "FALSE" || message == "LOW") {
					outputs[i].set(LOW);
					return;
				}
			}
		}

		if (topic == pixels.getPinTopic()) {
			pixels.set(message);
		}
	});

	mqtt.subscribe(outputs[0].getPinTopic());
	mqtt.subscribe(outputs[1].getPinTopic());
	mqtt.subscribe(pixels.getPinTopic());

	mqtt.begin();

	neopixel.setBlink(true);
	neopixel.setColor(CRGB(0,32,0));
	
}

void onError(long param, String message) {
	CRGB color = neopixel.getColor();

	neopixel.forceColor(CRGB::Black);

	/*for (size_t i = 0; i < 3; i++)
	{
		buzzer.force(HIGH);
		delay(100);
		buzzer.force(LOW);
		delay(100);
	}*/

	delay(1000);

	if (param != 0) {
		neopixel.forceColor(CRGB(param));
		delay(500);
	}

	neopixel.forceColor(color);
}

// Add the main program code into the continuous loop() function
void loop()
{
	wifi.loop();
	//ota.loop();
	mqtt.loop();
	neopixel.loop();

	for (int i = 0; i < 4; i++) {
		inputs[i].loop();
	}

	//process all fired events
	control.runEvents();
}



unsigned long stopwatchMillis = 0;

void stopwatchReset() {
	stopwatchMillis = millis();
}

unsigned long stopwatch() {
	return millis() - stopwatchMillis;
}