#pragma once
#include "libs.hpp"
#include "SimpleGL3Window.hpp"

class AppWindow : public Fl_Window {
private:
    SimpleGL3Window *glSubWin = nullptr;

public:
    AppWindow(int W,int H,const char*L=0);
};

