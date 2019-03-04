#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"
#include "SliderInput.hpp"
#include <vector>
#include <memory>

class State {
protected:
    std::vector<Fl_Widget*> widgets;
    
public:
    State() = default;
    virtual void hideWidgets();
    virtual void showWidgets();
    virtual const State* getState();
};

class statePoints final : public State {
private:
public:
    statePoints() : State() {
        auto si_pointsNumber = new SliderInput(500 + 40, 100, 180, 25, "Points number:");
        si_pointsNumber->bounds(1, 1000);
        si_pointsNumber->value(50);
        widgets.push_back(si_pointsNumber);

        auto choice_placamentType = new Fl_Choice(500 + 40, 140, 180, 25, "Размещение:");
        choice_placamentType->add("Saas");
        widgets.push_back(choice_placamentType);
    }

};

class stateLines final  : public State {
private:

public:
    stateLines() : State() {
        auto si_pointsNumber = new SliderInput(500 + 40, 100, 180, 25, "Lines number:");
        si_pointsNumber->bounds(1, 1000);
        si_pointsNumber->value(50);
        widgets.push_back(si_pointsNumber);
    }

};

class AppWindow : public Fl_Window {
private:
    GlSubWin *glSubWin = nullptr;
    Fl_Choice *choice = nullptr;
    Fl_Box *box_upper = nullptr;

    PrimitiveType currentType = PrimitiveType::POINTS;
    std::vector<std::unique_ptr<State>> primitiveTypeStates;

public:
    AppWindow(int W,int H,const char*L=0);

    static void changePrimitive_CB(Fl_Widget* w, void* ptrAppWin);
    void changePrimitive(PrimitiveType type);

private:
    void makeCurrentWidgetsInvisiable();
    void setCurrentPrimitiveType(PrimitiveType type);
    void makeCurrentWidgetsVisiable();
};

