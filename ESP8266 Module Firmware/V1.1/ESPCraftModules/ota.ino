
#ifdef OTA_ENABLE

#include <ESP8266mDNS.h>  
#include <WiFiUdp.h>      
#include <ArduinoOTA.h>   

#include "definitions.h"

//Necesary to make Arduino Software autodetect OTA device
WiFiServer TelnetServer(8266);

void ota_setup() {

	log_log("Configuring OTA device...");
	TelnetServer.begin();   //Necesary to make Arduino Software autodetect OTA device

	ArduinoOTA.onStart([]() {
		log_logln("OTA starting...");
	});
	ArduinoOTA.onEnd([]() {
		log_logln("OTA update finished!");
		log_logln("Rebooting...");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		log_logf("OTA in progress: %u%%\r\n", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		log_logf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) { log_logln("Auth Failed"); }
		else if (error == OTA_BEGIN_ERROR) { log_logln("Begin Failed"); }
		else if (error == OTA_CONNECT_ERROR) { log_logln("Connect Failed"); }
		else if (error == OTA_RECEIVE_ERROR) { log_logln("Receive Failed"); }
		else if (error == OTA_END_ERROR) { log_logln("End Failed"); }
	});

	ArduinoOTA.begin();
	log_logln("OTA OK");
}


void ota_loop() {
	ArduinoOTA.handle();
}

#else

void ota_setup() {}
void ota_loop() {}

#endif // OTA_ENABLE