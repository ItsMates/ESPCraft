
#include "Events.h"
#include "EventQueue.h"
#include "EventDispatcher.h"

#include "private.h"

//#define DEBUG_ENABLE
//#define LOG_ENABLE

/*Board services*/
#define WIFI_ENABLE
//#define OTA_ENABLE
#define MQTT_ENABLE

/*Touch board*/
//#define TOUCH_PIN D8
//#define NEOPIXEL_PIN D2
//#define RELAY_PIN D1
//#define NEARIR_PIN D7

/*PIR board*/
//#define PIR_PIN D6
//#define DISPLAY_ADRESS 0x3C
//#define BUTTON_PIN D7

/*Service settings*/
#define SERIAL_BAUD 115200
#define MQTT_PAYLOAD_MAX 64


#define MQTT_ROOT_TOPIC "nvias/MC/" MC_NAME "/" BOARD_NAME

#define MQTT_TOUCH_TOPIC MQTT_ROOT_TOPIC "/TOU"
#define MQTT_BUTTON_TOPIC MQTT_ROOT_TOPIC "/BUT"
#define MQTT_NEARIR_TOPIC MQTT_ROOT_TOPIC "/NEA"
#define MQTT_PIR_TOPIC MQTT_ROOT_TOPIC "/PIR"
#define MQTT_MIC_TOPIC MQTT_ROOT_TOPIC "/MIC"
#define MQTT_RELAY_TOPIC MQTT_ROOT_TOPIC "/REL"
#define MQTT_DISPLAY_TOPIC MQTT_ROOT_TOPIC "/DIS"
#define MQTT_NEOPIXEL_TOPIC MQTT_ROOT_TOPIC "/NEO"
#define MQTT_NEOPIXEL_R_TOPIC MQTT_NEOPIXEL_TOPIC "/R"
#define MQTT_NEOPIXEL_G_TOPIC MQTT_NEOPIXEL_TOPIC "/G"
#define MQTT_NEOPIXEL_B_TOPIC MQTT_NEOPIXEL_TOPIC "/B"




#define NO_MESSAGE ""

//==============================================================

#ifdef DEBUG_ENABLE

#define log_debugln(x); Serial.println(x);
#define log_debug(x); Serial.print(x);
#define log_debugf(a,b); Serial.printf(a,b);

#else

#define log_debugln(x); 
#define log_debug(x); 
#define log_debugf(a,b);  

#endif

#ifdef LOG_ENABLE

#define log_logln(x); Serial.println(x);
#define log_log(x); Serial.print(x);
#define log_logf(a,b); Serial.printf(a,b);

#else

#define log_logln(x);
#define log_log(x);
#define log_logf(a,b);  

#endif