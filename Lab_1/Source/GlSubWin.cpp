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
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA); // OPACITY MODE

    // glBegin(GL_QUADS);
    //     glColor4f(1.0f,0.0f,1.0f, 0.6f);
    //     glVertex2f(left,bottom);
    //     glColor4f(0.0f,1.0f,0.0f, 0.6f);
    //     // glColor3ub(0,255,0);
    //     glVertex2f(left,top);
    //     glColor4f(1.0f,1.0f,0.0f, 0.6f);
    //     glVertex2f(right,top);
    //     glColor4f(0.0f,0.0f,1.0f, 0.6f);
    //     glVertex2f(right,bottom);
    // glEnd();
    // glBegin(GL_QUADS);
    //     glColor4f(1.0f,0.0f,1.0f, 0.6f);
    //     glVertex2f(20,30);
    //     glColor4f(0.0f,1.0f,0.0f, 0.6f);
    //     // glColor3ub(0,255,0);
    //     glVertex2f(20,40);
    //     glColor4f(1.0f,1.0f,0.0f, 0.6f);
    //     glVertex2f(40,40);
    //     glColor4f(0.0f,0.0f,1.0f, 0.6f);
    //     glVertex2f(40,30);
    // glEnd();
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

void GlSubWin::setPrimitiveType(PrimitiveType type){
    this->type = type;
    // call func to draw
}

void GlSubWin::drawPrimitive(PrimitiveType newType, State* state, bool isRegenerate){
    if ((int)type != (int)newType) isRegenerate = true;
    type = newType;
    curStatePtr = state;
    redraw();
}

void GlSubWin::draw_POINTS(const State* const state, bool isRegenerate){
    std::cout << "Draw: point" << (int)type << "\n";
}

void GlSubWin::draw_LINES(const State* const state, bool isRegenerate){
    std::cout << "Draw: lines" << (int)type << "\n";
}






void PointPainter::operator()(State* statePtr, bool redraw){
    std::cout << "Draw point (gl func)\n";
}

void LinePainter::operator()(State* statePtr, bool redraw){
    std::cout << "Draw line (gl func)\n";

    glBegin(GL_QUADS);
        glColor4f(1.0f,0.0f,1.0f, 0.6f);
        glVertex2f(20,30);
        glColor4f(0.0f,1.0f,0.0f, 0.6f);
        // glColor3ub(0,255,0);
        glVertex2f(20,40);
        glColor4f(1.0f,1.0f,0.0f, 0.6f);
        glVertex2f(40,40);
        glColor4f(0.0f,0.0f,1.0f, 0.6f);
        glVertex2f(40,30);
    glEnd();
}