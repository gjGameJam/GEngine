#include "viewBoundBox.hpp"

    // /*
    // getInstance() is a static method that returns an
    // instance when called. It returns the same
    // instance if it is called more than once because the desired
    // functionality of a singleton is for there only to be one
    // */
    // viewBoundBox* viewBoundBox::getInstance(float sizex, float sizey, int xPos, int yPos)
    // {
    // // If there is no instance of class
    // // then we can create an instance.
    // if (instancePtr == nullptr)
    //     {
    //         // We can access private members
    //         // within the class.
    //         instancePtr = new viewBoundBox(sizex, sizey, xPos, yPos);
       
    //     }

    //     // returning the instance pointer
    //     return instancePtr;
    // }


viewBoundBox::viewBoundBox(float sizex, float sizey, int xPos, int yPos) : sf::RectangleShape(sf::Vector2f((sizex + 0.f), (sizey + 0.f))) { 
    setPosition((xPos + 0.f), (yPos + 0.f));
}

void viewBoundBox::shift(float differenceHorizontal, float differenceVertical){
    printf("OK\n");
    move(differenceHorizontal, differenceVertical);
}