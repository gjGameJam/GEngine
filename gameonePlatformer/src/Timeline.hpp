#pragma once
#ifndef TIMELINE_HPP
#define TIMELINE_HPP
#include <mutex>
//#include "Timeline.cpp"


class Timeline {
  private:
   std::mutex m; //if tics can change size and the game is multithreaded
   int64_t start_time; //the time of the *anchor when created
   int64_t elapsed_paused_time;
   int64_t last_paused_time;
   int64_t tic; //units of anchor timeline per step
   bool paused;
   Timeline *anchor; //for most general game time, system library pointer

  public:
   Timeline(Timeline *anchor, int64_t tic);
   Timeline(); //optional, may not be included
   

   //Needs to use mutex for all of these below
   int64_t getTime(); //this can be game or system time implementation
   void pause();
   void unpause();
   void changeTic(int tic);
   int getTic();
   bool isPaused();
};

#endif