#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H, State* state, const char*L)
    : Fl_Gl_Window(X,Y,W,H,L), statePtr(state)
{
    end();
    // primitives
}

GlSubWin::~GlSubWin(){
}

void GlSubWin::FixViewport(int W,int H) {
    glViewport(0,0,W,H);
    glOrtho(0,W,0,H,-1,1);
}

void GlSubWin::draw() {
    if (!valid()){ // first time? init
        valid(1);
        FixViewport(w(), h());
    }
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_LINES);
    //     glVertex2d(0,0);
    //     glVertex2d(500,500);
    //     glVertex2d(500, 0);
    //     glVertex2d(0,500);
    // glEnd();

    // int i1 = 3;
    // DrawFractal(100, 1,250, 250, 250, 250, 2, i1);

    glPolygonMode(GL_FRONT, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLdouble triangleVertices[] = {
        0,  150,
        -100,  -50,
        100,  -50
    };
    glVertexPointer(2, GL_DOUBLE, 0, (void*)triangleVertices);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslated(250, 250, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(250, 250, 0);
        glTranslated(0, 150*2/3, 0);
        glScaled(1.0/3, 1.0/3, 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(250, 250, 0);
        glTranslated(-150/3, 150/3 , 0);
        glScaled(1.0/3, 1,1);
        glRotatef(90, 0.0f, 0.0f, 1.0f);
        // glRotatef(statePtr->getAngle(), 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(250, 250, 0);
        glTranslated(150/3, 150/3 , 0);
        glScaled(1.0/3, 1,1);
        glRotatef(-90, 0.0f, 0.0f, 1.0f);
        // glRotatef(statePtr->getAngle(), 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);

}

void GlSubWin::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    redraw();
}

void GlSubWin::Fractal(){

}

void GlSubWin::drawUpdated(){
    redraw();
}