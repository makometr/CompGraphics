#include "States.hpp"

stateTriangles::stateTriangles(AppWindow* ptr) : State(ptr) {
    
}

void stateTriangles::setPointsNumber(size_t newNumber){
    pointsNumber = newNumber;
}

void stateTriangles::setLength(LineLength newLength){
    length = newLength;
}

void stateTriangles::setBkgColor(Fl_Color color){
    bkgColor = color;
}

void stateTriangles::setElemColor(ElemColor color_1, ElemColor color_2, ElemColor color_3){

}
    
void stateTriangles::setElemColor(TripleColors tripleCol){
}


size_t stateTriangles::getPointsNumber() const {
    return pointsNumber;
}

LineLength stateTriangles::getLength() const {
    return length;
}

Fl_Color stateTriangles::getBkgColor() const {
    return bkgColor;
}

ElemColor stateTriangles::getElemColor() const {
}
