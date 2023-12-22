// #include <SFML/Graphics.hpp>
// #include <cassert>
// #include <string>
// #include <thread>
// #include <chrono>
// #include <mutex>
// #include <condition_variable>
// #include <iostream>


// #include "GameManager.hpp"
// //#include "Timeline.hpp"

// //PhysicsEngine physEngine;
// static int windowResize = 1;

// //int64_t pausePressDelay = 0;
// //global timeline now in game manager
// //Timeline* globalTimeline;

// GameManager *gameManager;

// sf::RenderWindow window(sf::VideoMode(800, 600), "My scalable window :)");


// /**
// specific class for enemy inheriting from pawn
// */
// class Enemy : public Pawn
// {
//     //body
// };

// class ForkAndJoinExample
// {
//     bool busy; // a member variable used to indicate thread "status"
//     int i; // an identifier
//     ForkAndJoinExample *other; // a reference to the "other" thread in this example
//     std::mutex *_mutex; // the object for mutual exclusion of execution
//     std::condition_variable *_condition_variable; // for messaging between threads

//     public:
//         ForkAndJoinExample(int i, ForkAndJoinExample *other, std::mutex *_mutex, std::condition_variable *_condition_variable)
//         {
//             this->i = i; // set the id of this thread
//             if(i==0) { busy = true; }
//             else { this->other = other; }
//             this->_mutex = _mutex;
//             this->_condition_variable = _condition_variable;
//         }

//         bool isBusy()
//         {
//             // this locks the mutuex until the variable goes out of scope (i.e., when the function returns in this case)
//             std::lock_guard<std::mutex> lock(*_mutex);
//             return busy;
//         }

//         void run()
//         {
//             if(i==0)
//             {
//                 //thread zero functions here
//                 //consider passing in render window to run and drawing objects through gamemanager draw
                
//                 try
//                 {
//                     //std::unique_lock<std::mutex> cv_lock(*this->_mutex);

//                     //need to update internal time variables in game manager
//                     gameManager->timeCalculations();
//                     //and take player input
//                     gameManager->takeInput();
//                     //then render the objects based on elapsed time
//                     gameManager->renderWorldObjects(&window);
                    
//                     //the two lines below could be a source of error
//                     busy = !busy; //indicate no longer busy
//                     _condition_variable->notify_all(); //and notify all
//                     std::cout << "Thread " << i << " is FINISHED!" << std::endl;
//                     // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//                     // { // anonymous inner block to manage scop of mutex lock 
//                     //     std::unique_lock<std::mutex> cv_lock(*this->_mutex);
//                     //     std::cout << "Thread " << i << " is done sleeping" << std::endl;
//                     //     _condition_variable->notify_all();
//                     //     std::cout << "Thread " << i << " is notifying with busy=" << busy << std::endl;
//                     //     //here it should be busy, so should I call functions for thread 0 here?
//                     // }
//                     // std::cout << "Thread " << i << " is sleeping" << std::endl;
//                     // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//                     // { // anonymous inner block to manage scop of mutex lock 
//                     //     std::unique_lock<std::mutex> cv_lock(*this->_mutex);
//                     //     _condition_variable->notify_all();
//                     //     std::cout << "Thread " << i << " is notifying with busy=" << busy << std::endl;
//                     // }
//                     // std::cout << "Thread " << i << " is sleeping" << std::endl;
//                     // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//                     // { // anonymous inner block to manage scop of mutex lock 
//                     //     std::unique_lock<std::mutex> cv_lock(*this->_mutex);
//                     //     busy = !busy;
//                     //     _condition_variable->notify_all();
//                     //     std::cout << "Thread " << i << " is notifying with busy=" << busy << std::endl;
//                     //     std::cout << "Thread " << i << " is FINISHED!" << std::endl;
//                     //}
//                 }
//                 catch (...)
//                 {
//                     std::cerr << "Thread " << i << " caught exception." << std::endl;
//                 }
//             }
//             else // id == 1
//             {
//                 while(other->isBusy())
//                 {
//                     std::cout << "Thread " << i << " is waiting!" << std::endl;
//                     try 
//                     {
//                         std::unique_lock<std::mutex> lock(*_mutex);
//                         _condition_variable->wait(lock);
//                         std::cout << "Thread " << i << " inside lock scope." << std::endl;
//                     }
//                     catch (...)
//                     {
//                         std::cerr << "Thread " << i << " caught exception." << std::endl;
//                     }
//                 }
//                 //before thread one finishes
//                 std::cout << "Thread " << i << " is FINISHED!" << std::endl;
//                 //so thread one just finished
//             }
//         }

