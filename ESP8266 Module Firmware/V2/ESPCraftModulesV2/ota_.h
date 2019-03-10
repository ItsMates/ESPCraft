//#ifndef OTA_H
//#define OTA_H
//
//
//#include <WiFi.h>
//#include <ESPmDNS.h>
//#include <WiFiUdp.h>
//#include <ArduinoOTA.h>
//
//
//class ModuleOta {
//
//public:
//	void setup() {
//
//		// Port defaults to 3232
//		// ArduinoOTA.setPort(3232);
//
//		// Hostname defaults to esp3232-[MAC]
//		ArduinoOTA.setHostname("LaserESP32");
//
//		// No authentication by default
//		// ArduinoOTA.setPassword("travickazelena");
//
//		// Password can be set with it's md5 value as well
//		// MD5(admin) = 992a372826da6e7f3bc7038e9f8d582e
//		ArduinoOTA.setPasswordHash("992a372826da6e7f3bc7038e9f8d582e");
//
//		ArduinoOTA
//			.onStart([]() {
//			String type;
//			if (ArduinoOTA.getCommand() == U_FLASH)
//				type = "sketch";
//			else // U_SPIFFS
//				type = "filesystem";
//
//			// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
//			Serial.println("Start updating " + type);
//		})
//			.onEnd([]() {
//			Serial.println("\nEnd");
//		})
//			.onProgress([](unsigned int progress, unsigned int total) {
//			Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
//		})
//			.onError([](ota_error_t error) {
//			Serial.printf("Error[%u]: ", error);
//			if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
//			else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
//			else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
//			else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
//			else if (error == OTA_END_ERROR) Serial.println("End Failed");
//		});
//
//		ArduinoOTA.begin();
//	}
//
//	void loop() {
//		ArduinoOTA.handle();
//	}
//};
//
//#endif
//
