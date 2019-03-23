#pragma once
#include "libs.hpp"
class State;

class GlSubWin : public Fl_Gl_Window {
private:
    State* statePtr = nullptr;
public:
    GlSubWin(int X,int Y,int W,int H, State* state, const char*L=0);
    virtual ~GlSubWin();

    void drawUpdated();

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING

    void figureCenter(std::vector<glm::vec2> &verteces, int deep, int cur = 0);
    void figureLeft(std::vector<glm::vec2> &verteces, int deep, int cur = 0);
    void figureRight(std::vector<glm::vec2> &verteces, int deep, int cur = 0);
};