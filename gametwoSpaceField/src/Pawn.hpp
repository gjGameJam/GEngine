#ifndef PAWN_HPP
#define PAWN_HPP

#include "PhysicsObject.hpp"

/**
the class for all enemies and players
*/
class Pawn : public PhysicsObject
{
    int layer = 0;
    //body
    void setLayer(int layer);

    int getLayer();
};

#endif