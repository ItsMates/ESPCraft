#ifndef MODULE_H
#define MODULE_H

#include "definitions.h"

#include "QList.h"
#include "EventQueue.h"
#include "EventDispatcher.h"

#include "ErrorHandler.h"


class Control {

private:
	// the event queue
	EventQueue queue;

	// the event dispatcher
	EventDispatcher dispatcher;

public:
	Control() : queue(), dispatcher(&queue) {
		dispatcher.addEventListener(Events::EV_MODULE_ERROR, handleError);
		dispatcher.addEventListener(Events::EV_MODULE_RESTART, handleRestart);
	}

	void addEventListener(int eventCode, EventListener handler) {
		dispatcher.addEventListener(eventCode, handler);
	}

	void fireEvent(int eventCode, int eventParam, String eventMessage) {
		log_debug("Fireing event #");
		log_debugln(eventCode);
		queue.enqueueEvent(eventCode, eventParam, eventMessage);
	}

	void runEvents() {
		dispatcher.run();
	}

private:
	static void handleError(int code, long param, String message) {
		ErrorHandler().handleError(code, param, message);
	}
	static void handleRestart(int code, long param, String message) {
		log_logln("Restarting ESP...")
			ESP.restart();
	}

};


#endif

