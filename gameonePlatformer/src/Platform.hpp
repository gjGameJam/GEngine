#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include <SFML/System.hpp>
#include "PhysicsObject.hpp"
/**
platform object for standing on and moving
*/
class Platform : public PhysicsObject , public sf::RectangleShape
{
    public:

    bool collider = false;
    bool movingRight = true;
    
    Platform(bool collidable, float sizex, float sizey, int x, int y, sf::Color color);

    /**
    * makes platform oscilate between two positions at a desired speed
    */
    void Oscilate(int posx1, int posx2, float speed);

};

#endif
