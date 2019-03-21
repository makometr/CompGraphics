#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new GlSubWin(10, 10, 500, 500);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 300, "Primitive name:");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);
}