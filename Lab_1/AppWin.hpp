#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"
#include "SliderInput.hpp"
#include <vector>

class State {
protected:
    std::vector<Fl_Widget*> widgets;
    
public:
    State(){
        //  do nothing;
    }

    template <typename T, typename... Args>
    State(T ptr, Args... other){
        widgets.push_back(ptr);
        State(other...);
    }
    virtual void hideWidgets();
    virtual void showWidgets();
    virtual const State* getState();
};

class statePoints final : public State {

};

class stateLines final  : public State {

};

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;

    SliderInput *si_pointsNumber_1 = nullptr;

    SliderInput *si_pointsNumber_2 = nullptr;

    PrimitiveType currentType = PrimitiveType::POINTS;
    std::vector<State> primitiveTypeStates;

public:
    AppWindow(int W,int H,const char*L=0);

    static void changePrimitive_CB(Fl_Widget* w, void* ptrAppWin);
    void changePrimitive(PrimitiveType type);

private:
    void makeCurrentWidgetsInvisiable();
    void setCurrentPrimitiveType(PrimitiveType type);
    void makeCurrentWidgetsVisiable();
};

