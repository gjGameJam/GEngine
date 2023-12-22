#include "GameManager.hpp"
#include <cstdio>
#include <iostream>
//#include <bits/stdc++.h>
   
//the pointer to game manager instance
GameManager* GameManager::instancePtr;

GameObject gameObjectsToRender[10]; //currently not using for simplicity sake (will be using storage like this in future)

//the timeline variables used for calculation based on elapsed time
Timeline* globalTimeline;
int64_t pausePressDelay = 0;
int64_t last_time;
double movementDelta = 0;

//intialize objects as global variables for game manager to manipulate
Platform movingPlatform1 = Platform(false, 200.f, 50.f, 225, 300, sf::Color(150, 128, 120));
Platform movingPlatform2 = Platform(false, 75.f, 75.f, 700, 400, sf::Color(220, 0, 120));
Platform grass = Platform(true, 3000.f, 400.f, -1000, 300, sf::Color(0, 128, 0));
//Platform platform2 = Platform(true, 100.f, 50.f, 210, 450, sf::Color(128, 0, 0));
//Platform platform3 = Platform(true, 50.f, 50.f, 420, 460, sf::Color(0, 0, 128));
static float playerWidth = 50.f;
Character player = Character(playerWidth, 50.f, 400, 300, "../src/spaceship.png");
Character altPlayer1 = Character(50.f, 50.f, 20, 300, "../src/spaceship.png"); //change to sprite/picture only
Character altPlayer2 = Character(50.f, 50.f, 20, 300, "../src/spaceship.png"); //change to sprite/picture only
Character altPlayer3 = Character(50.f, 50.f, 20, 300, "../src/spaceship.png"); //change to sprite/picture only
Character altPlayer4 = Character(50.f, 50.f, 20, 300, "../src/spaceship.png"); //change to sprite/picture only

Deathzone dzone = Deathzone(1000.f, 70.f, -200, 500);
Platform asteroid1 = Platform(true, 100.f, 100.f, 210, -450, sf::Color(128, 128, 128));
Platform asteroid2 = Platform(true, 200.f, 200.f, 790, -300, sf::Color(128, 128, 128));
Platform asteroid8 = Platform(true, 50.f, 50.f, 550, -500, sf::Color(128, 128, 128));
Platform asteroid9 = Platform(true, 25.f, 25.f, 100, -700, sf::Color(128, 128, 128));
Platform asteroid10 = Platform(true, 125.f, 125.f, 750, -800, sf::Color(128, 128, 128));
Platform asteroid11 = Platform(true, 125.f, 125.f, 750, -1000, sf::Color(128, 128, 128));
Platform asteroid3 = Platform(true, 200.f, 200.f, 400, -3000, sf::Color(128, 128, 128));
Platform asteroid4 = Platform(true, 150.f, 150.f, 150, -1000, sf::Color(128, 128, 128));
Platform asteroid5 = Platform(true, 175.f, 175.f, 500, -1200, sf::Color(128, 128, 128));
Platform asteroid6 = Platform(true, 50.f, 50.f, 550, -1400, sf::Color(128, 128, 128));
Platform asteroid7 = Platform(true, 66.f, 66.f, 230, -1300, sf::Color(128, 128, 128));

