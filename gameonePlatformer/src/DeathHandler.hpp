#pragma once
#ifndef DEATHHANDLER_HPP
#define DEATHHANDLER_HPP

#include "Event.hpp"
#include "EventHandler.hpp"

class DeathHandler : public EventHandler {
	public:
		void onEvent(Event e);
        DeathHandler();
};

#endif