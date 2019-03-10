#include "States.hpp"
#include "../AppWin.hpp"

bool State::isScissorTest = false;
bool State::isAlphaTest = false;
bool State::isBlendTest = false;

void State::hideWidgets(){
    for (auto &widget : widgets)
        widget->hide();
}

void State::callUpdateGraphics(bool regenerate){
    appWinPtr->update(regenerate);
}

void State::showWidgets(){
    for (auto &widget : widgets)
        widget->show();
}

const State* State::getState(){
    return this;
}

size_t State::getNeededParentBoxHeight(){
    return parentBoxHeight;
}

bool State::isScissorTestEnabled() {
    return isScissorTest;
}

void State::setScissorTest(bool isNew){
    isScissorTest = isNew;
}

bool State::isAlphaTestEnabled() {
    return isAlphaTest;
}

void State::setAlphaTest(bool isNew){
    isAlphaTest = isNew;
}

bool State::isBlendTestEnabled() {
    return isBlendTest;
}

void State::setBlendTest(bool isNew){
    isBlendTest = isNew;
}
