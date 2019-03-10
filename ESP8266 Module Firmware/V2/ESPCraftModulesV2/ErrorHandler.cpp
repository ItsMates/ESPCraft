// 
// 
// 

#include "ErrorHandler.h"

ErrorCallback ErrorHandler::_errorHandler = [](long param, String message) -> void {};

ErrorHandler::ErrorHandler() {

}

void ErrorHandler::setErrorHandler(ErrorCallback handler) {
	_errorHandler = handler;
}

void ErrorHandler::handleError(int code, long param, String message)
{
	Serial.print(F("### ERROR "));
	Serial.print(message);
	Serial.println(F(" ###"));

	(*_errorHandler)(param, message);
}