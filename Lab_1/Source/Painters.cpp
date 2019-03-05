#include "Painters.hpp"

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