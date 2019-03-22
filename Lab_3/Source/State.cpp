#include "State.hpp"

void State::callUpdateGraphics(){
    appWinPtr->update();
}

GLdouble State::getAngle() const { 
    return angle;
}

void State::setAngle(GLdouble newAngle){
    angle = newAngle;
}