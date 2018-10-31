#ifdef MQTT_ENABLE

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "definitions.h"
#include "QList.h"

const char* MQTT_SERVER_IP = MY_MQTT_HOST;
const int MQTT_SERVER_PORT = MY_MQTT_HOST_PORT;

const char* MQTT_USER = MY_MQTT_USERNAME;
const char* MQTT_PASSWORD = MY_MQTT_PASSWORD;
const char* MQTT_CLIENT_NAME = BOARD_NAME;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

QList<String> _subscriptions;

void mqtt_subscribe(char* topic) {
	_subscriptions.push_back(String(topic));
}

void mqtt_subscribe(String topic) {
	_subscriptions.push_back(topic);
}

void _mqtt_runSubscribe() {
	int lenght = _subscriptions.length();
	for (int i = 0; i < lenght; i++) {
		mqttClient.subscribe(_subscriptions.at(i).c_str());		
	}
}

void mqtt_setup() {
	log_logln("Setting up MQTT");

	mqtt_reconnect();
	_mgtt_connectModule();

	log_logln("MQTT setup done");
}

byte _mqtt_buttonLast = false;
byte _mqtt_nearirLast = false;
byte _mqtt_pirLast = false;
byte _mqtt_touchLast = false;
byte _mqtt_micLast = false;

long _mqtt_neopixelLast = 0;
byte _mqtt_neopixelRLast = 0;
byte _mqtt_neopixelGLast = 0;
byte _mqtt_neopixelBLast = 0;

String _mqtt_displayLast = "";
byte _mqtt_relayLast = false;

const int pause = 2;

void _mgtt_connectModule() {

	mqttClient.publish(MQTT_ROOT_TOPIC, "ONLINE");
	
	auto button = [](int code, long param, String message)->void {
		if (param != _mqtt_buttonLast) {
			_mqtt_buttonLast = param;
			mqttClient.publish(MQTT_BUTTON_TOPIC, param == HIGH ? "1" : "0");
		}
	};
	auto nearir = [](int code, long param, String message)->void {
		if (param != _mqtt_nearirLast) {
			_mqtt_nearirLast = param;
			mqttClient.publish(MQTT_NEARIR_TOPIC, param == HIGH ? "1" : "0");
		}
	};
	auto pir = [](int code, long param, String message)->void {
		if (param != _mqtt_pirLast) {
			_mqtt_pirLast = param;
			mqttClient.publish(MQTT_PIR_TOPIC, param == HIGH ? "1" : "0");
		}
	};
	auto touch = [](int code, long param, String message)->void {
		if (param != _mqtt_touchLast) {
			_mqtt_touchLast = param;
			mqttClient.publish(MQTT_TOUCH_TOPIC, param == HIGH ? "1" : "0");
		}
	};
	auto mic = [](int code, long param, String message)->void {
		if(param != _mqtt_micLast){
		_mqtt_micLast = param;
		mqttClient.publish(MQTT_MIC_TOPIC, param == HIGH ? "1" : "0");
		}
	};

	module_addEventListener(Events::EV_ACTION_BUTTON, button);
	module_addEventListener(Events::EV_ACTION_NEARIR, nearir);
	module_addEventListener(Events::EV_ACTION_PIR, pir);
	module_addEventListener(Events::EV_ACTION_TOUCH, touch);
	module_addEventListener(Events::EV_ACTION_MIC, mic);

	auto neopixel = [](int code, long param, String message)->void {
		
		log_debugln(param);
		if (param != _mqtt_neopixelLast) {
			_mqtt_neopixelLast = param;
			mqttClient.publish(MQTT_NEOPIXEL_TOPIC, String(param).c_str());
		}	
		log_debugln(neopixel_r(param));
		if (neopixel_r(param) != _mqtt_neopixelRLast) {
			_mqtt_neopixelRLast = neopixel_r(param);
			mqttClient.publish(MQTT_NEOPIXEL_R_TOPIC, String(neopixel_r(param)).c_str());
		}
		log_debugln(neopixel_g(param));
		if (neopixel_g(param) != _mqtt_neopixelGLast) {
			_mqtt_neopixelGLast = neopixel_g(param);
			mqttClient.publish(MQTT_NEOPIXEL_G_TOPIC, String(neopixel_g(param)).c_str());
		}
		log_debugln(neopixel_b(param));
		if (neopixel_b(param) != _mqtt_neopixelBLast) {
			_mqtt_neopixelBLast = neopixel_b(param);
			mqttClient.publish(MQTT_NEOPIXEL_B_TOPIC, String(neopixel_b(param)).c_str());
		}
	};
	auto display = [](int code, long param, String message)->void {
		if (message != _mqtt_displayLast) {
			_mqtt_displayLast = message;
			mqttClient.publish(MQTT_DISPLAY_TOPIC, message.c_str());
		}
	};
	auto relay = [](int code, long param, String message)->void {
		if (param != _mqtt_relayLast) {
			_mqtt_relayLast = param;
			mqttClient.publish(MQTT_RELAY_TOPIC, param == HIGH ? "1" : "0");
		}
	};

	module_addEventListener(Events::EV_CHANGE_NEOPIXEL, neopixel);
	module_addEventListener(Events::EV_CHANGE_DISPLAY, display);
	module_addEventListener(Events::EV_CHANGE_RELAY, relay);
}

