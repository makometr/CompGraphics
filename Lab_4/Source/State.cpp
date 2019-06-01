#include "State.hpp"

void State::callUpdateGraphics(){
    appWinPtr->update();
}

void State::badAllocOn(){
    appWinPtr->showBadAllocLabel();
    badAlloc = true;
}

void State::badAllocOff(){
    badAlloc = false; 
}

bool State::isBadAlloc(){
    return badAlloc;
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
