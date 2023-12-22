#pragma once
#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "Event.hpp"
#include "EventHandler.hpp"

class InputHandler : public EventHandler {
	public:
		void onEvent(Event e);
        InputHandler();
        //InputHandler* instancePtr;
};

#endif