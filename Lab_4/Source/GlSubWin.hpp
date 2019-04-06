#pragma once
#include "libs.hpp"
class State;

class GlSubWin : public Fl_Gl_Window {
private:
    State* statePtr = nullptr;
    size_t p = 3; // Spline basis function degree
    size_t n = 7; // Control points
    size_t m = n+p+1;//13; // Knots
    // size_t k = 3;
    double* U;
    const size_t pointsNum = m*10;
    glm::vec2* controlPoints;
    // double* points;

public:
    GlSubWin(int X,int Y,int W,int H, State* state, const char*L=0);
    virtual ~GlSubWin();
    void drawUpdated();

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING

    float N(int i, int p, double u);
    glm::vec2 C(int p, double u);
};