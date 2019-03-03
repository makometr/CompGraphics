#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new GlSubWin(10, 10, 500, 500);
    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 300, "Primitive name:");
    box_upper->box(FL_UP_BOX);
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    choice = new Fl_Choice(glSubWin->w() + 40, 37, 180, 25);
    choice->add("GL_POINTS",         "q", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_LINES",          "w", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_LINE_STRIP",     "e", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_LINE_LOOP",      "r", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_TRIANGLES",      "t", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_TRIANGLE_STRIP", "a", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_TRIANGLE_FAN",   "s", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("QUADS",             "d", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_QUAD_STRIP",     "f", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->add("GL_POLYGON",        "g", GlSubWin::setPrimitiveType_CB, (void*)glSubWin);
    choice->value(0);
    

    end();
}