// };

// /**
//  * Wrapper function because threads can't take pointers to member functions.
//  */
// void run_wrapper(ForkAndJoinExample *fe)
// {
//     fe->run();
// }



// /**
//  main function that uses two threads to call different game manager functions
// */
// int main()
// {
//     //XInitThreads(); // <-needed for linux?
//     //creates the singleton instance of GameManager
//     gameManager = GameManager::getInstance();
//     //sets up window properties
//     gameManager->startUp(&window);

//     //create physics engine (WIP) don't mind this
//     PhysicsEngine physEngine();

//     // Mutex to handle locking, condition variable to handle notifications between threads
//     std::mutex m;
//     std::condition_variable cv;

//     // // Create thread objects
//     // ForkAndJoinExample t1(0, NULL, &m, &cv);  //thread1
//     // ForkAndJoinExample t2(1, &t1, &m, &cv);   //thread2

//     // // Start threads
//     // std::thread first(run_wrapper, &t1);
//     // std::thread second(run_wrapper, &t2);

//     // // Make sure both threads are complete before stopping main thread
//     // printf("1");
//     // first.join();
//     // printf("2");
//     // second.join();
//     // printf("3");
    
//     //passes in window to for game manager to draw objects on
//     //gameManager->createWorldObjects(&window);


//     //create the platform within platform class and call it grass
//     //Platform grass(true, 200.f, 50.f, 10, 400, sf::Color(0, 128, 0));
//     //Platform movingPlatform(false, 200.f, 50.f, 225, 320, sf::Color(150, 128, 120));
//     //create player with texture
//     //Character player(50.f, 50.f, 20, 300, "beachball.png");
//     //player.setName("player");
    
    


//     //Timeline anchoredTimeline(globalTimeline*, 60);
    
//     //gets time before loop (last time)
//     //int64_t last_time = globalTimeline->getTime();
    
//     //while window is open delegate to threads
//     gameManager->createWorldObjects(&window);
//     //then the main game loop
//     while (window.isOpen())
//     {
//         // Create thread objects
//         ForkAndJoinExample t1(0, NULL, &m, &cv);  //thread1
//         ForkAndJoinExample t2(1, &t1, &m, &cv);   //thread2

//         // Start threads
//         std::thread first(run_wrapper, &t1);
//         std::thread second(run_wrapper, &t2);

//         // Make sure both threads are complete before joining
//         printf("first thread start\n");
//         first.join();
//         printf("first thread done, second thread start\n");
//         second.join();
//         printf("second thread done\n");
        
//         //start with time calculations
//         // int64_t current_time = globalTimeline->getTime();
//         // int64_t frame_delta = current_time - last_time;
//         // frame_delta = frame_delta / globalTimeline->getTic();
//         // last_time = current_time;
//         // //printf("current timeline time (ms): %ld\n", current_time);
//         // //printf("frame delta (ms): %ld\n", frame_delta);
        
//         // double movementDelta = (frame_delta % 10) / 3;
//         // if (frame_delta != 0){
//         //     movementDelta++;
//         //     movementDelta++;
//         // }
//         //printf("movement delta (ms): %f\n", movementDelta);

//         //need to get actual tic size
//         //int64_t timeMultiplier =  frame_delta / ticSize;
//         //printf("Time mult (ms): %ld\n", timeMultiplier);

//         //then window setup
//         // window.clear(sf::Color::Black);
//         // //platform game object named grass
//         // //window.draw(grass);
//         // window.draw(movingPlatform);
//         // window.draw(player);

