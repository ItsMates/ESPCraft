#ifdef NEARIR_PIN

boolean _nearir_state = LOW;

void nearir_setup() {
	pinMode(NEARIR_PIN, INPUT);
	mqtt_subscribe(MQTT_NEARIR_TOPIC);
}

bool nearir_get() {
	return _nearir_state;
}

bool nearir_read() {
	return digitalRead(NEARIR_PIN);
}

void nearir_loop() {
	static boolean previous = LOW;
	boolean state = nearir_read();

	if (state != previous) {
		previous = state;
		nearir_setState(state);
	}
}


void nearir_setState(bool state)
{
	static bool lastState = LOW;

	_nearir_state = state;

	if (_nearir_state != lastState) {
		lastState = _nearir_state;
		if (_nearir_state == HIGH) {
			log_debugln("Fireing NEARIR TRUE Event!");
			module_fireEvent(Events::EV_ACTION_NEARIR, HIGH, NO_MESSAGE);
		}
		else {
			log_debugln("Fireing NEARIR FALSE Event!");
			module_fireEvent(Events::EV_ACTION_NEARIR, LOW, NO_MESSAGE);
		}
	}
}

#else

void nearir_setup() {}
bool nearir_get() { return false; }
bool nearir_read() { return false; }
void nearir_loop() {}
void nearir_setState(bool state) {}

#endif // NEARIR_PIN
