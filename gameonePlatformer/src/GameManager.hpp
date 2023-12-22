#pragma once
#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
#include <vector>
#include <mutex>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "PhysicsEngine.hpp"
#include "Timeline.hpp"
#include "Spawnpoint.hpp"
#include "EventManager.hpp"
#include "viewBoundBox.hpp"


/**
game manager for spawning and rendering objects
*/
class GameManager
{
    

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

    public:
    
    int numberOfClients = 0;

    static GameManager* getInstance();

    void startUp(sf::RenderWindow* window);

    void timeCalculations();
    
    void createWorldObjects(sf::RenderWindow* window);

    //renders all players
    void renderWorldObjects(sf::RenderWindow* window, int numberOfClients, int selfId, int clientId1, float xpos1, float ypos1, int clientId2, float xpos2, float ypos2, int clientId3, float xpos3, float ypos3, int clientId4, float xpos4, float ypos4);

    void updateMovingPlatforms(int xpos);

    void sidescrollIfNeeded(sf::View* view, sf::RenderWindow* window);

    void clientLeave();
    
    // void eventCheck();
    //void renderOtherPlayers(sf::RenderWindow* window);

    //void otherPlayerUpdate(int clientId, float xpos, float ypos);

    //void allPlayersUpdate(sf::RenderWindow* window, int numberOfClients, int selfId, int clientId1, float xpos1, float ypos1, int clientId2, float xpos2, float ypos2, int clientId3, float xpos3, float ypos3);

    //takes input if window is focused and returns true if client paused
    bool takeInput(sf::RenderWindow* window);

    sf::Vector2f getPlayerPosition();

    GameManager();

    private:
    
     
    // static pointer which will points
    //to the instance of this class
    static GameManager* instancePtr;
    

    
};

#endif