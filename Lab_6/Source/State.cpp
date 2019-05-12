#include "State.hpp"

void State::updateGraphics(){
    appWinPtr->updateGraphicsWindow();
}

ProjectionType State::getProjectionType() const {
    return proj;
}

void State::setProjectionType(ProjectionType newProj) {
    proj = newProj;
    updateGraphics();
}

ActionType State::getActionType() const {
    return action;
}

void State::setActionType(ActionType newActionType){
    action = newActionType;
    updateGraphics();
}
