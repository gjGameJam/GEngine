#include "Platform.hpp"
#include <SFML/System.hpp>
/**
platform object for standing on and moving
*/

    
    Platform::Platform(bool collidable, float sizex, float sizey, int x, int y, sf::Color color) : sf::RectangleShape(sf::Vector2f((sizex + 0.f), (sizey + 0.f))) { 
        setPosition((x + 0.f), (y + 0.f)); // you can do this because the class extends RectangleShape, so Platform has setPosition and setFillColor
        setFillColor(color);

        //adds a collider if the bool collidable is true
        if (collidable)
        {
            this->collider = true;
        }
    } 

    /**
    * makes platform oscilate between two positions at a desired speed
    */
    void Platform::Oscilate(int posx1, int posx2, float speed){
        //if too far left go right
        sf::Vector2f vec = getPosition();

        //moving right to start with
        if (movingRight)
        {
            vec = getPosition();
            if (vec.x >= posx2)
            {
                movingRight = false;
            }
            //printf("right: %f   %d\n", vec.x, posx1);
            move((speed + 0.f), (0.f));
        }
        // //if too far right go left
        else if (!movingRight)
        {
            vec = getPosition();
            if (vec.x <= posx1)
            {
                movingRight = true;
            }
            //printf("left: %f   %d\n", vec.x, posx1);
            move(-(speed + 0.f), (0.f));
        }

    }