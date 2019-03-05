#pragma once
#include "GlSubWin.hpp"
#include "libs.hpp"
#include "States.hpp"

class IPainter {
private:
    // vars
public:
    IPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) = 0;
};

class PointPainter : public IPainter {
private:
public:
    PointPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class LinePainter : public IPainter {
private:
public:
    LinePainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class GlSubWin : public Fl_Gl_Window {
private:
    std::vector<IPainter*> painters;
    PrimitiveType type = PrimitiveType::POINTS;
    State* curStatePtr = nullptr;
    bool shouldRedraw = false;

public:
    GlSubWin(int X,int Y,int W,int H,const char*L=0);

    void setPrimitiveType(PrimitiveType type);
    void drawPrimitive(PrimitiveType type, State* state, bool isRegenerate = false);

private:
    void FixViewport(int W,int H);// FIX OPENGL VIEWPORT Do this on init or when window's size is changed
    void draw(); // DRAW METHOD
    void resize(int X,int Y,int W,int H);// HANDLE WINDOW RESIZING

    void draw_POINTS(const State* const state, bool isRegenerate = false);
    void draw_LINES(const State* const state, bool isRegenerate = false);
};