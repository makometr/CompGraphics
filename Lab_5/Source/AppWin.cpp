#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new SimpleGL3Window(0, 0, 300, 300);
    glSubWin->end();
}