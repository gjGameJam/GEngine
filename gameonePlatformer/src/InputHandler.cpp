#include "InputHandler.hpp"

InputHandler::InputHandler(){
    //constructor
}

//on event for input handler will read the input bool array and determine what to do
void InputHandler::onEvent(Event e){
    for (auto const& variantStruct : e.parameters){
        if (variantStruct.first == "input"){
            printf("input handler heard input");
        }
    }
}