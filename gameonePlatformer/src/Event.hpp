#pragma once
#ifndef EVENT_HPP
#define EVENT_HPP

#include "GameObject.hpp"
#include "Character.hpp"
#include "Spawnpoint.hpp"
#include "Timeline.hpp"

typedef struct variant {
	enum Type {
		TYPE_INT,
		TYPE_INPUT,
		TYPE_COLLIDEE,
        TYPE_COLLIDER,
        TYPE_POS,
        TYPE_SPAWNPOINT
        //maybe a delay?
		//add more?
    }m_Type;
	//}Type m_Type;
	union VarianceUnion {
		int m_asInt;
		//float m_asFloat;
        sf::Vector2f eventposition;
		GameObject *m_asGameObject;
        Spawnpoint *spawnPoint;
        int *inputArray;
        Spawnpoint *spoint;
        
	} Vunion;
} variant;


class Event {
    public:
        //each event needs a priority
        int priority;
        //Parameters for the event based off of type
 		std::map<std::string, struct variant> parameters;
        //each event has trigger time
        int64_t time;
        int deltaTime;
        Character *triggerPlayer;
        Timeline *tline;
        //event type (based on ints below)
        int type;
        bool death = false;
		const static int EVENT_TYPE_COLLISION = 1;
        const static int EVENT_TYPE_DEATH = 2;
		const static int EVENT_TYPE_SPAWN = 3;
        const static int EVENT_TYPE_INPUT = 4;
        Event(std::map<std::string, variant> params, int delay);
        //void addVariants(std::map<std::string, struct variant> parameters);
        //void addVariantToParameters(std::string id, variant v);
        //void addVariant(Event e, variant v);
        //void addVariant(Event e, Type t, VarianceUnion u);
        //void addVariant(Event e, variant v);
        

};




#endif