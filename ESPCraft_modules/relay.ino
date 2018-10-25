

void relay_setup()
{
	pinMode(RELAY_PIN, OUTPUT);
}


void setRelay(bool state)
{
	digitalWrite(RELAY_PIN, state);
}

bool getRelay()
{
	return digitalRead(RELAY_PIN);
}
