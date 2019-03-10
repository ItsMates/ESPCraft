#ifdef MIC_PIN

boolean _mic_state = LOW;

void mic_setup() {
	pinMode(MIC_PIN, INPUT);
	mqtt_subscribe(MQTT_MIC_TOPIC);
}

bool mic_get() {
	return _mic_state;
}

bool mic_read() {
	return digitalRead(MIC_PIN);
}

void mic_loop() {
	static boolean previous = LOW;
	boolean state = mic_read();

	if (state != previous) {
		previous = state;
		mic_setState(state);
	}
}

void mic_setState(bool state)
{
	static boolean lastState = LOW;

	_mic_state = state;

	if (_mic_state != lastState) {
		lastState = _mic_state;
		if (_mic_state == HIGH) {
			log_debugln("Fireing MIC TRUE Event!");
			module_fireEvent(Events::EV_ACTION_MIC, HIGH, NO_MESSAGE);
		}
		else {
			log_debugln("Fireing MIC FALSE Event!");
			module_fireEvent(Events::EV_ACTION_MIC, LOW, NO_MESSAGE);
		}
	}
}

#else

void mic_setup() {}
bool mic_get() { return false; }
bool mic_read() { return false; }
void mic_loop() {}
void mic_setState(bool state) {}

#endif // MIC_PIN
