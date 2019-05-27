#pragma once
#include "libs.hpp"
#include "AppWin.hpp"
class AppWindow;

class State {
private:
    AppWindow *appWinPtr = nullptr;
    ProjectionType proj = ProjectionType::perspective;
    ActionType action = ActionType::translate;
    std::array<std::array<GLfloat, 3>, 3> XYZ =
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
        // Translate        // Rotate         // Scale

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    ProjectionType getProjectionType() const;
    void setProjectionType(ProjectionType newProjectionType);

    ActionType getActionType() const;
    void setActionType(ActionType newActionType);

    XYZArray getXYZ(ActionType actionType) const;
    void setXYZ(XYZArray newXYZ, ActionType actionType);

private:
    void updateGraphics();
};