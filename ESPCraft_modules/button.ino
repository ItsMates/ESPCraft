
#ifdef BUTTON_PIN

#include <Bounce2.h>

// Instantiate a Bounce object :
Bounce button = Bounce();

void button_setup() {
	button.attach(BUTTON_PIN);   // Use the bounce2 library to debounce the built in button
	button.interval(50);         // Input must be low for 50 ms
}

bool button_update() {
	button.update();
	// Call code if Bounce fell (transition from HIGH to LOW) :
	if (button.fell()) {
		//mqttClient.publish(outTopic, "0");
	}
}

bool getButton() {
	return button.status()???? ajdono
}

#else

void button_setup() { return; }
bool getButton() { return false; }
bool button_update() { return false; }

#endif // BUTTON_PIN