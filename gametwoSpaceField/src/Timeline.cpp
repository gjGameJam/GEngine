#include <mutex>
#include <chrono>
#include <ctime>

#include "Timeline.hpp"

//  private:
//    std::mutex m; //if tics can change size and the game is multithreaded
//    int64_t start_time; //the time of the *anchor when created
//    int64_t elapsed_paused_time;
//    int64_t last_paused_time;
//    int64_t tic; //units of anchor timeline per step
//    bool paused;
//    Timeline *anchor; //for most general game time, system library pointer

  //public:
   //Timeline(Timeline *anchor, int64_t tic);
   //Timeline(); //optional, may not be included

   //Needs to use mutex for all of these below
//    int64_t getTime(); //this can be game or system time implementation
//    void pause();
//    void unpause();
//    void changeTic(int tic);
//    bool isPaused();


//create timeline anchored on other timeline with desired tic size
Timeline::Timeline(Timeline *anchor, int64_t tic) : anchor(anchor), tic(tic), paused(false), start_time(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()), elapsed_paused_time(0), last_paused_time(0)
{
}

//default timeline constructor
Timeline::Timeline() : anchor(nullptr), tic(2), paused(false), start_time(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()), elapsed_paused_time(0), last_paused_time(0)
{
}


    //returns the time as a int64_t
    int64_t Timeline::getTime(){
        //use game time in milliseconds since epoch (1970)
        //Needs to use mutex for this?
        if (paused){
            return last_paused_time;
        }
        else if (anchor != nullptr){
            return anchor->getTime();
        }
            //here it is not paused and an anchor timeline exists
            // Citation: This  below call for milliseconds since epoch is based on code from: https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
        return (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count() * tic);
        
        
        
    }

   void Timeline::pause(){
    //Needs to use mutex for this
    //m.lock();
    this->paused = true;
    //milliseconds since epoch * tic
    this->last_paused_time = std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::system_clock::now()).time_since_epoch()).count() * tic;;
    //m.unlock();

   }

   
   
   

   void Timeline::unpause(){
    //Needs to use mutex for this?

    this->paused = false;

    //When you pause, you have to subtract the amount of time spent paused (in milliseconds)
    this->elapsed_paused_time = getTime() - last_paused_time;

    //In units of anchor timeline before dividing by tic
    //anchor. - elapsed_paused_time;

    //and in units of this timeline after dividing by tic size
    int64_t ticChange = elapsed_paused_time / tic;
    //anchor. - ticChange;

    //then unlock mutex? (that was locked in pause)
    //m.unlock();
   }


   bool Timeline::isPaused(){
    //Needs to use mutex for this
    return paused;
   }

   void Timeline::changeTic(int tic){
    //Needs to use mutex for this?
    this->tic = tic;
   }

   int Timeline::getTic(){
    //Needs to use mutex for this?
    return tic;
   }
