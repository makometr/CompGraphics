#pragma once
#include "libs.hpp"
class AppWindow;
#include "AppWin.hpp"

class State {
private:
    AppWindow *appWinPtr = nullptr;
    GLdouble angle = 0;

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    GLdouble getAngle() const;
    void callUpdateGraphics();

    void setAngle(GLdouble newAngle);
};