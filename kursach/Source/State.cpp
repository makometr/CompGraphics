#include "State.hpp"

void State::updateGraphics(){
    appWinPtr->updateGraphicsWindow();
}

bool State::getIsAxesDrawn() const {
    return isAxesDrawing;
}

void State::setIsAxesDrawn(bool newBool) {
    isAxesDrawing = newBool;
    updateGraphics();
}

bool State::getIsNormalsDrawn() const {
    return isNormalsDrawing;
}

void State::setIsNormalsDrawn(bool newBool){
    isNormalsDrawing = newBool;
    updateGraphics();
}

RGBArray State::getRGB() const {
    return rgbArray;
}

void State::setRGB(RGBArray newRGB){
    rgbArray = newRGB;
    updateGraphics();
}