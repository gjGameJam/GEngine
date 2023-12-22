#include "PhysicsEngine.hpp"

//the pointer to the singleton PhysicsEngine instance
PhysicsEngine* PhysicsEngine::instancePtr;
/**
physics engine
*/
    PhysicsEngine::PhysicsEngine(){
        //this->physicalItems = ;
    }

    //void //method to check if two objects are touching
    bool PhysicsEngine::collisionCheck(Platform platform1, Character character1, EventManager *eManager)
    {
        
        // get the bounding box of the entity
        sf::FloatRect platBox = platform1.getGlobalBounds();
        sf::FloatRect charBox = character1.getGlobalBounds();

        //contains takes a point
        if (platBox.intersects(charBox))
        {
            // collision!
            //create map of variants to define even
            std::map<std::string, variant> collisionMap;
            //create variant for input
            variant colideVariant = {variant::TYPE_COLLIDER, 1};
            //set the union's data in variant to hold the collider (the player collided with something)
            colideVariant.Vunion.m_asGameObject = &platform1;
            //insert the input variant into the map of variants
            collisionMap.insert(std::pair<std::string, variant>("collision", colideVariant));
            //construct event
            Event collisionEvent = Event(collisionMap, 0); //second param is delay (which we don't want for input events)
            //set the type and trigger player
            collisionEvent.type = collisionEvent.EVENT_TYPE_COLLISION;
            collisionEvent.triggerPlayer = &character1;
            //then raise event
            //printf("raise collision event\n");
            eManager->raise(collisionEvent);
            //EventManager::raise(Event newEvent)
            return true;
        }

        return false;
    }

        /*
    getInstance() is a static method that returns an
    instance when called. It returns the same
    instance if it is called more than once because the desired
    functionality of a singleton is for there only to be one
    */
    PhysicsEngine* PhysicsEngine::getInstance()
    {
    // If there is no instance of class
    // then we can create an instance.
    if (instancePtr == nullptr)
        {
            // We can access private members
            // within the class.
            instancePtr = new PhysicsEngine();
       
        }

        // returning the instance pointer
        return instancePtr;
    }

    int PhysicsEngine::gravityFuntion(int64_t grassTouchTime, int64_t last_time){
        int64_t difference = last_time - grassTouchTime;
        //all these times will be in milliseconds
        if (difference <= 500){
            //printf("GRAVITY IS 0\n");
            return 0;
        }
        else if (difference <= 1250){
            //printf("GRAVITY IS 1\n");
            return 1;
        }
        else if (difference <= 2500){
            //printf("GRAVITY IS 2\n");
            return 2;
        }
        else if (difference <= 3500){
            //printf("GRAVITY IS 3\n");
            return 3;
        }
        //printf("GRAVITY IS 4\n");
        return 4;
        
    }
    