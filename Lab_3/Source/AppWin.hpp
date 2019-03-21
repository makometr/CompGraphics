#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"

class GlSubWin;

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;

public:
    AppWindow(int W,int H,const char*L=0);

private:
};

