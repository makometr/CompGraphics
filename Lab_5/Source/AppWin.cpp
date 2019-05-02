#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new SimpleGL3Window(0, 0, 500, 500);
    glSubWin->end();

    outputText = new Fl_Text_Display(500, 0, 300, 480);
    outputText->buffer(new Fl_Text_Buffer());

    Fl_Light_Button *lb = new Fl_Light_Button(500, 480, 300, 20, "Double-Buffered");
    lb->callback([](Fl_Widget *wid, void *data){
        static bool doublebuff = true;
        doublebuff = !doublebuff;
        SimpleGL3Window *glwin = (SimpleGL3Window*)data;
        int flags = glwin->mode();
        if (doublebuff)
            flags |= FL_DOUBLE;
        else
            flags &= ~FL_DOUBLE;
        glwin->mode(flags);
        glwin->reset();
    });
    lb->user_data(this);
    lb->value(1);
}