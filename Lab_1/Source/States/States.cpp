#include "States.hpp"
#include "../AppWin.hpp"

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

bool State::isScissorTestEnabled() const {
    return isScissorTest;
}

bool State::setScissorTest(bool isNew){
    isScissorTest = isNew;
}

bool State::isAlphaTestEnabled() const {
    return isAlphaTest;
}

bool State::setAlphaTest(bool isNew){
    isAlphaTest = isNew;
}

bool State::isBlendTestEnabled() const {
    return isBlendTest;
}

bool State::setBlendTest(bool isNew){
    isBlendTest = isNew;
}
