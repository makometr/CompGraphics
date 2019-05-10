#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new SimpleGL3Window(0, 0, 500, 500);
    glSubWin->end();

    outputText = new Fl_Text_Display(500, 0, 300, 500);
    outputText->buffer(new Fl_Text_Buffer());
}