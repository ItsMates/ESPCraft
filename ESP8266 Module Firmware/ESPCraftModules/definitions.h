
#include "Events.h"
#include "EventQueue.h"
#include "EventDispatcher.h"

#include "private.h"

#define DEBUG_ENABLE
#define LOG_ENABLE

/*Board services*/
#define WIFI_ENABLE
#define OTA_ENABLE
#define MQTT_ENABLE

/*Touch board*/
//#define TOUCH_PIN D8
//#define NEOPIXEL_PIN D2
//#define RELAY_PIN D1
//#define NEARIR_PIN D7

/*PIR board*/
//#define PIR_PIN 

/*Microphone board*/
//#define MIC_PIN
#define DISPLAY_ADRESS 0x3C
//#define MIC_PIN 
//#define BUTTON_PIN

/*Service settings*/
#define SERIAL_BAUD 115200
#define MQTT_PAYLOAD_MAX 64

#define MQTT_ROOT_TOPIC BOARD_NAME
#define MQTT_TOUCH_TOPIC MQTT_ROOT_TOPIC "/TOUCH"
#define MQTT_BUTTON_TOPIC MQTT_ROOT_TOPIC "/BUTTON"
#define MQTT_NEARIR_TOPIC MQTT_ROOT_TOPIC "/NEARIR"
#define MQTT_PIR_TOPIC MQTT_ROOT_TOPIC "/PIR"
#define MQTT_MIC_TOPIC MQTT_ROOT_TOPIC "/MIC"
#define MQTT_RELAY_TOPIC MQTT_ROOT_TOPIC "/RELAY"
#define MQTT_DISPLAY_TOPIC MQTT_ROOT_TOPIC "/DISPLAY"
#define MQTT_NEOPIXEL_TOPIC MQTT_ROOT_TOPIC "/NEOPIXEL"

#define NO_MESSAGE ""

//==============================================================

#ifdef DEBUG_ENABLE

#define log_debugln(x); Serial.println(x);
#define log_debug(x); Serial.print(x);
#define log_debugf(a,b); Serial.printf(a,b);

#define log_logln(x); Serial.println(x);
#define log_log(x); Serial.print(x);
#define log_logf(a,b); Serial.printf(a,b);

#else

#define log_debugln(x); 
#define log_debug(x); 
#define log_debugf(a,b);  

#define log_logln(x);
#define log_log(x);
#define log_logf(a,b);  

#endif