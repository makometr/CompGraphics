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
enum class PointPlacement : int {
    circle = 0,
    rect = 1,
    normal = 2,
    uniform = 3
};
private:
    PointPlacement placement;
    Fl_Color bkgColor = FL_GRAY;
    size_t pointsNumber = 1;

public:
    statePoints();

    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;
    
    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

private:
    static void callColorChooser_CB(Fl_Widget* w, void* data);
    // static 
};

class stateLines final  : public State {
private:

public:
    stateLines();
};