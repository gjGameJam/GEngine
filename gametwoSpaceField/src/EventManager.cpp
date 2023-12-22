#include "EventManager.hpp"
#include "InputHandler.hpp"
#include "DeathHandler.hpp"
#include "SpawnHandler.hpp"
#include "CollisionHandler.hpp"
#include "Timeline.hpp"
#include <mutex>
//#include <vector>

//the pointer to the singleton event manager instance
EventManager* EventManager::instancePtr;
//priority queue of events 
std::priority_queue<Event, std::vector<Event>, comparePriority> event_queue;

//mutex for event manager
std::mutex _mutex;
//map of all the handlers
std::map<std::string,std::list<EventHandler *>> handlers;
std::list<EventHandler *> inputHandlerList;
std::list<EventHandler *> deathHandlerList;
std::list<EventHandler *> collisionHandlerList;
std::list<EventHandler *> spawnHandlerList;

InputHandler* inHandler;
SpawnHandler* spwnHandler;
DeathHandler* dthHandler;
CollisionHandler* colHandler;

Timeline *eventManagerTimeline = new Timeline();


    //Private constructor to prevent external instantiation.
    EventManager::EventManager() {
        // Constructor code here.
        //creates input, collision, spawn, and death handlers
        inHandler = new InputHandler();

        //registers event handlers
        registerHandler("input", inHandler);

    }
    /*
    getInstance() is a static method that returns an
    instance when called. It returns the same
    instance if it is called more than once because the desired
    functionality of a singleton is for there only to be one
    */
    EventManager* EventManager::getInstance()
    {
    // If there is no instance of class
    // then we can create an instance.
    if (instancePtr == nullptr)
        {
            // We can access private members
            // within the class.
            instancePtr = new EventManager();
       
        }

        // returning the instance pointer
        return instancePtr;
    }

    bool EventManager::checkForDeathEvent(Character* client, Deathzone* dzone){

        // get the bounding box of the death zone
        sf::FloatRect dzoneBox = dzone->getGlobalBounds();
        // get the bounding box of the client
        sf::FloatRect clientBox = client->getGlobalBounds();

        //check for any intersection
        if (dzoneBox.intersects(clientBox))
        {
            // collision! (death)
            return true;
        }

        return false;
    }

    // bool EventManager::Test(Deathzone* dzone){
    //     return true;
    // }

    //registers 
    // void EventManager::registerHandler(std::forward_list<std::string> list, EventHandler *eHandler){

    // }
    void EventManager::registerHandler(std::string str, EventHandler *eHandler){
        if (str == "input"){
            inputHandlerList.emplace_back(eHandler);
            handlers[str] = inputHandlerList; //This form can/will overwrite existing entry
            return; //reason for return is we only ever want to add one handler at a time
        }
        if (str == "death"){
            deathHandlerList.emplace_back(eHandler);
            handlers[str] = deathHandlerList; //This form can/will overwrite existing entry
            return; //reason for return is we only ever want to add one handler at a time
        }
        if (str == "spawn"){
            spawnHandlerList.emplace_back(eHandler);
            handlers[str] = spawnHandlerList; //This form can/will overwrite existing entry
            return; //reason for return is we only ever want to add one handler at a time
        }
        if (str == "collision"){
            collisionHandlerList.emplace_back(eHandler);
            handlers[str] = collisionHandlerList; //This form can/will overwrite existing entry
            return; //reason for return is we only ever want to add one handler at a time
        }

        //here there could be a new type of event/handler
        

    }

    //deregisters event handler
	void EventManager::deregisterHandler(std::list<std::string> list, EventHandler *eHandler){

    }

    // raises event
	void EventManager::raise(Event newEvent){
        
        //std::unique_lock<std::mutex> cv_lock(*this->_mutex);
        //std::unique_lock<std::mutex> cv_lock(instancePtr->_mutex);
        //std::lock_guard<std::mutex> cv_lock(*this->_mutex);

        //std::lock_guard<std::mutex> lock(_mutex);
        //std::lock_guard<std::mutex> cv_lock(_mutex);    //all mutex locking is currently segfaulting
	    event_queue.push(newEvent);

        //immediate handling
        //std::vector<EventHandler *> Handlers = EventManager.Handlers.get(newEvent.getType);
	    // for(auto h:Handlers){
        //     h->onEvent(e);
        // }
        //printf("event heard by manager %d\n", newEvent.type);
        //input event
        
		
    }

    //update function will use priority queue to determine which event to do
    void EventManager::update(){
        int64_t currentTime = eventManagerTimeline->getTime();
        event_queue.top();
        //check if there is an event that should take place now or before now
        while (!event_queue.empty() && event_queue.top().time <= currentTime){
            //could perform additional check for priority of event here if necessary
            //get the event that needs to happen
            Event newEvent = event_queue.top();
            printf("%d event update due to time\n", newEvent.type);
            event_queue.pop(); //and pop event off of priority queue
            //then handle event logic
            if (newEvent.type == newEvent.EVENT_TYPE_INPUT){
            //inHandler->onEvent(newEvent);
            Character* player = newEvent.triggerPlayer;
            for (auto idVariantPair : newEvent.parameters){
                if (idVariantPair.first == "input"){ //if the first is "input"
                    //then the second is the input int array
                    // int inputArray[7];
                    
                    
                    //std::copy(inputArray, inputArray + 7, idVariantPair.second);
                    int *inputArray = idVariantPair.second.Vunion.inputArray;
                    if (inputArray[0] == 1){
                        //left
                        //printf("LEFT input raise event\n");
                        newEvent.triggerPlayer->move(-2 * newEvent.deltaTime,0);
                        //player.move()
                    }
                    if (inputArray[1] == 1){
                        //right
                        //printf("RIGHT input raise event\n");
                        newEvent.triggerPlayer->move(2 * newEvent.deltaTime,0);
                    }
                    if (inputArray[2] == 1){
                        //up
                        //printf("UP input raise event\n");
                        newEvent.triggerPlayer->move(0,-3 * newEvent.deltaTime);
                    }
                    if (inputArray[3] == 1){
                        //time1
                        printf("time1 input raise event\n");
                        //newEvent.tline
                        newEvent.tline->changeTic(1);
                    }
                    if (inputArray[4] == 1){
                        //time2
                        printf("time2 input raise event\n");
                        newEvent.tline->changeTic(2);
                    }
                    if (inputArray[5] == 1){
                        //time3
                        printf("time3 input raise event\n");
                        newEvent.tline->changeTic(4);
                    }
                    if (inputArray[6] == 1){
                        //pause
                        printf("pause input raise event\n");
                        if (!(newEvent.tline->isPaused())){
                            printf("was unpaused now pausing\n");
                            newEvent.tline->pause();
                        }
                        else if (newEvent.tline->isPaused()){
                            printf("was paused now unpausing\n");
                            newEvent.tline->unpause();
                        }
                    }


                    //and finally free heap allocated input array
                    delete(inputArray);
                    //free(inputArray);

                }
            }
        }
        //collision event
        else if (newEvent.type == newEvent.EVENT_TYPE_COLLISION){
            //printf("collision raise event\n");
            if (newEvent.death){ //collided with death box (create death event)
                //create and raise death event
                //create map of variants to define death event
                std::map<std::string, variant> deathMap;
                //create variant for death event
                variant deathVariant = {variant::TYPE_SPAWNPOINT, 1};
                //set the union's data in variant to hold the position of the spawn point
                for (auto idVariantPair : newEvent.parameters){
                    if (idVariantPair.first == "collision"){ //if the first is "input"
                        deathVariant.Vunion.spoint = idVariantPair.second.Vunion.spoint;
                    }
                }
                //insert the input variant into the map of variants
                deathMap.insert(std::pair<std::string, variant>("death", deathVariant));
                //construct event
                Event deathEvent = Event(deathMap, 0); //second param is delay (which we don't want for input events)
                //set the type and trigger player
                deathEvent.type = deathEvent.EVENT_TYPE_DEATH;
                deathEvent.triggerPlayer = newEvent.triggerPlayer;
                //then raise event
                raise(deathEvent);

            }
            else{ //collided with something other than death box
                newEvent.triggerPlayer->isOnGround(true);
                newEvent.triggerPlayer->setGroundedTime(eventManagerTimeline->getTime());
            }

        }
        //death event
        else if (newEvent.type == newEvent.EVENT_TYPE_DEATH){
            //printf("death raise event\n");
            //death event creates and raises spawn event
            // for (auto idVariantPair : newEvent.parameters){
            // }
            //create map of variants to define event
            std::map<std::string, variant> spawnMap;
            //create variant for input
            variant spawnVariant = {variant::TYPE_SPAWNPOINT, 1};
            //set the union's data in variant to hold the desired spawn point
            for (auto idVariantPair : newEvent.parameters){
                if (idVariantPair.first == "death"){ //if the first is "death"
                    spawnVariant.Vunion.spoint = idVariantPair.second.Vunion.spoint; //second will be spawn point
                }
            }
            //insert the input variant into the map of variants
            spawnMap.insert(std::pair<std::string, variant>("spawn", spawnVariant));
            //construct event
            Event spawnEvent = Event(spawnMap, 0); //second param is delay (which we don't want for input events)
            //set the type and trigger player
            spawnEvent.type = spawnEvent.EVENT_TYPE_SPAWN;
            spawnEvent.triggerPlayer = newEvent.triggerPlayer;
            //then raise event
            //printf("raise input event\n");
            raise(spawnEvent);

        }
        //spawn event
        else if (newEvent.type == newEvent.EVENT_TYPE_SPAWN){
            //printf("spawn raise event\n");
            //spawns the player at a spawnpoint
            for (auto idVariantPair : newEvent.parameters){
                if (idVariantPair.first == "spawn"){ //if the first is "spawn"
                    idVariantPair.second.Vunion.spoint->respawnClient(newEvent.triggerPlayer); //respawn player at spawn point
                }
            }
        }
        }

        //pop events off of event queue until time of event in queue is yet to pass
        //event_queue.pop();

    }