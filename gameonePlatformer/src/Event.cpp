#include "Event.hpp"

Timeline *eventTimeline = new Timeline();

//constructs a new event currently with a map of variants
Event::Event(std::map<std::string, variant> params, int delay){
    //set the time to be currenttime + desired delay
    time = eventTimeline->getTime() + delay;
    //loops through all content of param map, adding them to the event
    for (auto const& idVariantPair : params){
        if (idVariantPair.first == "input"){
            type = EVENT_TYPE_INPUT;
        }
        else if (idVariantPair.first == "death"){
            type = EVENT_TYPE_DEATH;
        }
        else if (idVariantPair.first == "spawn"){
            type = EVENT_TYPE_SPAWN;
        }
        else if (idVariantPair.first == "collision"){
            type = EVENT_TYPE_COLLISION;
        }
        parameters.insert(std::pair<std::string, variant>(idVariantPair.first, idVariantPair.second));
    }
}

