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
    appWinPtr->makeVisibleActionWidgets(newActionType);
}

XYZArray State::getXYZ(ActionType action) const {
    return XYZ.at(static_cast<int>(action));
}

void State::setXYZ(XYZArray newXYZ, ActionType action){
    XYZ.at(static_cast<int>(action)) = newXYZ;
    updateGraphics();
}
