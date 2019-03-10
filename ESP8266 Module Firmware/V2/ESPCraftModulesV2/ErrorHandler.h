#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <arduino.h>

typedef void(*ErrorCallback)(long param, String message);

class ErrorHandler
{
private:
	static ErrorCallback _errorHandler;
public:
	ErrorHandler();
	static void handleError(int code, long param, String message);
	static void setErrorHandler(ErrorCallback handler);
};


#endif

