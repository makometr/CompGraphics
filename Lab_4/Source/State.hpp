#pragma once
#include "libs.hpp"
class AppWindow;
#include "AppWin.hpp"

class State {
private:
    AppWindow *appWinPtr = nullptr;
    GLdouble deep = 1;
    int lenght = 1;
    ElemColor color = ElemColor::random;
    bool badAlloc = false;

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    void callUpdateGraphics();

    int getDeep() const;
    void setDeep(int newDeep);

    int getLength() const;
    void setLength(int newLength);

    // ElemColor getElemColor() const;
    // void setElemColor(ElemColor newColor);
};