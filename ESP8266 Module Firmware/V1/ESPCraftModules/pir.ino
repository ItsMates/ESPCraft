#ifdef PIR_PIN

boolean _pir_state = LOW;

void pir_setup() {
	pinMode(PIR_PIN, INPUT);
	mqtt_subscribe(MQTT_PIR_TOPIC);
}

bool pir_get() {
	return _pir_state;
}

bool pir_read() {
	return digitalRead(PIR_PIN);
}

void pir_loop() {
	static boolean previous = LOW;
	boolean state = pir_read();

	if (state != previous) {
		previous = state;
		pir_setState(state);
	}
}

void pir_setState(bool state)
{
	static boolean lastState = LOW;

	_pir_state = state;

	if (_pir_state != lastState) {
		lastState = _pir_state;
		if (_pir_state == HIGH) {
			log_debugln("Fireing PIR TRUE Event!");
			module_fireEvent(Events::EV_ACTION_PIR, HIGH, NO_MESSAGE);
		}
		else {
			log_debugln("Fireing PIR FALSE Event!");
			module_fireEvent(Events::EV_ACTION_PIR, LOW, NO_MESSAGE);
		}
	}
}

#else

void pir_setup() {}
bool pir_get() { return false; }
bool pir_read() { return false; }
void pir_loop() {}
void pir_setState(bool state) {}

#endif // PIR_PIN
