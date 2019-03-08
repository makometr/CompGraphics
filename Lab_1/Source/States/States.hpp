#pragma once
#include "../AppWin.hpp"
#include "../libs.hpp"

class AppWindow;

class State {
protected:
    std::vector<Fl_Widget*> widgets;
    size_t parentBoxHeight = 300; // default number, should be rewritten in derived classes
    AppWindow *appWinPtr = nullptr;
    
public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };
    size_t getNeededParentBoxHeight();
    void callUpdateGraphics(bool);
    virtual void hideWidgets();
    virtual void showWidgets();
    virtual const State* getState();
};



class statePoints final : public State {
private:
    size_t pointsNumber = 100;
    PointPlacement placement = PointPlacement::circle;
    Fl_Color bkgColor = FL_GRAY;

public:
    statePoints(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

    void setPlacementType(PointPlacement newType);
    PointPlacement getPlacementType() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;
};



class stateLines final : public State {
private:
    size_t pointsNumber = 50;
    LineLength length = LineLength::small;
    Fl_Color bkgColor = FL_GRAY;
    ElemColor linesColor = ElemColor::random;

public:
    stateLines(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

    void setLength(LineLength newType);
    LineLength getLength() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setElemColor(ElemColor newColor);
    ElemColor getElemColor() const;
};



class stateLineStrips final : public State {
private:
    size_t pointsNumber = 50;
    LineLength length = LineLength::small;
    Fl_Color bkgColor = FL_GRAY;
    ElemColor stripsColor = ElemColor::random;

public:
    stateLineStrips(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

    void setLength(LineLength newType);
    LineLength getLength() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setElemColor(ElemColor newColor);
    ElemColor getElemColor() const;
};



class stateLineLoop final : public State {
private:
    size_t pointsNumber = 50;
    LineLength length = LineLength::small;
    Fl_Color bkgColor = FL_GRAY;
    ElemColor loopColor = ElemColor::random;

public:
    stateLineLoop(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;

    void setLength(LineLength newType);
    LineLength getLength() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setLoopColor(ElemColor newColor);
    ElemColor getLoopColor() const;
};



class stateTriangles final : public State {
private:
    size_t pointsNumber = 9;
    Fl_Color bkgColor = FL_GRAY;
    TripleColors colors;

public:
    stateTriangles(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setTripleColor(TripleColors tripleCol);
    TripleColors getTripleElemColor() const;
};



class stateTriangleStrip final : public State {
private:
    size_t pointsNumber = 9;
    Fl_Color bkgColor = FL_GRAY;
    TripleColors colors;

public:
    stateTriangleStrip(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setTripleColor(TripleColors tripleCol);
    TripleColors getTripleElemColor() const;
};



class stateTriangleFan final : public State {
private:
    size_t pointsNumber = 9;
    Fl_Color bkgColor = FL_GRAY;
    TripleColors colors;

public:
    stateTriangleFan(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setTripleColor(TripleColors tripleCol);
    TripleColors getTripleElemColor() const;
};



class stateQuads final : public State {
private:
    size_t pointsNumber = 40;
    Fl_Color bkgColor = FL_GRAY;
    TetradColors colors;

public:
    stateQuads(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setTetradColor(TetradColors newColor);
    TetradColors getTetradColor() const; 
};


class stateQuadsStrip final : public State {
private:
    size_t pointsNumber = 40;
    Fl_Color bkgColor = FL_GRAY;
    TetradColors colors;

public:
    stateQuadsStrip(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setTetradColor(TetradColors newColor);
    TetradColors getTetradColor() const; 
};


class statePolygon final : public State {
private:
    size_t pointsNumber = 4;
    Fl_Color bkgColor = FL_GRAY;
    ElemColor color = ElemColor::random;

public:
    statePolygon(AppWindow* ptr);

    void setPointsNumber(size_t newNumber);
    size_t getPointsNumber() const;
    
    void setBkgColor(Fl_Color color);
    Fl_Color getBkgColor() const;

    void setElemColor(ElemColor newColor);
    ElemColor getElemColor() const; 
};