void _mqtt_callback(char* top, byte* payload, unsigned int length) {

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

	module_fireEvent(Events::EV_ACTION_MQTT, length, top);

	if (topic == MQTT_BUTTON_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_buttonLast) {
			_mqtt_buttonLast = state;
			button_setState(state);		
		}
	}

	else if (topic == MQTT_NEARIR_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_nearirLast) {
			_mqtt_nearirLast = state;
			nearir_setState(state);
		}
	}

	else if (topic == MQTT_PIR_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_pirLast) {
			_mqtt_pirLast = state;
			pir_setState(state);		
		}
	}

	else if (topic == MQTT_TOUCH_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_touchLast) {
			_mqtt_touchLast = state;
			touch_setState(state);			
		}
	}

	else if (topic == MQTT_MIC_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_micLast) {
			_mqtt_micLast = state;
			mic_setState(state);			
		}
	}





	else if (topic == MQTT_NEOPIXEL_TOPIC) {
		long colour = message.toInt();
		if (colour != _mqtt_neopixelLast) {
			_mqtt_neopixelLast = colour;
			neopixel_setState(colour);
		}
	}

	else if (topic == MQTT_NEOPIXEL_R_TOPIC) {
		int r = (byte)message.toInt();
		long colour = neopixel_color(r, neopixel_g(_mqtt_neopixelLast), neopixel_b(_mqtt_neopixelLast));
		if (r != _mqtt_neopixelRLast) {
			_mqtt_neopixelRLast = r;
			neopixel_setState(colour);
		}
		
	}

	else if (topic == MQTT_NEOPIXEL_G_TOPIC) {
		int g = (byte)message.toInt();
		long colour = neopixel_color(neopixel_r(_mqtt_neopixelLast), g, neopixel_b(_mqtt_neopixelLast));
		if (g != _mqtt_neopixelGLast) {
			_mqtt_neopixelGLast = g;
			neopixel_setState(colour);	
		}
	}

	else if (topic == MQTT_NEOPIXEL_B_TOPIC) {
		int b = (byte)message.toInt();
		long colour = neopixel_color(neopixel_r(_mqtt_neopixelLast), neopixel_g(_mqtt_neopixelLast), b);
		if (b != _mqtt_neopixelBLast) {		
			_mqtt_neopixelBLast = b;
			neopixel_setState(colour);
		}
	}

	else if (topic == MQTT_DISPLAY_TOPIC) {

		if (message != _mqtt_displayLast) {
			_mqtt_displayLast = message;
			display_setState(message);		
		}
	}

	else if (topic == MQTT_RELAY_TOPIC) {
		boolean state = msg[0] == '0' ? LOW : HIGH;
		if (state != _mqtt_relayLast) {			
			_mqtt_relayLast = state;
			relay_setState(state);
		}
		
	}


#ifdef LOG_ENABLE
	log_log("MQTT: [");
	log_log(top);
	log_log("] - ");
	for (int i = 0; i < (int)length; i++) {
		log_log((char)payload[i]);
	}
	if (length > MQTT_PAYLOAD_MAX) {
		log_log("!!! payload too big");
	}
	log_logln();
#endif
}

void mqtt_reconnect() {
	mqttClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
	mqttClient.setCallback(_mqtt_callback);
	while (!mqttClient.connected()) {
		log_logln("Connecting to MQTT...");
		if (mqttClient.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
			log_logln("connected");
		}
		else {
			log_log("failed with state ");
			log_logln(mqttClient.state());
			delay(250);
		}	
	}
	_mqtt_runSubscribe();
}

bool mqtt_loop() {
	while (!mqttClient.connected()) {
		mqtt_reconnect();
		return false;
	}

	mqttClient.loop();
	return true;
}

void mqtt_publish(String topic, String payload) {
	mqttClient.publish(topic.c_str(), payload.c_str());
}

void mqtt_publish(char* topic, char* payload) {
	mqttClient.publish(topic, payload);
}

#else

void mqtt_setup(){}
//void mqtt_addListener(EventListener handler){}
void mqtt_reconnect(){}
bool mqtt_loop(){}
void mqtt_publish(String topic, String payload){}
void mqtt_publish(char* topic, char* payload){}
void mqtt_subscribe(char* topic){}

#endif // MQTT_ENABLE