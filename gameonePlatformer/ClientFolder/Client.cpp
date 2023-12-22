#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include "../src/GameManager.hpp"
#include "../src/EventManager.hpp"


zmq::context_t context (1);
//want request, reply, and subscibe sockets
zmq::socket_t clientRequest (context, zmq::socket_type::req);
zmq::socket_t clientSubscribe (context, zmq::socket_type::sub);
//initialize client id to be 0 in order for server to determine it is a new client
char clientId = 0;
//each client has a window
sf::RenderWindow window(sf::VideoMode(800, 600), "Client Window");
//each client also has their own view
sf::View view;
int serverPauseEvent = 0;

// struct PlayerPositionStruct{
//     int playerID;
//     float xPosition;
//     float yPosition;
// };

class ThreadExample
{
    bool busy; // a member variable used to indicate thread "status"
    int i; // an identifier
    ThreadExample *other; // a reference to the "other" thread in this example
    std::mutex *_mutex; // the object for mutual exclusion of execution
    std::condition_variable *_condition_variable; // for messaging between threads
    //  each player has a gamemanager
    GameManager *gameManager;

    public:
        ThreadExample(int i, ThreadExample *other, std::mutex *_mutex, std::condition_variable *_condition_variable, GameManager *_gameManager)
        {
            this->i = i; // set the id of this thread
            if(i==0) { busy = true; }
            else { this->other = other; }
            this->_mutex = _mutex;
            this->_condition_variable = _condition_variable;
            this->gameManager = _gameManager;
        }

        bool isBusy()
        {
            // this locks the mutuex until the variable goes out of scope (i.e., when the function returns in this case)
            std::lock_guard<std::mutex> lock(*_mutex);
            return busy;
        }

