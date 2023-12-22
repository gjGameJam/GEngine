#pragma once
#ifndef VIEWBOUNDBOX_HPP
#define VIEWBOUNDBOX_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class viewBoundBox : public sf::RectangleShape
{
    public:
        //static viewBoundBox* getInstance(float sizex, float sizey, int xPos, int yPos);
        
        viewBoundBox(float sizex, float sizey, int xPos, int yPos);

        void shift(float differenceHorizontal, float differenceVertical);

    // private:
    
     
    // // static pointer which will points
    // //to the instance of this class
    // static viewBoundBox* instancePtr;


};

#endif