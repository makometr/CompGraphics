#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"

class AppWindow : public Fl_Window {
public:
    AppWindow(int W,int H,const char*L=0);
private:
    GlSubWin *glSubWin = nullptr;
};