//         // //oscilate all necessary platforms
//         // //movingPlatform.Oscilate(225, 550, 2.00f * movementDelta);

//         // // end the current frame
//         // window.display();

//         // printf("grass (x,y): %f ", grass.getPosition().x);
//         // printf("%f\n", grass.getPosition().y);

//         // printf("player (x,y): %f ", player.getPosition().x);
//         // printf("%f\n", player.getPosition().y);
        
//         //press left to move left
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//         //     player.move(-2 * movementDelta,0);
//         // }

//         // //press right to move right
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//         //     player.move(2 * movementDelta,0);
//         // }

//         // //press up to move up
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//         //     player.move(0,-3 * movementDelta);
//         //     player.isOnGround(false);
//         // }

//         // //press down to move down if not colliding
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

//         //     //can only move down if not colliding with ground already
//         //     if (!player.touchingGround){
//         //     player.move(0,3 * movementDelta);
//         //     }
            
//         // }

//         // //press 1 to set time speed to 0.50
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
//         //     printf("tic to .5\n");
//         //     globalTimeline->changeTic(1);

//         // }

//         // //press 2 to set time speed to 1.00
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
//         //     printf("tic to 1\n");
//         //     globalTimeline->changeTic(2);

//         // }

//         // //press 3 to set time speed to 2.00
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
//         //     printf("tic to 2\n");
//         //     globalTimeline->changeTic(4);

//         // }

//         // //press P to pause the game
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            
//         //     //only allow toggling every quarter second (250 ms)
//         //     if (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count() - pausePressDelay >= 500){
//         //         if (!(globalTimeline->isPaused())){
//         //             printf("was unpaused now pausing\n");
//         //             globalTimeline->pause();
//         //             pausePressDelay = std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count();
//         //         }
//         //         else if (globalTimeline->isPaused()){
//         //             printf("was paused now unpausing\n");
//         //             globalTimeline->unpause();
//         //             pausePressDelay = std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count();
//         //         }
//         //     }
            

//         // }

        
//         //commented out screen resize on press of E
//         // if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){

//         //     printf("resizing\n");
//         //     window->close();
//         //     if (windowResize == 1)
//         //     {
//         //         windowResize = 0;
//         //         sf::RenderWindow window(sf::VideoMode(800, 600), "My window that shouldn't scale", sf::Style::None);
//         //         window.setSize(sf::Vector2u(800, 600));
//         //         //limit framerate to 60
//         //         window.setFramerateLimit(60);
//         //         window.setPosition(sf::Vector2i(200, 50));
//         //         // deactivate its OpenGL context
//    	    //         window.setActive(false);
//    	    //         // launch the rendering thread
//    	    //         sf::Thread thread(&renderingThread, &window);
//    	    //         thread.launch();
//         //     }
//         //     else if (windowResize == 0){
//         //         windowResize = 1;
//         //         sf::RenderWindow window(sf::VideoMode(800, 600), "My scalable window :)");
//         //         sf::Style::Default;
//         //         window.setPosition(sf::Vector2i(200, 50));
//         //         //limit framerate to 60
//         //         window.setFramerateLimit(60);
//         //         // deactivate its OpenGL context
//    	    //         window.setActive(false);
//    	    //         // launch the rendering thread
//    	    //         sf::Thread thread(&renderingThread, &window);
//    	    //         thread.launch();
//         //     }
            
//         // }
        

//         //check collision between player and grass
//         // if (PhysicsEngine().collisionCheck(grass, player))
//         // {
//         //     player.isOnGround(true);
//         //     //printf("PLAYER ON GRASS!\n");
//         // }
//         // else {
//         //     //and move player down with gravity if not on ground
//         //     //printf("go touch grass\n");
//         //     player.move(0,1 * movementDelta);
//         // }

//         //put event polling at the end of the loop so if you close the window it won't keep on drawing and stuff
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
            
//         }
        
//         //and finally join threads
        
//     }

//     return 0;
// }






