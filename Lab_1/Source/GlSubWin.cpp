#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H,const char*L)
    : Fl_Gl_Window(X,Y,W,H,L)
{
    end();
    painters.push_back(new PointPainter{});
    painters.push_back(new LinePainter{});
    // TODO push other painters
    std::cout << "W: " << w() << "\n";
    std::cout << "H: " << h() << "\n";
}

void GlSubWin::FixViewport(int W,int H) {
    glLoadIdentity();
    glViewport(0,0,W,H);
    std::cout << W << " " << H << std::endl;
    glOrtho(0,W,0,H,-1,1);
}

void GlSubWin::draw() {
    if (!valid()){ // first time? init
        valid(1);
        FixViewport(w(), h());
    }

    int left, right, top, bottom;
    // GLint Width = 512, Height = 512;
    int CubeSize = 100;
    left  = (w() - CubeSize) / 2;
    right = left + CubeSize;
    bottom = (h() - CubeSize) / 2;
    top = bottom + CubeSize;

    glClearColor(0, 0, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_QUADS, GL_POINT);

    

    painters.at(static_cast<int>(type))->operator()(curStatePtr, shouldRedraw);
    
    // glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_LESS, 0.81);

    // glEnable(GL_SCISSOR_TEST);
    // glScissor(0, 0, w()/2+50, h()/2+50);
    // glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // glEnable(GL_BLEND);
    glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
        glVertex2f(left,top);
        glVertex2f(right+10,top+10);
        glVertex2f(right,bottom);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
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