/*
* EventQueue.h
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

#ifndef EventQueue_h
#define EventQueue_h

#include <arduino.h>
#include "Events.h"

class EventQueue {

public:
   // Event queue size.
   // The maximum number of events
   // the queue can hold is EVQUEUE_SIZE - 1.
   // Increasing this number will consume 2 * sizeof(int)
   // bytes of RAM for each unit.
   static const int EVQUEUE_SIZE = 30;

   // Queue constructor
   EventQueue();

   // returns true if no events are in the queue
   boolean isEmpty();

   // returns true if no more events can be inserted into the queue
   boolean isFull();

   // actual number of events in queue
   int getNumEvents();

   // tries to insert an event into the queue;
   // returns true if successful, false if the
   // queue if full and the event cannot be inserted
   boolean enqueueEvent(int ev_code, long ev_param, String ev_message);

   // tries to extract an event from the queue;
   // returns true if successful, false if the
   // queue is empty (the parameteres are not touched
   // in this case)
   boolean dequeueEvent(int* ev_code, long* ev_param, String* ev_message);

private:
   // each event is represented by an integer code
   int eventQueue[EVQUEUE_SIZE];

   // each event has a single integer parameter
   long eventParam[EVQUEUE_SIZE];

   // each event has a string message
   String eventMessage[EVQUEUE_SIZE];

   // index of event queue head
   int eventQueueHead;

   // index of event queue tail
   int eventQueueTail;

   // actual number of events in queue
   int numEvents;

   // initialize event queue - to be called only by constructor
   void init();
};

#endif