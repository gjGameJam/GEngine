#include "DeathHandler.hpp"

DeathHandler::DeathHandler(){
    //constructor
}

//on event for death handler will create a spawn event
void DeathHandler::onEvent(Event e){
    for (auto const& variantStruct : e.parameters){
        if (variantStruct.first == "death"){
            printf("death handler heard death event");
        }
    }
}