Platform asteroid12 = Platform(true, 100.f, 100.f, 210, -1450, sf::Color(128, 128, 128));
Platform asteroid13 = Platform(true, 200.f, 200.f, 790, -1300, sf::Color(128, 128, 128));
Platform asteroid14 = Platform(true, 50.f, 50.f, 550, -1500, sf::Color(128, 128, 128));
Platform asteroid15 = Platform(true, 25.f, 25.f, 100, -1700, sf::Color(128, 128, 128));
Platform asteroid21 = Platform(true, 125.f, 125.f, 750, -1800, sf::Color(128, 128, 128));
Platform asteroid22 = Platform(true, 125.f, 125.f, 750, -2000, sf::Color(128, 128, 128));
Platform asteroid16 = Platform(true, 180.f, 180.f, 550, -3500, sf::Color(128, 128, 128));
Platform asteroid17 = Platform(true, 150.f, 150.f, 150, -2000, sf::Color(128, 128, 128));
Platform asteroid18 = Platform(true, 175.f, 175.f, 500, -2200, sf::Color(128, 128, 128));
Platform asteroid20 = Platform(true, 90.f, 90.f, 0, -2300, sf::Color(128, 128, 128));
Platform asteroid19 = Platform(true, 50.f, 50.f, 550, -2400, sf::Color(128, 128, 128));
Platform asteroid23 = Platform(true, 66.f, 66.f, 230, -2500, sf::Color(128, 128, 128));
Platform asteroid26 = Platform(true, 25.f, 25.f, 750, -2500, sf::Color(128, 128, 128));
Platform asteroid24 = Platform(true, 125.f, 125.f, 0, -2600, sf::Color(128, 128, 128));
Platform asteroid25 = Platform(true, 266.f, 266.f, 400, -3000, sf::Color(128, 128, 128));
Platform asteroid27 = Platform(true, 100.f, 100.f, 200, -2800, sf::Color(128, 128, 128));
Platform asteroid28 = Platform(true, 65.f, 75.f, 400, -2900, sf::Color(128, 128, 128));
Platform asteroid29 = Platform(true, 160.f, 160.f, 600, -2700, sf::Color(128, 128, 128));

Platform asteroid30 = Platform(true, 100.f, 100.f, 210, -3450, sf::Color(128, 128, 128));
Platform asteroid31 = Platform(true, 200.f, 200.f, 790, -3300, sf::Color(128, 128, 128));
Platform asteroid32 = Platform(true, 50.f, 50.f, 550, -3500, sf::Color(128, 128, 128));
Platform asteroid33 = Platform(true, 125.f, 125.f, 100, -3700, sf::Color(128, 128, 128));
Platform asteroid34 = Platform(true, 125.f, 125.f, 750, -3800, sf::Color(128, 128, 128));
Platform asteroid35 = Platform(true, 125.f, 125.f, 600, -4000, sf::Color(128, 128, 128));
Platform asteroid36 = Platform(true, 40.f, 40.f, 400, -4200, sf::Color(128, 128, 128));
Platform asteroid37 = Platform(true, 150.f, 150.f, 150, -4000, sf::Color(128, 128, 128));
Platform asteroid38 = Platform(true, 175.f, 175.f, 500, -4100, sf::Color(128, 128, 128));
Platform asteroid39 = Platform(true, 50.f, 50.f, 550, -4400, sf::Color(128, 128, 128));
Platform asteroid40 = Platform(true, 166.f, 166.f, 230, -4300, sf::Color(128, 128, 128));

Platform asteroid41 = Platform(true, 100.f, 100.f, 210, -4450, sf::Color(128, 128, 128));
Platform asteroid42 = Platform(true, 200.f, 200.f, 790, -4300, sf::Color(128, 128, 128));
Platform asteroid48 = Platform(true, 50.f, 50.f, 550, -4500, sf::Color(128, 128, 128));
Platform asteroid49 = Platform(true, 25.f, 25.f, 100, -4700, sf::Color(128, 128, 128));
Platform asteroid52 = Platform(true, 33.f, 33.f, 0, -4750, sf::Color(128, 128, 128));
Platform asteroid50 = Platform(true, 125.f, 125.f, 750, -4800, sf::Color(128, 128, 128));
Platform asteroid51 = Platform(true, 150.f, 150.f, 750, -5000, sf::Color(128, 128, 128));
Platform asteroid43 = Platform(true, 200.f, 200.f, 400, -6000, sf::Color(128, 128, 128));
Platform asteroid44 = Platform(true, 150.f, 150.f, 150, -5000, sf::Color(128, 128, 128));
Platform asteroid45 = Platform(true, 175.f, 175.f, 500, -5200, sf::Color(128, 128, 128));
Platform asteroid46 = Platform(true, 75.f, 75.f, 550, -5400, sf::Color(128, 128, 128));
Platform asteroid47 = Platform(true, 166.f, 166.f, 230, -5300, sf::Color(128, 128, 128));
float viewBoxWidth = 800.f;
viewBoundBox viewBox = viewBoundBox(viewBoxWidth, 600.f, 0, 0);

//bounds for side scroll
// long leftBound = 0;
// long rightBound = 800;
//  each gamemanager has a physics engine singleton in order to only spawn it once
PhysicsEngine *physEngine;
EventManager *eventManager;

sf::Sprite background;

