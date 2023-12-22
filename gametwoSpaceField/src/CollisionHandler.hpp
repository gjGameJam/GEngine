#pragma once
#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Event.hpp"
#include "EventHandler.hpp"

class CollisionHandler : public EventHandler {
	public:
		void onEvent(Event e);
        CollisionHandler();
};

#endif