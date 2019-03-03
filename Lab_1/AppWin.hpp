#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;

public:
    AppWindow(int W,int H,const char*L=0);
    
    static void changePrimitive_CB(Fl_Widget* w, void* ptrAppWin);
    void changePrimitive(PrimitiveType type);
};