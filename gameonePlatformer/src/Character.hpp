#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <vector>
#include "Pawn.hpp"
#include "ScriptManager.hpp"
#include "v8helpers.hpp"
//#include "v8/v8.hpp"
//#include "Timeline.hpp"

/**
specific class for player inheriting from pawn
*/
class Character : public Pawn, public sf::RectangleShape//, public Timeline
{
    public: 
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture chartex;
    sf::Vector2f bottomPoint;
    double halfplayerHeight;
    bool touchingGround;
    ScriptManager* sriptMan;
    //Timeline playertimeline;
    


    Character(float sizex, float sizey, int posX, int posY, const std::string& texture);

    sf::Vector2f getBottomPosition();

    void isOnGround(bool grounded);

    void setGroundedTime(int64_t groundTouchTime);

    int64_t getGroundedTime();

    void setScriptManager(ScriptManager *sm);

    //void createDefaultPlayerTimeLine();
};

#endif

