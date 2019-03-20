#include "private.h"
#include "Events.h"

#define DEBUG_ENABLE
#define LOG_ENABLE

//WEMOS D1 Mini
#define PIN_D0 16
#define PIN_D1 5
#define PIN_D2 4
#define PIN_D3 0
#define PIN_D4 2
#define PIN_D5 14
#define PIN_D6 12
#define PIN_D7 13
#define PIN_D8 15

/*Board services*/
#define WIFI_ENABLE
#define OTA_ENABLE
#define MQTT_ENABLE

//PINS
#define NEOPIXEL_PIN PIN_D3
#define BUTTON_PIN PIN_D2

//NEOPIXEL LEDS
#define PIXELS_PIN PIN_D4
#define NUM_LEDS 8
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


/*Service settings*/
#define SERIAL_BAUD 115200
#define MQTT_PAYLOAD_MAX 64

#define ALARM_BLINK_DELAY 150
#define AUTO_IDLE_LOGOUT_TIME_MS 600000UL
#define AFTER_LOGOUT_ACESS_MS 60000UL

#define NO_MESSAGE ""

//MQTT CONNECTION
#define AQUA_ERROR_CODE 0x00FFFF
////POST ERROR
#define VIOLET_ERROR_CODE 0xFF00FF
//WIFI NOT CONNECTED
#define YELLOW_ERROR_CODE 0xFFFF00


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