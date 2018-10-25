

void nearir_setup()
{
	pinMode(NEARIR_PIN, INPUT);
}


bool getNearir()
{
	return digitalRead(NEARIR_PIN);
}

