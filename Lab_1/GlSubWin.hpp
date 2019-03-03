#pragma once
#include "libs.hpp"

class GlSubWin : public Fl_Gl_Window {
private:
    int CubeSize = 200;

public:
    GlSubWin(int X,int Y,int W,int H,const char*L=0);

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING
};