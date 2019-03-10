#ifndef MODULEWIFI_H
#define MODULEWIFI_H

#include "module.h"

#include <ESP8266WiFi.h>

class ModuleWifi {

private:
	String _ssid = MY_WIFI_SSID;
	String _pass = MY_WIFI_PASSWORD;
	String _name = BOARD_NAME;

protected:
	Control *control;

public:
	ModuleWifi(Control *c) {
		control = c;
	}

	ModuleWifi(Control *c, String ssid, String pass, String name) {
		control = c;
		_ssid = ssid;
		_pass = pass;
		_name = name;
	}

	void begin()
	{
		log_logln();
		log_log(F("Connecting to "));
		log_logln(_ssid);

		int count = 0;

		WiFi.begin(_ssid.c_str(), _pass.c_str());
		while (WiFi.status() != WL_CONNECTED) {
			count++;
			if (count > 120) {
				control->fireEvent(Events::EV_MODULE_ERROR, YELLOW_ERROR_CODE, "Can't connect to a wifi network");
				control->fireEvent(Events::EV_MODULE_RESTART, 0, "");
				return;
			}
			else {
				log_log(".");
			}
			delay(1000);
		}

		//WiFi.hostname(WIFI_NAME);
		log_log(F("   IP address: "));
		log_logln(WiFi.localIP());
	}

	void loop() {

		int count = 0;

		if (WiFi.status() != WL_CONNECTED) {
			log_logln();
			log_log(F("Connecting to "));
			log_logln(_ssid);

			while (WiFi.status() != WL_CONNECTED) {

				count++;
				if (count > 60) {
					control->fireEvent(Events::EV_MODULE_ERROR, YELLOW_ERROR_CODE, "Can't connect to a wifi network");
					control->fireEvent(Events::EV_MODULE_RESTART, 0, "");
					return;
				}
				else {
					log_log(".");
				}
				delay(1000);
			}
		}

	}
};

#endif // WIFI_ENABLE