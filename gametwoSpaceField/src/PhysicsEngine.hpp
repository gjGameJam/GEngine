#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include "GameObject.hpp"
#include "PhysicsObject.hpp"
#include "Platform.hpp"
#include "Character.hpp"
#include "EventManager.hpp"

class PhysicsEngine : public GameObject {
    public: 

    //storage of all physics objects
    std::vector<PhysicsObject> physicalItems;

    static PhysicsEngine* getInstance();
    
    //consider changing params to just bounding boxes?
    bool collisionCheck(Platform platform1, Character character1, EventManager *eManager);

    int gravityFuntion(int64_t grassTouchTime, int64_t last_time);


    private:
    
    PhysicsEngine();
    // static pointer which will points
    //to the instance of this class
    static PhysicsEngine* instancePtr;
};


#endif