        void run()
        {
            if(i==0)
            {
                //thread zero functions here
                //client only needs to pass input to server
                try
                {
                    zmq::message_t request (5);
                    //std::cout << "clientRequestReplyLoop" << std::endl;
                    //want to send client id to server so convert it to string
                    //std::cout << "clientIDNumber:" << clientId << std::endl;
                    int idToUse = clientId;// - '0';// - 48;
                    //std::cout << "IDNumberToUse:" << idToUse << std::endl;
                    std::string clientString = std::to_string(idToUse);
                    //std::cout << "clientIDString:" << clientString << std::endl;
                    //so client id should be 0 if new
                    if (clientId <= 0){
                        clientRequest.send (zmq::buffer(clientString), zmq::send_flags::none);
                    }
                    else{
                        //std::string publishString = std::to_string(clientId - 48);
                        //add comma to seperate data
                        clientString.append(",");
                        //the client only needs to send their position, it should handle all graphics and everything
                        //else with the help of gamemanager
                        sf::Vector2f PlayerPosition = gameManager->getPlayerPosition();
                        //float playerXPosition = PlayerPosition.x;
                        //float playerYPosition = PlayerPosition.y;
                        std::string xPosString = std::to_string(PlayerPosition.x);
                        std::string yPosString = std::to_string(PlayerPosition.y);
                        //std::cout << "Player X:" << xPosString << "Player Y:" << yPosString << std::endl;
                        //add the x and y position to string to send to server
                        clientString.append(xPosString);
                        clientString.append(",");
                        clientString.append(yPosString);
                        clientString.append(",");
                        clientString.append(std::to_string(serverPauseEvent));
                        clientString.append(",");
                        serverPauseEvent = 0;
                        //each client sends their id and position to the server
                        clientRequest.send (zmq::buffer(clientString), zmq::send_flags::none);
                        //std::cout << "ClientReqString: " << clientString << std::endl;
                    }
                    

                    //  Get the reply.
                    zmq::message_t reply;
                    clientRequest.recv (reply, zmq::recv_flags::none);
                    int server2client = std::stoi(reply.to_string());
                    //update the client's id number from the server response
                    clientId = server2client;
                    //std::cout << "clientIdFromServer" << server2client << std::endl;

                    busy = !busy; //indicate no longer busy
                    _condition_variable->notify_all(); //and notify all
                    


                //     //  Send reply of client id back to client
                //     zmq::message_t reply (5);
                //     //the id of the player passed back (now not -1)
                //     std::string serverString = std::to_string(playerId);
                //     serverReply.send (zmq::buffer(serverString), zmq::send_flags::none);
                //     //sleep(1);
                    //std::cout << "Thread " << i << " is FINISHED!\n" << std::endl;
                }
                catch (...)
                {
                    std::cerr << "Thread " << i << " caught exception." << std::endl;
                }
            }
            else // id == 1
            {
                //changed from while loop in order to not overincremment the iterations
                while(other->isBusy())
                {
                    //std::cout << "Thread " << i << " is waiting!" << std::endl;
                    try 
                    {
                        
                        //  Get the published string(s) of clientID,Xpos,Ypos,
                        zmq::message_t published;
                        //receive the publisher that the client should be subscribed to
                        clientSubscribe.recv(published, zmq::recv_flags::none); //right now only receiving client 1
                        //this message will contain client id and locations
                        std::string outputString = published.to_string();
                        //iteration number from server is delayed (increasingly from most recent client to first client)
                        //std::cout << "Serv2ClientSubReceived: " << outputString << std::endl;

                        int idToUse = clientId;
                        //parses strings from server to represent all clients (up to three)
                        int numOfClients = 0;
                        int player1Index = 0;
                        float player1XPosition = 0;
                        float player1YPosition = 0;
                        int player2Index = 0;
                        float player2XPosition = 0;
                        float player2YPosition = 0;
                        int player3Index = 0;
                        float player3XPosition = 0;
                        float player3YPosition = 0;
                        int player4Index = 0;
                        float player4XPosition = 0;
                        float player4YPosition = 0;
                        int movingPlatform1XPos;
                        //int movingPlatform2YPos;
                        //TODO: need to scan more according to number of clients
                        sscanf(outputString.c_str(), "%d,%d,%d,%f,%f,%d,%f,%f,%d,%f,%f,%d,%f,%f,", &numOfClients, &movingPlatform1XPos, &player1Index, &player1XPosition, &player1YPosition, &player2Index, &player2XPosition, &player2YPosition, &player3Index, &player3XPosition, &player3YPosition, &player4Index, &player4XPosition, &player4YPosition);
                        //iteration++;
                        // std::cout << "ClientSubscribe(#Clients,ID,X,Y): " << numOfClients << "," << player1Index << "," << player1XPosition << "," << player1YPosition
                        // << ",P2:" << player2Index << "," << player2XPosition<< "," << player2YPosition
                        // << ",P3:" << player3Index << "," << player3XPosition<< "," << player3YPosition
                        // << ",P4:" << player4Index << "," << player4XPosition<< "," << player4YPosition << std::endl;
                        
                        //sleep(1);
                        //only allow client to do stuff once they join server
                        //std::cout << "clientId: " << idToUse << std::endl;
                        //gameManager->allPlayersUpdate(&window, numOfClients, idToUse, player1Index, player1XPosition, player1YPosition, player2Index, player2XPosition, player2YPosition, player3Index, player3XPosition, player3YPosition);
                        // if (player1Index && player1Index != 0 && player1Index != idToUse){
                        //     //so this should update other clients on this client's window when render world objects is called
                        //     std::cout << "OPTION1" << std::endl;
                        //     gameManager->otherPlayerUpdate(player1Index, player1XPosition, player1YPosition);
                        // }
                        // if (player2Index && player2Index != 0 && player2Index != idToUse){
                        //     //so this should update other clients on this client's window when render world objects is called
                        //     std::cout << "OPTION2" << std::endl;
                        //     gameManager->otherPlayerUpdate(player2Index, player2XPosition, player2YPosition);
                        // }
                        // if (player3Index && player3Index != 0 && player3Index != idToUse){
                        //     //so this should update other clients on this client's window when render world objects is called
                        //     std::cout << "OPTION3" << std::endl;
                        //     gameManager->otherPlayerUpdate(player3Index, player3XPosition, player3YPosition);
                        // }
                        //other clients info should be in game manager

                        if (idToUse > 0){
                            
                            //NO LONGER USING STRUCT
                            //PlayerPositionStruct data2send;
                            //data2send.playerID = clientId;
                            //data2send.xPosition = PlayerPosition.x;
                            //data2send.yPosition = PlayerPosition.y;
                            //now serialize struct to turn it into string

                            gameManager->updateMovingPlatforms(movingPlatform1XPos);
                            //timeline was intialized in startup function
                            //updates internal time variables in game manager
                            gameManager->timeCalculations();

                            //side scroll if player touches side
                            gameManager->sidescrollIfNeeded(&view, &window);

                            //then render the objects based on elapsed time
                            gameManager->renderWorldObjects(&window, numOfClients, idToUse, player1Index, player1XPosition, player1YPosition, player2Index, player2XPosition, player2YPosition, player3Index, player3XPosition, player3YPosition, player4Index, player4XPosition, player4YPosition);

                            //and make events from player input (relies on time calculations)
                            //takes input if window is focused and returns true if client paused
                            if (gameManager->takeInput(&window)){
                                printf("pauseEventClientNumUpdate\n");
                                serverPauseEvent = clientId;
                            }
                        }
                        
                        busy = !busy; //indicate no longer busy
                        _condition_variable->notify_all(); //and notify all
                    }
                    catch (...)
                    {
                        std::cerr << "Thread " << i << " caught exception." << std::endl;
                    }
                }
                //std::cout << "Thread " << i << " is FINISHED!\n" << std::endl;
            }
        }

};

