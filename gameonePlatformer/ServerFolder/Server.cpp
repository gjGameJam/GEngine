//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "../src/Timeline.hpp"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>


#define sleep(n)	Sleep(n)
#endif

//  Prepare our context and sockets
zmq::context_t context (2);
//needs reply (works both ways) and publish sockets
zmq::socket_t serverReply (context, zmq::socket_type::rep);
zmq::socket_t serverPublisher (context, zmq::socket_type::pub);
//key is player id value is position vector for player
std::map<int, std::vector<float>> playerPositionMap;
//and timeline content
Timeline* serverTimeline;
//keeps track of when player with playerID last sent to server
std::map<int, int64_t> playerTimeMap;
int numberOfPlayers = 0;
bool platform1OscilateBool = true;
int platformXPos = 225;

// struct PlayerPositionStruct{
//     float xPosition;
//     float yPosition;
// };

std::string PlatformOscilate(int posx1, int posx2, float speed){
    //if too far left go right
    // sf::Vector2f vec = getPosition();
    //std::string platformString = "platforms:";
    // //moving right to start with
    if (platform1OscilateBool)
    {
        //vec = getPosition();
        if (platformXPos >= posx2)
        {
            platform1OscilateBool = false;
        }
        //printf("right: %f   %d\n", vec.x, posx1);
        //move((speed + 0.f), (0.f));
        platformXPos += speed;
    }
    // //if too far right go left
    else if (!platform1OscilateBool)
    {
        //vec = getPosition();
        if (platformXPos <= posx1)
        {
            platform1OscilateBool = true;
        }
        //printf("left: %f   %d\n", vec.x, posx1);
        //move(-(speed + 0.f), (0.f));
        platformXPos -= speed;
    }

    std::string xposString = std::to_string(platformXPos);
    //platformString.append(xposString);

    
    return xposString;

}

class ThreadExample
{
    bool busy; // a member variable used to indicate thread "status"
    int i; // an identifier
    ThreadExample *other; // a reference to the "other" thread in this example
    std::mutex *_mutex; // the object for mutual exclusion of execution
    std::condition_variable *_condition_variable; // for messaging between threads
    std::map<int, std::vector<float>> *_pPosnMap; //player id and position map
    std::map<int, int64_t> *_pTimeMap;

