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
    std::vector<Coord> points;
    int currentPoint = 0;

public:
    State(AppWindow* ptr);
    void callUpdateGraphics();

    int getCurrPoint() const;
    void setCurrPoint(int curPoint);

    GLdouble getCurrPoint_X() const;
    void setCurrPoint_X(GLdouble newCoord);

    GLdouble getCurrPoint_Y() const;
    void setCurrPoint_Y(GLdouble newCoord);

    // int getDeep() const;
    // void setDeep(int newDeep);

    // int getLength() const;
    // void setLength(int newLength);

    // ElemColor getElemColor() const;
    // void setElemColor(ElemColor newColor);
};