#pragma once
#include "States.hpp"
#include "libs.hpp"

class State;

class IPainter {
private:
    // vars
public:
    IPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) = 0;
protected:
    static RGB Fl_Color_To_RGB(Fl_Color color);
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