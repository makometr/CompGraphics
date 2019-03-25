#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"
#include "State.hpp"

class GlSubWin;

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;
    Fl_Box* label_error = nullptr;

    State* state = nullptr;

public:
    AppWindow(int W,int H,const char*L=0);

    void update();
    void showBadAllocLabel();

private:
    void boxTextSettings(Fl_Box* box);
};

