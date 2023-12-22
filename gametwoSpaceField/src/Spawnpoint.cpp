#include "Spawnpoint.hpp"

int xpos;

int ypos;

//create a spawnpoint with the desired location
Spawnpoint::Spawnpoint(int Xposition, int Yposition){
    //create spawnpoint at location
    this->xpos = Xposition;
    this->ypos = Yposition;
    //this->spawnPointIndex = spawnPointInd;

}

//move a client to indicate respawn 
void Spawnpoint::respawnClient(Character* client){ //(takes pointer to actually effect player instead of taking copy)
    //printf("UHHHHHH\n");
    client->setPosition(xpos, ypos);
    
}