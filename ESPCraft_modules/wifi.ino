#ifdef WIFI_ENABLE

#include <ESP8266WiFi.h>
#include "definitions.h"

//WIFI configuration
const char* WIFI_SSID = MY_WIFI_SSID; 
const char* WIFI_PASS = MY_WIFI_PASSWORD; 
const char* WIFI_NAME = BOARD_NAME;

void wifi_setup()
{
	log_logln();
	log_log("Connecting to ");
	log_logln(WIFI_SSID);

	int count = 0;

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED) {
		if (count > 10) {
			module_error("Can't connect to a wifi network..");
		}
		else {
			log_log(".");	
		}
		delay(500);	
	}

	WiFi.hostname(WIFI_NAME);
	log_log("   IP address: ");
	log_logln(WiFi.localIP());
}

#else

void wifi_setup() {}

#endif // WIFI_ENABLE