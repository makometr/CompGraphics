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
    // virtual size_t getNeededParentBoxHeight();
};



class statePoints final : public State {
private:
    size_t pointsNumber = 100;
    PointPlacement placement = PointPlacement::circle;
    Fl_Color bkgColor = FL_GRAY;

public:
    statePoints();

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

    void setPlacementType(PointPlacement newType);
    PointPlacement getPlacementType() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;


private:
    static void callColorChooser_CB(Fl_Widget* w, void* data);
    // static 
};

class stateLines final  : public State {
private:

public:
    stateLines();
};