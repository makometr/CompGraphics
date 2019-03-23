#include "State.hpp"

void State::callUpdateGraphics(){
    appWinPtr->update();
}

void State::badAllocTrigger(){
    std::cout << "Bad alloc!\n";
}

GLdouble State::getDeep() const { 
    return deep;
}

void State::setDeep(GLdouble newDeep){
    deep = newDeep;
}

int State::getLength() const {
    return lenght;
}

void State::setLength(int newLength) {
    lenght = newLength;
}


ElemColor State::getElemColor() const {
    return color;
}

void State::setElemColor(ElemColor newColor) {
    color = newColor;
}
