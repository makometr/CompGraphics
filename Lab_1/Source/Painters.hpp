#pragma once
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