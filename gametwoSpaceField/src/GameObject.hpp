#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
    public: 

    int xPosition;
    int yPosition;
    sf::String name = "blank";

    sf::String getName();

    void setName(sf::String name);

    
};


#endif