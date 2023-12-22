#include "GameObject.hpp"

/**
all encompassing gameobject, unsure if should inhereit from something
*/
sf::String GameObject::getName(){
    return this->name;
}

void GameObject::setName(sf::String name){
    this->name = name;
}