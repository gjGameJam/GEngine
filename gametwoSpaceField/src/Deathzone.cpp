#include "Deathzone.hpp"

Deathzone::Deathzone(float sizex, float sizey, int xPos, int yPos) : sf::RectangleShape(sf::Vector2f((sizex + 0.f), (sizey + 0.f))) { 
    setPosition((xPos + 0.f), (yPos + 0.f));
}