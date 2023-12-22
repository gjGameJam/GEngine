#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(){
    //constructor
}

//on event for collision handler will restrict player movement depending on parameters
void CollisionHandler::onEvent(Event e){
    for (auto const& variantStruct : e.parameters){
        if (variantStruct.first == "collision"){
            printf("collision handler heard collision event");
        }
    }
}