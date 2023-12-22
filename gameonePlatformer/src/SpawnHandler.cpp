#include "SpawnHandler.hpp"

SpawnHandler::SpawnHandler(){
    //constructor
}

//on event for spawn handler will move the player to a spawn point
void SpawnHandler::onEvent(Event e){
    for (auto const& variantStruct : e.parameters){
        if (variantStruct.first == "spawn"){
            printf("spawn handler heard spawn event");
        }
    }
}