#ifdef RELAY_PIN

void relay_setup()
{
	pinMode(RELAY_PIN, OUTPUT);
	mqtt_subscribe(MQTT_RELAY_TOPIC);
	
	module_addEventListener(Events::EV_CHANGE_RELAY, [](int code, long param, char* message)->
		void {
		digitalWrite(RELAY_PIN, (bool)param);
	});
}

void relay_setState(bool state)
{
	module_fireEvent(Events::EV_CHANGE_RELAY, state, NO_MESSAGE);
}

bool relay_get()
{
	return digitalRead(RELAY_PIN);
}

#else

void relay_setup() {}
void relay_setState(bool state) {}
bool relay_get() { return false; }

#endif // RELAY_PIN