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
InputPinMQTT input_D4(&control, D5);
InputPinMQTT input_D5(&control, D6);
InputPinMQTT input_D6(&control, D7);
InputPinMQTT input_D7(&control, D8);
OutputPinMQTT output_D2(&control, D0);
OutputPinMQTT output_D3(&control, D1);
NeopixelPinMQTT pixels(&control);

InputPinMQTT inputs[] = { input_D4, input_D5, input_D6, input_D7 };
OutputPinMQTT outputs[] = { output_D2, output_D3 };

//Button button(&control);
//ModuleOta ota;

void setup()
{
	Serial.begin(SERIAL_BAUD);

	ErrorHandler().setErrorHandler(onError);

	neopixel.setBlink(false);
	neopixel.forceColor(CRGB::White);

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

	mqtt.begin();


	auto handleInputs = [](int code, long param, String msg) -> void {
		String pin = msg;
		String getTopic = String(MQTT_TOPIC_ROOT) + "/" + pin;
		String payload;

		if (param) {
			payload = "1";
		}
		else {
			payload = "0";
		}
		mqtt.publish(getTopic, payload);
	};

	control.addEventListener(Events::EV_INPUTPIN_CHANGE, handleInputs);

	mqtt.setOnMessageHandler([](String topic, String message) -> void {

		for (int i = 0; i < 2; i++)
		{
			if (topic == outputs[i].getTopic()) {
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

		if (topic == pixels.getTopic()) {
			pixels.set(message);
		}
	});

	pixels.set("XRGBX");
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

	for (int i = 0; i < 4; i++)
	{
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