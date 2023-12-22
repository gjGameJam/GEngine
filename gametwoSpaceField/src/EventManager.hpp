#pragma once
#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Timeline.hpp"
#include "Deathzone.hpp"
#include "Spawnpoint.hpp"
#include "EventHandler.hpp"
#include <list>
#include <queue>

struct comparePriority{
    bool operator()(Event const & e1, Event const & e2) {
        // return "true" if "e1" is ordered before "e2" in time number
        return e1.time < e2.time;
    }
};

class EventManager
{
    public:
        //all event stuff
        static EventManager* getInstance();
        EventManager();
        bool checkForDeathEvent(Character* client, Deathzone* dzone);
        //bool Test(Deathzone* dzone);
        //void registerHandler(std::forward_list<std::string>, EventHandler *);
        void registerHandler(std::string, EventHandler *);
		void deregisterHandler(std::list<std::string>, EventHandler *);
		void raise(Event);
        void update();
        
	private:
		
		std::vector<Event> raised_events;
        // static pointer which will points
        //to the instance of this class
        static EventManager* instancePtr;

};

#endif