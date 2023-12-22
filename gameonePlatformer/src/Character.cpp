#include "Character.hpp"
#include <vector>
#include "ScriptManager.hpp"
#include "v8helpers.hpp"
//#include "v8/v8.hpp"
//the pointer ScriptManager instance


/**
specific class for player inheriting from pawn
*/

    //stores the time when the player last touched ground
    int64_t groundedTime = 0;

    Character::Character(float sizex, float sizey, int posX, int posY, const std::string& texture) : sf::RectangleShape(sf::Vector2f((sizex + 0.f), (sizey + 0.f))){ //, Timeline::Timeline() 
        setPosition((posX + 0.f), (posY + 0.f)); // you can do this because the class extends RectangleShape, so it has setPosition and setFillColor

        if (!chartex.loadFromFile(texture))
        {
            printf("filled player with red to indicate missing file \n");
            setFillColor(sf::Color(150, 0, 0));
        }

        //tex.update(playerImg);
        //sf::Texture::bind(&tex);
        setTexture(&chartex);
        halfplayerHeight = sizey / 2;
        //printf("%f \n", halfplayerHeight);
        //int64_t defaultTic = 60;
        //createDefaultPlayerTimeLine();
        //Timeline();
        
        
        
    } 

    sf::Vector2f Character::getBottomPosition()
    {
        //get midpoint of player
        sf::Vector2f point = getOrigin();
        //make vector to player foot
        sf::Vector2f originToPlayerFoot = sf::Vector2f(0, halfplayerHeight);

        //add vectors to determine exact position of player's foot
        point += originToPlayerFoot;
        return point;
    }

    void Character::isOnGround(bool grounded)
    {
        touchingGround = grounded;
    }

    // void Character::createDefaultPlayerTimeLine(){
    //     Timeline playertimeline();
    // }

    void Character::setGroundedTime(int64_t groundTouchTime){
        //sets the player groundedTime field
        groundedTime = groundTouchTime;
    }

    int64_t Character::getGroundedTime(){
        //gets the player groundedTime field
        return groundedTime;
    }

    void Character::setScriptManager(ScriptManager *sm) {
        this->sriptMan = sm;
    }