#pragma once
#ifndef SPAWNPOINT_HPP
#define SPAWNPOINT_HPP

#include "Character.hpp"

class Spawnpoint
{
    public:

        Spawnpoint(int Xposition, int Yposition);

        void respawnClient(Character* client);

        int xpos;

        int ypos;

        //int spawnPointIndex;

};

#endif