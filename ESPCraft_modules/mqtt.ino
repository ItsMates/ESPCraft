
/*

 It connects to an MQTT server then:
  - on 0 switches off relay
  - on 1 switches on relay
  - on 2 switches the state of the relay

  - sends 0 on off relay
  - sends 1 on on relay

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 The current state is stored in EEPROM and restored on bootup

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "Events.h"
#include "EventQueue.h"
#include "EventDispatcher.h"

const char* MQTT_SERVER_IP = "10.58.200.29";
const int MQTT_SERVER_PORT = 1884;

const char* MQTT_USER = "ESP Touch module";
const char* MQTT_PASSWORD = "";

const char* MQTT_TOPIC = "ESP Touch module";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* outTopic = "OUTPUT";
const char* inTopic = "INPUT";


// the event queue
EventQueue mqtt_events;

// the event dispatcher
EventDispatcher mqtt_eventDispatcher(&mqtt_events);

void mqtt_addListener(EventListener handler) {
	mqtt_eventDispatcher.addEventListener(Events::EV_MQTT, handler);
}

void mqtt_setup() {
	Serial.println("Setting up MQTT");

	mqttClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
	mqttClient.setCallback(_mqtt_callback);

	while (!mqttClient.connected()) {
		Serial.println("Connecting to MQTT...");

		if (mqttClient.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
			Serial.println("connected");
		}
		else {
			Serial.print("failed with state ");
			Serial.print(mqttClient.state());
			delay(2000);
		}
	}

	mqttClient.subscribe(inTopic);
	mqttClient.publish(outTopic, "ESP booted");
}


void _mqtt_callback(char* topic, byte* payload, unsigned int length) {
	
	char message[MQTT_PAYLOAD_MAX];
	
	Serial.print("MQTT: [");
	Serial.print(topic);
	Serial.print("] - ");
	
	//topic
	strcpy(message, topic);

	int offset = 8;
	//message
	for (int i = 0; i < (int)length; i++) {
		char c = (char)payload[i];
		Serial.print(c);
		message[i + offset] = c;
	}

	Serial.println();

	mqtt_events.enqueueEvent(Events::EV_MQTT, 0, message);    // param is not used here

}

void mqtt_reconnect() {
	Serial.println("Connecting to MQTT...");
	if (mqttClient.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
		Serial.println("connected");
	}
	else {
		Serial.print("failed with state ");
		Serial.print(mqttClient.state());
	}	
}



bool mqtt_loop() {
	while (!mqttClient.connected()) {
		mqtt_reconnect();
		delay(1000);
		return false;
	}

	mqttClient.loop();	
	mqtt_eventDispatcher.run();

	return true;
}

void mqtt_publish(String topic, String payload) {
	mqttClient.publish(topic.c_str(), payload.c_str());
}


