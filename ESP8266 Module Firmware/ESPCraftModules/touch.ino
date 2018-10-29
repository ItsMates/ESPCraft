#ifdef TOUCH_PIN

boolean _touch_state = LOW;

void touch_setup(){
	pinMode(TOUCH_PIN, INPUT);
	mqtt_subscribe(MQTT_TOUCH_TOPIC);
}

bool touch_get(){
	return _touch_state;
}

bool touch_read() {
	return digitalRead(TOUCH_PIN);
}

void touch_loop() {
	static bool previous = LOW;
	boolean state = touch_read();

	if (state != previous) {
		previous = state;
		touch_setState(state);
	}
}

void touch_setState(bool state)
{
	static bool previous = LOW;

	if (state != previous) {
		previous = state;

		if (state == HIGH) {
			log_debugln("Fireing TOUCH TRUE Event!");
			module_fireEvent(Events::EV_ACTION_TOUCH, HIGH, NO_MESSAGE);
		}
		else {
			log_debugln("Fireing TOUCH FALSE Event!");
			module_fireEvent(Events::EV_ACTION_TOUCH, LOW, NO_MESSAGE);
		}
	}

	_touch_state = state;
}

#else

void touch_setup() {}
bool touch_get() { return false; }
bool touch_read() { return false; }
void touch_loop() {}
void touch_setState(bool state) {}

#endif // TOUCH_PIN
