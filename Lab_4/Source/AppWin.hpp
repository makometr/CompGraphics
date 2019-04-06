#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"
#include "State.hpp"

class GlSubWin;

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Box *box_upper = nullptr;
    State* state = nullptr;
    Fl_Value_Slider* widgetX;
    Fl_Value_Slider* widgetY;

public:
    AppWindow(int W,int H,const char*L=0);
    void updateXY(Coord curCoord);
    void update();
    void makeVisiblePointWidgets(size_t pointNum);

private:
    void boxTextSettings(Fl_Box* box);
};