Spawnpoint spawnpoint1 = Spawnpoint(400, 300);



    //Private constructor to prevent external instantiation.
    GameManager::GameManager() {
        // Constructor code here.
    }


 
    /*
    getInstance() is a static method that returns an
    instance when called. It returns the same
    instance if it is called more than once because the desired
    functionality of a singleton is for there only to be one
    */
    GameManager* GameManager::getInstance()
    {
    // If there is no instance of class
    // then we can create an instance.
    if (instancePtr == nullptr)
        {
            // We can access private members
            // within the class.
            instancePtr = new GameManager();
       
        }

        // returning the instance pointer
        return instancePtr;
    }
 


//function to create player, moving platform, and static platform
void GameManager::createWorldObjects(sf::RenderWindow* window){ //NO LONGER IN USE
    printf("creating all world objects\n");

    //store all objects in to render array in order to render later (field is: GameObject gameObjectsToRender[10];)
    gameObjectsToRender[0] = grass;
    gameObjectsToRender[1] = movingPlatform1;
    gameObjectsToRender[2] = player;
    //so gameObjectsToRender should be {grass, movingPlatform1, player}
    
    
}

//function to render/rerender player, moving platform, and static platform
void GameManager::renderWorldObjects(sf::RenderWindow* window, int numberOfClients, int selfId, int clientId1, float xpos1, float ypos1, int clientId2, float xpos2, float ypos2, int clientId3, float xpos3, float ypos3, int clientId4, float xpos4, float ypos4){
    
    //clears window
    window->clear(sf::Color::Black);
    //draw background
    window->draw(background);
    //draws player and asteroids
    window->draw(grass);
    window->draw(asteroid1);
    window->draw(asteroid2);
    window->draw(asteroid3);
    window->draw(asteroid4);
    window->draw(asteroid5);
    window->draw(asteroid6);
    window->draw(asteroid7);
    window->draw(asteroid8);
    window->draw(asteroid9);
    window->draw(asteroid10);
    window->draw(asteroid11);
    window->draw(asteroid12);
    window->draw(asteroid13);
    window->draw(asteroid14);
    window->draw(asteroid15);
    window->draw(asteroid16);
    window->draw(asteroid17);
    window->draw(asteroid18);
    window->draw(asteroid19);
    window->draw(asteroid20);
    window->draw(asteroid21);
    window->draw(asteroid22);
    window->draw(asteroid23);
    window->draw(asteroid24);
    window->draw(asteroid25);
    window->draw(asteroid26);
    window->draw(asteroid27);
    window->draw(asteroid28);
    window->draw(asteroid29);
    window->draw(asteroid30);
    window->draw(asteroid31);
    window->draw(asteroid32);
    window->draw(asteroid33);
    window->draw(asteroid34);
    window->draw(asteroid35);
    window->draw(asteroid36);
    window->draw(asteroid37);
    window->draw(asteroid38);
    window->draw(asteroid39);
    window->draw(asteroid40);
    window->draw(asteroid41);
    window->draw(asteroid42);
    window->draw(asteroid43);
    window->draw(asteroid44);
    window->draw(asteroid45);
    window->draw(asteroid46);
    window->draw(asteroid47);
    window->draw(asteroid48);
    window->draw(asteroid49);
    window->draw(asteroid50);
    window->draw(asteroid51);
    window->draw(asteroid52);

    //window->draw(movingPlatform1);
    //window->draw(movingPlatform2);
    //window->draw(platform2);
    //window->draw(platform3);
    

    //check for death event (player touching death zone)
    if (eventManager->checkForDeathEvent(&player, &dzone) || physEngine->collisionCheck(asteroid1, player, eventManager)  || physEngine->collisionCheck(asteroid2, player, eventManager)  || physEngine->collisionCheck(asteroid3, player, eventManager)  || physEngine->collisionCheck(asteroid4, player, eventManager) || physEngine->collisionCheck(asteroid5, player, eventManager)  || physEngine->collisionCheck(asteroid6, player, eventManager)  || physEngine->collisionCheck(asteroid7, player, eventManager)  || physEngine->collisionCheck(asteroid8, player, eventManager)  || physEngine->collisionCheck(asteroid9, player, eventManager) || physEngine->collisionCheck(asteroid10, player, eventManager)
     || physEngine->collisionCheck(asteroid11, player, eventManager)  || physEngine->collisionCheck(asteroid12, player, eventManager)  || physEngine->collisionCheck(asteroid13, player, eventManager)  || physEngine->collisionCheck(asteroid14, player, eventManager) || physEngine->collisionCheck(asteroid15, player, eventManager)  || physEngine->collisionCheck(asteroid16, player, eventManager)  || physEngine->collisionCheck(asteroid17, player, eventManager)  || physEngine->collisionCheck(asteroid18, player, eventManager)  || physEngine->collisionCheck(asteroid19, player, eventManager) || physEngine->collisionCheck(asteroid20, player, eventManager)
    || physEngine->collisionCheck(asteroid31, player, eventManager)  || physEngine->collisionCheck(asteroid32, player, eventManager)  || physEngine->collisionCheck(asteroid33, player, eventManager)  || physEngine->collisionCheck(asteroid34, player, eventManager) || physEngine->collisionCheck(asteroid35, player, eventManager)  || physEngine->collisionCheck(asteroid36, player, eventManager)  || physEngine->collisionCheck(asteroid37, player, eventManager)  || physEngine->collisionCheck(asteroid38, player, eventManager)  || physEngine->collisionCheck(asteroid39, player, eventManager) || physEngine->collisionCheck(asteroid40, player, eventManager)
    || physEngine->collisionCheck(asteroid41, player, eventManager)  || physEngine->collisionCheck(asteroid42, player, eventManager)  || physEngine->collisionCheck(asteroid43, player, eventManager)  || physEngine->collisionCheck(asteroid44, player, eventManager) || physEngine->collisionCheck(asteroid45, player, eventManager)  || physEngine->collisionCheck(asteroid46, player, eventManager)  || physEngine->collisionCheck(asteroid47, player, eventManager)  || physEngine->collisionCheck(asteroid48, player, eventManager)  || physEngine->collisionCheck(asteroid49, player, eventManager) || physEngine->collisionCheck(asteroid50, player, eventManager) || physEngine->collisionCheck(asteroid51, player, eventManager) || physEngine->collisionCheck(asteroid52, player, eventManager)
      || physEngine->collisionCheck(asteroid21, player, eventManager)  || physEngine->collisionCheck(asteroid22, player, eventManager)  || physEngine->collisionCheck(asteroid23, player, eventManager)  || physEngine->collisionCheck(asteroid24, player, eventManager) || physEngine->collisionCheck(asteroid25, player, eventManager)  || physEngine->collisionCheck(asteroid26, player, eventManager)  || physEngine->collisionCheck(asteroid27, player, eventManager)  || physEngine->collisionCheck(asteroid28, player, eventManager)  || physEngine->collisionCheck(asteroid29, player, eventManager) || physEngine->collisionCheck(asteroid30, player, eventManager)){
        //create map of variants to define collision that will cause death event
            std::map<std::string, variant> deathMap;
            //create variant for death event
            variant deathVariant = {variant::TYPE_SPAWNPOINT, 1};
            //set the union's data in variant to hold the position of the spawn point
            deathVariant.Vunion.spoint = &spawnpoint1;
            //insert the input variant into the map of variants
            deathMap.insert(std::pair<std::string, variant>("collision", deathVariant));
            //construct event
            Event deathEvent = Event(deathMap, 0); //second param is delay (which we don't want for input events)
            //set the type and trigger player
            deathEvent.type = deathEvent.EVENT_TYPE_COLLISION;
            deathEvent.death = true;
            deathEvent.triggerPlayer = &player;
            //inputEvent.deltaTime = movementDelta;
            //then raise event
            eventManager->raise(deathEvent);
            //the function call to actually respawn client is handled by event manager
            //spawnpoint1.respawnClient(&player);
    }
    //update event manager's priority queue to make events happen that should be happening
    eventManager->update();
    

    //now draw player upon potential respawn
    window->draw(player);

    //draws other clients if they exist (and aren't the original client)
    if (clientId1 != 0 && selfId != clientId1){
        //printf("APU1\n");
        altPlayer1.setPosition(xpos1, ypos1);
        window->draw(altPlayer1);
    }
    if (clientId2 != 0 && selfId != clientId2){
        //printf("APU2\n");
        altPlayer2.setPosition(xpos2, ypos2);
        window->draw(altPlayer2);
    }
    if (clientId3 != 0 && selfId != clientId3){
        //printf("APU3\n");
        altPlayer3.setPosition(xpos3, ypos3);
        window->draw(altPlayer3);
    }
    if (clientId4 != 0 && selfId != clientId4){
        //printf("APU4\n");
        altPlayer3.setPosition(xpos4, ypos4);
        window->draw(altPlayer4);
    }

    //And display everything just drawn on window (could be all clients)
    window->display();
    
    
}

