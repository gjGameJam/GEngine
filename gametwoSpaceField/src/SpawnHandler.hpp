#pragma once
#ifndef SPAWNHANDLER_HPP
#define SPAWNHANDLER_HPP

#include "Event.hpp"
#include "EventHandler.hpp"

class SpawnHandler : public EventHandler {
	public:
		void onEvent(Event e);
        SpawnHandler();
};

#endif