#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H,const char*L)
    : Fl_Gl_Window(X,Y,W,H,L)
{
    end();
    painters.reserve(PrimitivesNumber);
    painters.push_back(new PointPainter{});
    painters.push_back(new LinePainter{});
    painters.push_back(new LineStripPainter{});
    painters.push_back(new LineLoopPainter{});
    painters.push_back(new TrianglesPainter{});
    painters.push_back(new TriangleStripPainter{});
    painters.push_back(new TriangleFanPainter{});
    painters.push_back(new QuadsPainter{});
    painters.push_back(new QuadStripPainter{});
    painters.push_back(new PolygonPainter{});
}

GlSubWin::~GlSubWin(){
    for (auto &painter : painters)
        delete painter;
}

void GlSubWin::FixViewport(int W,int H) {
    glLoadIdentity();
    glViewport(0,0,W,H);
    glOrtho(0,W,0,H,-1,1);
}

void GlSubWin::draw() {
    if (!valid()){ // first time? init
        valid(1);
        FixViewport(w(), h());
    }
    glPolygonMode(GL_QUADS, GL_POINT);
    State::isScissorTestEnabled() ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
    State::isAlphaTestEnabled() ? glEnable(GL_ALPHA_TEST) : glDisable(GL_ALPHA_TEST);
    State::isBlendTestEnabled() ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    painters.at(static_cast<int>(type))->operator()(curStatePtr, w(), h(), shouldRedraw);
}

void GlSubWin::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    redraw();
}

void GlSubWin::drawPrimitive(PrimitiveType newType, State* state, bool isRegenerate){
    if ((int)type != (int)newType) isRegenerate = true;
    type = newType;
    curStatePtr = state;
    redraw();
}