//called before main loop to set up sfml window/game enviroment
void GameManager::startUp(sf::RenderWindow* window){
    //references passed in window and sets the style and position
    sf::Style::Default;
    window->setPosition(sf::Vector2i(200, 50));
    //limit framerate to 60
    window->setFramerateLimit(60);
    globalTimeline = new Timeline();   //intitialize globalTimeline as a Timeline object
    //gets time before loop (last time)
    last_time = globalTimeline->getTime();
    //create physics engine
    //creates the singleton instance of the physics engine for each client
    PhysicsEngine* physEngine = PhysicsEngine::getInstance();
    player.setName("player1");
    //creates the singleton instance of the physics engine for each client
    EventManager* eventManager = EventManager::getInstance();

    //used base code from on lines 294 to 309:
    //https://stackoverflow.com/questions/36448101/2-3-1-set-scale-of-background-texture-to-renderwindow-size
    sf::Texture BackgroundTexture;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.

    if (!BackgroundTexture.loadFromFile("../src/Space_Stars1.png")){
        printf("background texture wasn't loaded in properly\n");
        return;
    }
    TextureSize = BackgroundTexture.getSize(); //Get size of texture.
    WindowSize = window->getSize();             //Get size of window.

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

    (&background)->setTexture(BackgroundTexture);
    (&background)->setScale(ScaleX, ScaleY);      //Set scale.  

}

