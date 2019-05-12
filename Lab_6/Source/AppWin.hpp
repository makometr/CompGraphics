#pragma once
#include "libs.hpp"
#include "SimpleGL3Window.hpp"
#include "State.hpp"
class State;

class AppWindow : public Fl_Window {
private:
    SimpleGL3Window *glSubWin = nullptr;
    State* statePtr = nullptr;
    std::array<std::vector<Fl_Widget*>, 3> XYZ_widgets;

public:
    AppWindow(int W,int H,const char*L=0);
    void updateGraphicsWindow();

private:
    void initXYZ_widgets(int XYZ_widgets_index, int leftBorder, int leftValue, int rightValue);
    void makeVisibleXYZ_widget(int index);
};

