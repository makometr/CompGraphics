#pragma once
#include "GlSubWin.hpp"
#include "libs.hpp"
#include "States.hpp"
#include "Painters.hpp"

class GlSubWin : public Fl_Gl_Window {
private:
    std::vector<IPainter*> painters;
    PrimitiveType type = PrimitiveType::POINTS;
    State* curStatePtr = nullptr;
    bool shouldRedraw = false;

public:
    GlSubWin(int X,int Y,int W,int H,const char*L=0);
    void drawPrimitive(PrimitiveType type, State* state, bool isRegenerate = false);

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING
};