//takes player input to pause, change tic size, and move
//only want to take input when window is focused (so clients don't all read each other's input)
bool GameManager::takeInput(sf::RenderWindow* window){
    bool clientHasPaused = false;
    //printf("reading input\n");
    if (!window->hasFocus()){ //only take input when window is focused
        return clientHasPaused;
    }

    //creates array of ints to store which keys are being pressed
    //int *inputBools = (int*)malloc(sizeof(int*));
    //int inputBools[7] = {0};
    int *inputBools = new int[7];
    std::fill(inputBools, inputBools + 7, 0);
    bool inputRead = false; //and bool to determine if any are pressed

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //movement now being handled by input event
        //player.move(-2 * movementDelta,0);
        inputRead = true;
        //the index of inputbools is determined by the order of if statements
        inputBools[0] = 1;
    }

    //press right to move right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //movement now being handled by input event
        //player.move(2 * movementDelta,0);
        inputRead = true;
        //the index of inputbools is determined by the order of if statements
        inputBools[1] = 1;
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    //     inputBools[0] = 0;
    //     inputBools[1] = 0;
    //     inputBools[2] = 1;
    //     player.rotate(2);
    //     //printf("\n\n\nBANG\n\n\n");
    // }

    //press up to move up
    //movement now being handled by input event
    //always want rocket to be moving through asteroid field
    inputRead = true;
    //the index of inputbools is determined by the order of if statements
    inputBools[2] = 1;

    // //press down to move down if not colliding
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

    //     //can only move down if not colliding with ground already
    //     if (!player.touchingGround){
    //     player.move(0,3 * movementDelta);
    //     }    
    // }
    
    //Collision and gravity section
    //want to make more efficient, could pass vectorwith all desired collisions to avoid repeat calling of function
    // if (physEngine->collisionCheck(grass, player, eventManager) || physEngine->collisionCheck(movingPlatform1, player, eventManager) || physEngine->collisionCheck(platform2, player, eventManager) || physEngine->collisionCheck(platform3, player, eventManager) || physEngine->collisionCheck(movingPlatform2, player, eventManager))
    // {
    //     //collision logic now handled by event
    //     // player.isOnGround(true);
    //     // player.setGroundedTime(globalTimeline->getTime());
    // }
    // else {
    //     //and move player down with gravity if not on ground
    //     //printf("go touch grass\n");
    //     player.isOnGround(false);
    //     //player.move(0,1 * movementDelta);
    //     player.move(0,(movementDelta * (1 + gravScale)));
    // }

    //press 1 to set time speed to 0.50
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        //printf("tic to .5\n");
        //globalTimeline->changeTic(1);
        inputRead = true;
        //the index of inputbools is determined by the order of if statements
        inputBools[3] = 1;
    }

    //press 2 to set time speed to 1.00
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        //printf("tic to 1\n");
        //globalTimeline->changeTic(2);
        inputRead = true;
        //the index of inputbools is determined by the order of if statements
        inputBools[4] = 1;
    }

    //press 3 to set time speed to 2.00
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        //printf("tic to 2\n");
        //globalTimeline->changeTic(4);
        inputRead = true;
        //the index of inputbools is determined by the order of if statements
        inputBools[5] = 1;

    }

    //press P to pause the game
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            
        //only allow toggling every quarter second (250 ms)
        if (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count() - pausePressDelay >= 500){
            //input event content
            inputRead = true;
            //the index of inputbools is determined by the order of if statements
            inputBools[6] = 1;
            //and set time for last pause press
            pausePressDelay = std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count();
            clientHasPaused = true;
            //pause now happening via event
            // if (!(globalTimeline->isPaused())){
            //     printf("was unpaused now pausing\n");
            //     globalTimeline->pause();
            // }
            // else if (globalTimeline->isPaused()){
            //     printf("was paused now unpausing\n");
            //     globalTimeline->unpause();
            // }
        }
            

    }

    //so at this point all potential input has been read
    if (inputRead){
        //create map of variants to define event
        std::map<std::string, variant> inputMap;
        //create variant for input array
        variant inputVariant = {variant::TYPE_INPUT, 1};
        //set the union's data in variant to hold the input array of booleans
        inputVariant.Vunion.inputArray = inputBools;
        //insert the input variant into the map of variants
        inputMap.insert(std::pair<std::string, variant>("input", inputVariant));

        //construct event with full map of paramters, the delay for input is 0
        Event inputEvent = Event(inputMap, 0); //second param is delay (which we don't want for input events)
        //set the type and trigger player
        inputEvent.type = inputEvent.EVENT_TYPE_INPUT;
        inputEvent.triggerPlayer = &player;
        inputEvent.deltaTime = movementDelta;
        //besides the array of inputs, we also care about timeline manipulation
        inputEvent.tline = globalTimeline;
        //then raise event
        //printf("raise input event\n");
        eventManager->raise(inputEvent);
    }

    return clientHasPaused;

    
}

