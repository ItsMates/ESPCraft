

void touch_setup()
{
	pinMode(TOUCH_PIN, INPUT_PULLUP);
}


bool getTouch()
{
	return digitalRead(TOUCH_PIN);
}
