#pragma once
#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "Event.hpp"

class EventHandler {
	public:
		virtual void onEvent(Event e) = 0;
};

#endif