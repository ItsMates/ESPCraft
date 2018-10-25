
/*
* Events.h
*
* Part of Arduino Event System.
*
* Author: mromani@ottotecnica.com
* Copyright (c) 2010 OTTOTECNICA Italy
*
* This library is free software; you can redistribute it
* and/or modify it under the terms of the GNU Lesser
* General Public License as published by the Free Software
* Foundation; either version 2.1 of the License, or (at
* your option) any later version.
*
* This library is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*
* You should have received a copy of the GNU Lesser
* General Public License along with this library; if not,
* write to the Free Software Foundation, Inc.,
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*
*/

#ifndef Events_h
#define Events_h

#include <arduino.h>

// Some common events.
// Codes 0..199 are available for
// user defined events.

#define MESSAGE_SIZE 32

class Events {

public:
   enum eventType {

	   // no event occurred
	   // param: none
	   EV_NONE = 0,

	   EV_MQTT
   };
};

#endif