/**
 * updates the time variables in the gamemanager
*/
void GameManager::timeCalculations(){
    //start with time calculations
    int64_t current_time = globalTimeline->getTime();
    int64_t frame_delta = current_time - last_time;
    frame_delta = frame_delta / globalTimeline->getTic();
    last_time = current_time;
    //printf("current timeline time (ms): %ld\n", current_time);
    //printf("frame delta (ms): %ld\n", frame_delta);
        
    movementDelta = (frame_delta % 10) / 3;
    if (frame_delta != 0){
        movementDelta++;
        movementDelta++;
    }
    //printf("movement delta (ms): %f\n", movementDelta);
    //then call render and input functions right here
    //movingPlatform1.Oscilate(225, 550, 2.00f * movementDelta);
}

sf::Vector2f GameManager::getPlayerPosition(){
    return player.getPosition();
}

//plan on changing this method to receive a number (1-100)
//that represents each platform's stage
void GameManager::updateMovingPlatforms(int position){
    //printf("updatemovingPlatformNumber: %d\n", position);
    movingPlatform1.setPosition(position, 320);
    movingPlatform2.setPosition(700, (position - 150));
}

//return 0 if no shift is needed
//return -1 if left shift is needed
//return 1 if right shift is needed
int sidescrollLogicNumber(){
    
    int leftx = viewBox.getPosition().x;
    int rightx = viewBox.getPosition().x + viewBoxWidth;
    //printf("playerXpos: %f\n", player.getPosition().x);
    //printf("leftx: %d\n", leftx);
    //printf("rightx: %d\n", rightx);
    
    if (player.getPosition().x <= leftx){ //compares player x to viewbox left x
        (&player)->setPosition(leftx + 5, player.getPosition().y);
        return 0;
    }
    if ((player.getPosition().x + playerWidth) >= rightx){ //compares player x to viewbox right x
        (&player)->setPosition(rightx - playerWidth, player.getPosition().y);
        return 0;
    }
    //so we have a box that should check if player is before or after x positions to move left or right
    return 0;
}

