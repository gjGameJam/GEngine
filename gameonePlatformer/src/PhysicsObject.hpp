#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP
#include "GameObject.hpp"

/**
objects that are meant to be interacted with physically
*/
class PhysicsObject : public GameObject
{
    //body
    int xVelocity;
    int yVelocity;
    //int zVelocity;

        public:
        void moveRelative(int x,int y);
};

#endif