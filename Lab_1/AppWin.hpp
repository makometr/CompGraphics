#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"
#include "SliderInput.hpp"
#include <vector>

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;
    SliderInput *si = nullptr;

public:
    AppWindow(int W,int H,const char*L=0);

    static void changePrimitive_CB(Fl_Widget* w, void* ptrAppWin);
    void changePrimitive(PrimitiveType type);
};

class State {
protected:
    std::vector<Fl_Widget*> widgets;
    
public:
    // void init() // variadic template constructor
    virtual void hideWidgets();
    virtual void showWidgets();
    virtual const State* getState();
};

class statePoints final : public State {

};

class stateLines final  : public State {

};