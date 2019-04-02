#pragma once
#include "libs.hpp"

class GlSubWin : public Fl_Gl_Window {
private:

public:
    GlSubWin(int X,int Y,int W,int H,const char*L=0);
    virtual ~GlSubWin();

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING
};