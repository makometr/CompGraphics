#pragma once
#include "States/States.hpp"
#include "libs.hpp"
#include <random>

class State;

class IPainter {
public:
    IPainter() = default;
    virtual ~IPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) = 0;
protected:
    static RGB Fl_Color_To_RGB(Fl_Color color);
    static void applyColor(ElemColor color, double alpha = 1.00);
};

class PointPainter : public IPainter {
public:
    PointPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class LinePainter : public IPainter {
public:
    LinePainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class LineStripPainter : public IPainter {
public:
    LineStripPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class LineLoopPainter : public IPainter {
public:
    LineLoopPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class TrianglesPainter : public IPainter {
public:
    TrianglesPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class TriangleStripPainter : public IPainter {
public:
    TriangleStripPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class TriangleFanPainter : public IPainter {
public:
    TriangleFanPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class QuadsPainter : public IPainter {
public:
    QuadsPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class QuadStripPainter : public IPainter {
public:
    QuadStripPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class PolygonPainter : public IPainter {
public:
    PolygonPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class ScissorPainter : public IPainter {
public:
    ScissorPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class AlphaPainter : public IPainter {
public:
    AlphaPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};

class BlendPainter : public IPainter {
public:
    BlendPainter() = default;
    virtual void operator()(State* statePtr, int winWidth, int winHeight, bool redraw) override;
};