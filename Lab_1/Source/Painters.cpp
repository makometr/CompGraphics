#include "Painters.hpp"

void PointPainter::operator()(State* statePtr, bool redraw){
    statePoints* state = dynamic_cast<statePoints*>(statePtr);
    assert(state != nullptr);

    auto color = state->getBkgColor();
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    std:: cout << "Color: "  << r << " " << g << " " << b << " " << color << "\n";
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void LinePainter::operator()(State* statePtr, bool redraw){
    stateLines* state = dynamic_cast<stateLines*>(statePtr);
    assert(state != nullptr);

    auto color = state->getBkgColor();
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    std:: cout << "Colorbb: "  << r << " " << g << " " << b << " " << color << "\n";
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

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