void GameManager::sidescrollIfNeeded(sf::View* view, sf::RenderWindow* window){
    //gets either 0 (none), -1 (left), or 1 (right)
    int sideScrollNum = sidescrollLogicNumber();
    //printf("sideScrollLogicNum: %d\n", sideScrollNum);
    if (sideScrollNum == 0){
        //move view up to follow space ship
        view->setCenter(player.getPosition().x, player.getPosition().y);
        //view->move(0.f, -1.f * movementDelta);
        window->setView(*view);
        return;
        
    }
    else if(sideScrollNum == 1){
        //printf("moveRIGHT!\n");
        //move view to adjust new desired view
        viewBox.shift(10.f, 0.f);
        view->move(10.f, 0.f);
        window->setView(*view);
        

    }
    else if(sideScrollNum == -1){
        //printf("moveLeft!\n");
        //move view to adjust new desired view
        viewBox.shift(-10.f, 0.f);
        view->move(-10.f, 0.f);
        window->setView(*view);
        

    }
}

// void GameManager::eventCheck(){

// }



//method for rendering other player(s)
//logic for player joining/positions are handled by otherPlayerUpdate
// void GameManager::renderOtherPlayers(sf::RenderWindow* window){
    
//     //draws other players if they've joined
//     if (player2Joined){
//         printf("rendering player2 object\n");
//         window->draw(altPlayer1);
//     }
//     if (player3Joined){
//         printf("rendering player3 object\n");
//         window->draw(altPlayer2);
//     }

// }

// void GameManager::allPlayersUpdate(sf::RenderWindow* window, int numberOfClients, int selfId, int clientId1, float xpos1, float ypos1, int clientId2, float xpos2, float ypos2, int clientId3, float xpos3, float ypos3){

//     if (clientId1 != 0 && selfId != clientId1){
//         printf("APU1\n");
//         altPlayer1.setPosition(xpos1, ypos1);
//         window->draw(altPlayer1);
//     }
//     if (clientId2 != 0 && selfId != clientId2){
//         printf("APU2\n");
//         altPlayer2.setPosition(xpos2, ypos2);
//         window->draw(altPlayer2);
//     }
//     if (clientId3 != 0 && selfId != clientId3){
//         printf("APU3\n");
//         altPlayer3.setPosition(xpos3, ypos3);
//         window->draw(altPlayer3);
//     }

// }


//method is to update clients and their respective joined status/position
//this method will help renderWorldObjects function easier
// void GameManager::otherPlayerUpdate(int clientId, float xpos, float ypos){
//     if (clientId <= 0){
//         return;
//     }
    
//     //if player two hasn't joined
//     if (!player2Joined){
//         //then set bool to true and update position of player2
//         player2Joined = true;
//         player2ID = clientId;
//         altPlayer1.setPosition(xpos, ypos);
//         std::cout << "player2 joining with (ID,X,Y): " << clientId << "," << xpos<< "," << ypos << std::endl;
//     }
//     else if (player2Joined && player2ID == clientId){ //case where player two joined and is sending another message
//         std::cout << "updating player2 with (ID,X,Y): " << clientId << "," << xpos<< "," << ypos << std::endl;
//         altPlayer1.setPosition(xpos, ypos);
//     }
//     else if (!player3Joined){ //if player three hasn't joined
//         //then set bool to true and update position of player2
//         player3Joined = true;
//         player3ID = clientId;
//         altPlayer2.setPosition(xpos, ypos);
//         std::cout << "player3 joining with (ID,X,Y): " << clientId << "," << xpos<< "," << ypos << std::endl;
//     }
//     else if (player3Joined && player3ID == clientId){ //case where player three joined and is sending another message
//         std::cout << "updating player3 with (ID,X,Y): " << clientId << "," << xpos<< "," << ypos << std::endl;
//         altPlayer2.setPosition(xpos, ypos);
//     }
    
// }

