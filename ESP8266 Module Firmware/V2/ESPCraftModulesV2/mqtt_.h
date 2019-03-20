#ifndef MODULEMQTT_H
#define MODULEMQTT_H

#include "wifi_.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* MQTT_SERVER_IP = MY_MQTT_HOST;
const int MQTT_SERVER_PORT = MY_MQTT_HOST_PORT;

const char* MQTT_USER = MY_MQTT_USERNAME;
const char* MQTT_PASSWORD = MY_MQTT_PASSWORD;
const char* MQTT_CLIENT_NAME = BOARD_NAME;

typedef void(*MqttOnMessageCallback)(String topic, String message);

class ModuleMqtt : public ModuleWifi {

private:
	
	WiFiClient _wifiClient;
	PubSubClient _mqttClient;
	QList<String> _subscriptions;

	MqttOnMessageCallback _onMessageHandler;

	void _runSubscribe() {
		int lenght = _subscriptions.length();
		for (int i = 0; i < lenght; i++) {
			_mqttClient.subscribe(_subscriptions.at(i).c_str());
		}
	}

	//MQTT IN MODULE
	void _callback(char* top, uint8_t* payload, unsigned int length) {

		char msg[MQTT_PAYLOAD_MAX];
		String topic = String(top);

		//message
		for (int i = 0; i < MQTT_PAYLOAD_MAX; i++) {
			char c = '\0';
			if (i < (int)length) c = (char)payload[i];
			msg[i] = c;
		}

		String message = String(msg);
		message.remove(length);

		log_log(F("MQTT: ["));
		log_log(top);
		log_log(F("] - "));
		for (int i = 0; i < (int)length; i++) {
			log_log((char)payload[i]);
		}
		if (length > MQTT_PAYLOAD_MAX) {
			log_log(F("!!! payload too big"));
		}

		control->fireEvent(Events::EV_MQTT_RECEIVED, length, message);

		(*_onMessageHandler)(topic, message);
	}

public:

	ModuleMqtt(Control*c) : ModuleWifi(c) {
		_onMessageHandler = [](String topic, String message) -> void {};
	}

	void setOnMessageHandler(MqttOnMessageCallback handler) {
		_onMessageHandler = handler;
	}

	
	void begin() {
		log_logln(F("Setting up MQTT"));

		if (connect(true, true)) {
			log_logln(F("Setup MQTT: MQTT connected"));
		}
		else {
			log_logln(F("Setup MQTT: MQTT connection error"));
		}

		log_logln("MQTT setup end");
	}

	void subscribe(String topic) {

		_subscriptions.push_back(topic);
		//mqttClient.subscribe(topic.c_str());
	}

	//void subscribe(char* topic) {
	//	_subscriptions.push_back(String(topic));
	//	//mqttClient.subscribe(topic);
	//}

	void publish(String topic, String payload) {
		_mqttClient.publish(topic.c_str(), payload.c_str());
	}

	/*void publish(char* topic, char* payload) {
		_mqttClient.publish(topic, payload);
	}*/

	bool loop() {
		if (!_mqttClient.connected()) {
			connect(true);
			return false;
		}
		else {
			_mqttClient.loop();
			return true;
		}
	}

	//WTFFFFFFFFFFFFFFF
	std::function<void(char*, uint8_t*, unsigned int)> callback = [=](char* topic, uint8_t* payload, unsigned int length) {
		this->_callback(topic, payload, length);
	};


	bool connect(bool subscribe, bool forceConnect = false) {
		static unsigned long lastConnectionTry_millis = 0;
		static int count = 0;

		if (forceConnect || (millis() - lastConnectionTry_millis > 10000)) {

			lastConnectionTry_millis = millis();

			_mqttClient.setClient(_wifiClient);
			_mqttClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
			_mqttClient.setCallback(callback);

			if (!_mqttClient.connected()) {
				log_logln(F("Connecting to MQTT..."));
				if (_mqttClient.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
					log_logln(F("   connected"));
					control->fireEvent(Events::EV_MQTT_RECONNECTED, true, "MQTT_CONNECTED");
					if (subscribe) {
						_runSubscribe();
					}
					return true;
				}
				else {
					count++;
					log_log(F("   failed with state "));
					log_logln(_mqttClient.state());
					control->fireEvent(Events::EV_MODULE_ERROR, AQUA_ERROR_CODE, "MQTT_CONNECTION_ERROR");

					//After a minute -> restart
					if (count >= 6) {
						control->fireEvent(Events::EV_MODULE_RESTART, 0, "MQTT_CONNECTION_ERROR_RESTART");
					}			
					return false;
				}
			
			}
			else {
				count = 0;
				return true;
			}
		}

		return true;
	}
};

#endif // MQTT_ENABLE