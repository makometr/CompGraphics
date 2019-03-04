#pragma once
#include "libs.hpp"
#include "SliderInput.hpp"

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
    statePoints();
};

class stateLines final  : public State {
private:

public:
    stateLines();
};