    public:
        ThreadExample(int i, ThreadExample *other, std::mutex *_mutex, std::condition_variable *_condition_variable, std::map<int, std::vector<float>> *_playerPosMap, std::map<int, int64_t> *_playerTimeMap)
        {
            this->i = i; // set the id of this thread
            if(i==0) { busy = true; }
            else { this->other = other; }
            this->_mutex = _mutex;
            this->_condition_variable = _condition_variable;
            this->_pPosnMap = _playerPosMap;
            this->_pTimeMap = _playerTimeMap;
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
                //objective to get/set client ids correctly and receive player locations to insert/remove from map
                try
                {
                    //currently having issue where _pPosnMap/playerPositionMap is being accessed by loop mid deletion
                    while (true){
                    //mutex (or unique mutex?) lock map here so it can't be accessed before fully modified?


                    zmq::message_t request;
                    //  Wait for next request from client (Id, xpos, ypos)
                    zmq::recv_result_t idvalid = serverReply.recv (request, zmq::recv_flags::none); //might use dontwait
                    std::string client2Server = request.to_string();
                    //std::cout << "Received client id: " + client2Server<< std::endl;
                    int playerId;
                    float playerXPos;
                    float playerYPos;
                    int clientPauseNumber;
                    sscanf(client2Server.c_str(), "%d,%f,%f,%d,", &playerId, &playerXPos, &playerYPos, &clientPauseNumber);
                    if (clientPauseNumber != 0){
                        printf("client %d is changing pause state\n", clientPauseNumber);
                    }
                    
                    
                    //int64_t currTime = serverTimeline->getTime();

                    //now for the position storage
                    //if client id is 0 assign them an id one greater than the last one assigned
                    playerId = std::stoi(client2Server);
                    if (playerId == 0){ //id of zero indicates a new client joining
                        //set the player id to the number of players after preincrementing and set the iteration number to 1
                        playerId = ++numberOfPlayers;
                        //might need to remove from player time map if client with the same id already disconnected

                    }
                    if (playerId > 0){ //existing client
                        //update position with client2server string if client has non zero id
                        std::vector<float> playerPositionVector; //creates vector
                        playerPositionVector.push_back(playerXPos); //push xpos
                        playerPositionVector.push_back(playerYPos); //push ypos
                        (*_pPosnMap)[playerId] = playerPositionVector;
                        //also add to time map for timeouts
                        //add client to timeout map based on time of received message
                        (*_pTimeMap)[playerId] = serverTimeline->getTime();

                    }
                    else if (playerId < 0){ //existing client leaving (sends negative id via window close event)
                        int idOfClientLeaving = -1 * playerId; //the playerId will be a negative version of the id in the map
                        //(*_pTimeMap)[playerId] = 0; //considering letting timeout handle this by setting client heard from time to 0
                        std::cout << "Client " << idOfClientLeaving << " is exiting" << std::endl;
                        numberOfPlayers--; //decrement number of players
                        //need to clear player from maps upon disconnect
                        
                        { // anonymous inner block to manage scop of mutex lock 
                            std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                            //_mutex->lock();
                            _pPosnMap->erase(_pPosnMap->find(idOfClientLeaving)); //iterates to and erase client from player position map
                            _pTimeMap->erase(_pTimeMap->find(idOfClientLeaving)); //iterates to and erase client from player time map
                            //_mutex->unlock();
                        }
                        //iterate through all elements of player position map for viewing only
                        for (auto const& IdPositionPair : (*_pPosnMap)){
                            //start with client id
                            std::string publishString = std::to_string(IdPositionPair.first);
                            publishString += ","; //separate via commas
                            //adds x position float
                            publishString += std::to_string(IdPositionPair.second[0]);
                            publishString += ","; //separate via commas
                            //should now be "#,X," when # is client id and X is the X position of associated client
                            //adds y position float
                            publishString += std::to_string(IdPositionPair.second[1]);
                            publishString += ","; //separate via commas
                            //should now be "#,X,Y," when # is client id and X/Y are the X and Y positions of associated client
                            std::cout << "PlayerMapContent:" << publishString << std::endl;
                        }
                        //player with idOfClientLeaving should be removed from map (shouldn't be seen in PlayerMapContent)
                    }

                    //  Send reply of client id back to client
                    zmq::message_t reply (5);
                    //the id of the player passed back (now not 0)
                    std::string serverString = std::to_string(playerId);
                    serverReply.send (zmq::buffer(serverString), zmq::send_flags::none);
                    std::cout << "ServerRepString: " << serverString << std::endl;

                    //then unlock (don't want map to be accessed mid delete)
                    //busy = !busy; //indicate no longer busy
                    //_condition_variable->notify_all(); //and notify all

                    }//end of while loop
                    

                    //std::cout << "Thread " << i << " is FINISHED!\n" << std::endl;
                }
                catch (...)
                {
                    std::cerr << "Thread " << i << " caught exception." << std::endl;
                }
            }
            if (i == 1)
            {
                while(true)
                {
                    //objective is to check for client timeouts (caused by any type of disconnect)
                    //removes the clients if they haven't sent a response to the server in 3000ms
                    try 
                    {
                        //check timeout every one second
                        sleep(1);
                        int64_t currTime = serverTimeline->getTime();
                        std::cout << "CurrTime: " << currTime << std::endl;
                        //check if current time is (timeout duration) away from last time server heard from client
                        //loop through player time map
                        for (auto const& IdPositionPair : (*_pTimeMap)){ //likely going to have same issue where ptimemap could erase elemnt during iteration in other thread
                            int idOfClientTimingOut = IdPositionPair.first; //client of id checked for timing out
                            if (idOfClientTimingOut == 0){ //don't know how id of 0 is being added
                                return;
                            }
                            int64_t lastHeardClientTime = IdPositionPair.second; //time in ms last that client last talked to server
                            //check if current time is 3000ms (3 seconds) ahead of lastHeardClientTime
                            if (currTime - lastHeardClientTime >= 3000){
                                std::cout << "idOfClientTimingOut: " << idOfClientTimingOut << std::endl;
                                //erase client(s) from all maps if timed out
                                { // anonymous inner block to manage scop of mutex lock 
                                    std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                                    _pPosnMap->erase(_pPosnMap->find(idOfClientTimingOut)); //iterates to and erase client from player position map
                                    _pTimeMap->erase(_pTimeMap->find(idOfClientTimingOut)); //iterates to and erase client from player time map
                                }

                                numberOfPlayers--; //decrement number of players
                                break; //break out of for loop
                            }


                        }
                        


                        //busy = !busy; //indicate no longer busy
                        //_condition_variable->notify_all(); //and notify all
                    }
                    catch (...)
                    {
                        std::cerr << "Thread " << i << " caught exception." << std::endl;
                    }
                }
                //std::cout << "Thread " << i << " is FINISHED!\n" << std::endl;
                //so thread one just finished
            }
            // id == 2
            if (i == 2)
            {
                std::string oscilateString = PlatformOscilate(225, 550, 1);
                int iterationNumber = 0;
                while (true){
                    //std::cout << "ThreadTHREE" << std::endl;
                    if (iterationNumber % 170 == 0){
                        oscilateString = PlatformOscilate(225, 550, 1);
                        // oscilateString += ",";
                        // oscilateString = PlatformOscilate(150, 400, 1);
                        //std::cout << "oscilateString: " << oscilateString << std::endl;
                    }
                    int numberOfActiveClients = 0;
                    std::string publishString;
                    //segfault happening in below loop due to accessing element as it is removed even though the map should be mutexed?
                    { // anonymous inner block to manage scop of mutex lock 
                    std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                        for (auto const& IdPositionPair : *_pPosnMap){
                            //std::cout << "Start" << std::endl;
                            //start with client id
                            //auto playerIdAndPosition = IdPositionPair;
                            publishString += std::to_string(IdPositionPair.first); //adds the key (the client id)
                            //std::cout << "ids:" << publishString << std::endl;
                            //should now be "#" when # is client id
                            publishString += ","; //separate via commas
                            //adds x position float
                            publishString += std::to_string(IdPositionPair.second[0]); //vector is being deleted before accessing
                            publishString += ","; //separate via commas
                            //should now be "#,X," when # is client id and X is the X position of associated client
                            //adds y position float
                            publishString += std::to_string(IdPositionPair.second[1]);
                            publishString += ","; //separate via commas
                            //should now be "#,X,Y," when # is client id and X/Y are the X and Y positions of associated client
                            numberOfActiveClients++;
                            //std::cout << "Finish" << std::endl;
                            
                        }
                    }
                    if (numberOfActiveClients > 0){
                        //forms full string of numberofclients,(all clients info)
                        std::string fullPublishString = std::to_string(numberOfActiveClients);
                        fullPublishString.append(",");
                        //NO LONGER CHECKING ITERATIONS, CLIENTS ARE SYNCED
                        //check iterations
                        iterationNumber++;
                        std::string iterationNumberString = std::to_string(iterationNumber);
                        //NO LONGER CHECKING ITERATIONS, CLIENTS ARE SYNCED
                        fullPublishString.append(oscilateString);
                        fullPublishString.append(",");
                        fullPublishString.append(publishString);

                        //std::cout << "fullPubMessage:" << fullPublishString << std::endl;
                        //string is currently: numberofclients,(all clients info seperated by commas)

                        serverPublisher.send(zmq::buffer(fullPublishString), zmq::send_flags::none);
                    }
                }
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



int main () {

    // Mutex to handle locking, condition variable to handle notifications between threads
    std::mutex m;
    std::condition_variable cv;

    serverTimeline = new Timeline();   //intitialize serverTimeline as a Timeline object

    //binds sockets to different ports to communicate with clients
    serverReply.bind ("tcp://*:5556");
    serverPublisher.bind("tcp://*:4201");
    // Create thread objects
    ThreadExample t1(0, NULL, &m, &cv, &playerPositionMap, &playerTimeMap);  //adding new clients/updating old ones via req-rep
    ThreadExample t2(1, &t1, &m, &cv, &playerPositionMap, &playerTimeMap);   //thread for timing out clients
    ThreadExample t3(2, NULL, &m, &cv, &playerPositionMap, &playerTimeMap);  //publishing to all clients

    // Start threads
    std::thread first(run_wrapper, &t1);
    //first.detach();//run separately
    std::thread second(run_wrapper, &t2);
    //second.detach();//run separately
    std::thread third(run_wrapper, &t3);

    // Make sure both threads are complete before stopping main thread
    //std::cout << "thread-one-join" << std::endl;
    //first.join();
    //std::cout << "thread-two-join" << std::endl;
    //second.join();
    //std::cout << "THREAD-DONE" << std::endl;
    //std::string oscilateString = PlatformOscilate(225, 550, 1);
    //int iterationNumber = 0;
    while (true) {
        //std::cout << "ServerLoop" << std::endl;
        // if (iterationNumber % 170 == 0){
        //     oscilateString = PlatformOscilate(225, 550, 1);
        //     //TODO: add to oscilate string for vertical moving platform
        //     // oscilateString += ",";
        //     // oscilateString = PlatformOscilate(150, 400, 1);
        //     //std::cout << "oscilateString: " << oscilateString << std::endl;
        // }

        // int numberOfActiveClients = 0;
        // std::string publishString;
        // //segfault happening in below loop due to accessing element as it is removed even though the map should be mutexed?
        // for (auto const& IdPositionPair : playerPositionMap){
        //     std::cout << "Start" << std::endl;
        //     //start with client id
        //     //auto playerIdAndPosition = IdPositionPair;
        //     publishString += std::to_string(IdPositionPair.first); //adds the key (the client id)
        //     //std::cout << "ids:" << publishString << std::endl;
        //     //should now be "#" when # is client id
        //     publishString += ","; //separate via commas
        //     //adds x position float
        //     publishString += std::to_string(IdPositionPair.second[0]); //vector is being deleted before accessing
        //     publishString += ","; //separate via commas
        //     //should now be "#,X," when # is client id and X is the X position of associated client
        //     //adds y position float
        //     publishString += std::to_string(IdPositionPair.second[1]);
        //     publishString += ","; //separate via commas
        //     //should now be "#,X,Y," when # is client id and X/Y are the X and Y positions of associated client
        //     numberOfActiveClients++;
        //     std::cout << "Finish" << std::endl;
            
            
        // }
        // if (numberOfActiveClients > 0){
        //     //forms full string of numberofclients,(all clients info)
        //     std::string fullPublishString = std::to_string(numberOfActiveClients);
        //     fullPublishString.append(",");
        //     //NO LONGER CHECKING ITERATIONS, CLIENTS ARE SYNCED
        //     //check iterations
        //     iterationNumber++;
        //     std::string iterationNumberString = std::to_string(iterationNumber);
        //     //NO LONGER CHECKING ITERATIONS, CLIENTS ARE SYNCED
        //     fullPublishString.append(oscilateString);
        //     fullPublishString.append(",");
        //     fullPublishString.append(publishString);

        //     //std::cout << "fullPubMessage:" << fullPublishString << std::endl;
        //     //string is currently: numberofclients,(all clients info seperated by commas)

        //     //need to add info for platform(s)
        //     //TODO: add platform info and parse/display in client
        //     serverPublisher.send(zmq::buffer(fullPublishString), zmq::send_flags::none);
        // }
        
    } //end of while server loop
    return 0;
}