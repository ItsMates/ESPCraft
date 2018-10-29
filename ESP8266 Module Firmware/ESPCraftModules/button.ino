#ifdef BUTTON_PIN

boolean _button_state = LOW;

void button_setup() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	mqtt_subscribe(MQTT_BUTTON_TOPIC);
}

bool button_get() {
	return _button_state;
}

bool button_read() {
	return digitalRead(BUTTON_PIN);
}

void button_loop() {
	static boolean previous = LOW;
	boolean state = button_read();

	if (state != previous) {
		previous = state;
		button_setState(state);
	}
}

void button_setState(bool state)
{
	static boolean lastState = LOW;

	_button_state = state;

	if (_button_state != lastState) {
		lastState = _button_state;
		if (_button_state == HIGH) {
			log_debugln("Fireing BUTTON TRUE Event!");
			module_fireEvent(Events::EV_ACTION_BUTTON, HIGH, NO_MESSAGE);
		}
		else {
			log_debugln("Fireing BUTTON FALSE Event!");
			module_fireEvent(Events::EV_ACTION_BUTTON, LOW, NO_MESSAGE);
		}
	}
}

#else

void button_setup() {}
bool button_get() { return false; }
bool button_read() { return false; }
void button_loop() {}
void button_setState(bool state) {}

#endif // BUTTON_PIN
