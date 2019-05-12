#pragma once
#include "libs.hpp"
#include "AppWin.hpp"
class AppWindow;

class State {
private:
    AppWindow *appWinPtr = nullptr;
    ProjectionType proj = ProjectionType::perspective;
    ActionType action = ActionType::translate;
    std::array<GLfloat, 3> translateXYZ = { 0.0f, 0.0f, 0.0f };
    std::array<GLfloat, 3> roatateXYZ = { 0.0f, 0.0f, 0.0f };
    std::array<GLfloat, 3> scaleXYZ = { 0.0f, 0.0f, 0.0f };

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    ProjectionType getProjectionType() const;
    void setProjectionType(ProjectionType newProjectionType);

    ActionType getActionType() const;
    void setActionType(ActionType newActionType);

private:
    void updateGraphics();
};