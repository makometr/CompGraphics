#include "State.hpp"

State::State(AppWindow* ptr) : appWinPtr(ptr){
    points.reserve(numOfPoints);
    for (int i = 0; i < numOfPoints; i++)
        points.push_back({100,100});
};

void State::callUpdateGraphics(){
    appWinPtr->update();
}

int State::getCurrPoint() const{
    return currentPoint;
}

void State::setCurrPoint(int newPoint){
    currentPoint = newPoint;
    appWinPtr->updateXY(points.at(currentPoint));
}

GLdouble State::getCurrPoint_X() const {
    return points.at(currentPoint).first;
}

void State::setCurrPoint_X(GLdouble newX) {
    points.at(currentPoint).first = newX;
    // todo update graphics in x and y
}   


GLdouble State::getCurrPoint_Y() const {
    return points.at(currentPoint).second;
}

void State::setCurrPoint_Y(GLdouble newY) {
    points.at(currentPoint).second = newY;
}


// ElemColor State::getElemColor() const {
//     return color;
// }

// void State::setElemColor(ElemColor newColor) {
//     color = newColor;
// }
