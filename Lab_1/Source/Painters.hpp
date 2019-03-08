#pragma once
#include "States/States.hpp"
#include "libs.hpp"
#include <random>

class State;

class IPainter {
private:
    // vars
public:
    IPainter() = default;
    virtual ~IPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) = 0;
protected:
    static RGB Fl_Color_To_RGB(Fl_Color color);
    static void applyColor(ElemColor color);
    static int getSignVertex(Coord c_1, Coord c_2, Coord c_3);
    static bool isConvex(const std::vector<Coord> &array);
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
public:
    LinePainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class LineStripPainter : public IPainter {
public:
    LineStripPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class LineLoopPainter : public IPainter {
public:
    LineLoopPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class TrianglesPainter : public IPainter {
public:
    TrianglesPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class TriangleStripPainter : public IPainter {
public:
    TriangleStripPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class TriangleFanPainter : public IPainter {
public:
    TriangleFanPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class QuadsPainter : public IPainter {
public:
    QuadsPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class QuadStripPainter : public IPainter {
public:
    QuadStripPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};

class PolygonPainter : public IPainter {
public:
    PolygonPainter() = default;
    virtual void operator()(State* statePtr, bool redraw) override;
};