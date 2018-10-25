#ifdef WIFI_ENABLE

#include <ESP8266WiFi.h>

//WIFI configuration
const char* WIFI_SSID = "IoT Base"; //define your wifi SSID
const char* WIFI_PASS = THIS_IS_MY_PASSWORD; //sefine your wifi password
const char* WIFI_NAME = "TouchModule";

void wifi_setup()
{
	Serial.println("");
	Serial.print("Connecting to ");
	Serial.println(WIFI_SSID);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	WiFi.hostname(WIFI_NAME);
	Serial.print("   IP address: ");
	Serial.println(WiFi.localIP());

}

#else

void wifi_setup() {}

#endif // WIFI_ENABLE