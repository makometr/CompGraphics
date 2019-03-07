#pragma once
#include "States.hpp"
#include "libs.hpp"
#include <random>

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
    // std::random_device rd;  //Will be used to obtain a seed for the random number engine
    // std::uniform_real_distribution<> dis;
    // std::mt19937 gen;
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

class LineStripPainter : public IPainter {
private:
public:
    LineStripPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class LineLoopPainter : public IPainter {
private:
public:
    LineLoopPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};