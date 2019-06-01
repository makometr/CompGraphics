#pragma once
#include "libs.hpp"
class AppWindow;
#include "AppWin.hpp"

class State {
private:
    AppWindow *appWinPtr = nullptr;
    GLdouble deep = 0;
    int lenght = 100;
    ElemColor color = ElemColor::random;
    bool badAlloc = false;

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    void callUpdateGraphics();

    void badAllocOn();
    void badAllocOff();
    bool isBadAlloc();

    GLdouble getDeep() const;
    void setDeep(GLdouble newDeep);

    int getLength() const;
    void setLength(int newLength);

    ElemColor getElemColor() const;
    void setElemColor(ElemColor newColor);
};