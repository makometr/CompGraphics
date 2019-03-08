#include "States.hpp"
#include "../AppWin.hpp"

// ----- State ---------------------------------------------------------
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