/**
 * Wrapper function because threads can't take pointers to member functions.
 */
void run_wrapper(ThreadExample *fe)
{
    fe->run();
}

//main function for client that will handle all player actions and communication with server
int main ()
{
    // create a view with its center (first vector) and size (second vector) in order to side scroll
    //sf::View view(sf::Vector2f(400.f, 300.f), sf::Vector2f(800.f, 600.f));
    //set the size and center of the player view
    //view.setCenter(sf::Vector2f(400.f, 300.f));
    //view.setSize(sf::Vector2f(800.f, 600.f));
    //then set the window to the view
    view = window.getView();
    window.setView(view);
    
    //then bind them different ports
    clientRequest.connect ("tcp://localhost:5556"); //connects client request to server reply
    clientSubscribe.setsockopt(ZMQ_CONFLATE, 1);
    clientSubscribe.connect ("tcp://localhost:4201");  //connects client subscribe to server publish
    clientSubscribe.setsockopt(ZMQ_SUBSCRIBE, "", strlen(""));
    // Mutex to handle locking, condition variable to handle notifications between threads
    std::mutex m;
    std::condition_variable cv;

    //creates the singleton instance of GameManager
    GameManager* gameManager = GameManager::getInstance();
    //sets up window properties and intializes timeline
    gameManager->startUp(&window);

    while (true){

        // Create thread objects
        ThreadExample t1(0, NULL, &m, &cv, gameManager);  //thread for all static objects
        ThreadExample t2(1, &t1, &m, &cv, gameManager);   //thread for all dynamic objects

        // Start threads
        std::thread first(run_wrapper, &t1);
        std::thread second(run_wrapper, &t2);

        // Make sure both threads are complete before stopping main thread
        //std::cout << "thread-one-join" << std::endl;
        first.join();
        //std::cout << "thread-two-join" << std::endl;
        second.join();
        //std::cout << "THREAD-DONE" << std::endl;


        //put event polling at the end of the loop so if you close the window it won't keep on drawing and stuff
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std::cout << "END CALL" << std::endl;
                zmq::message_t request (5);
                std::string clientExitString = std::to_string(-1 * clientId);
                clientRequest.send (zmq::buffer(clientExitString), zmq::send_flags::none);
                // get the reply from server
                zmq::message_t reply;
                clientRequest.recv (reply, zmq::recv_flags::none);
                return 0;
            }
            
        }
        //end of main loop
    }


    return 0;
}
