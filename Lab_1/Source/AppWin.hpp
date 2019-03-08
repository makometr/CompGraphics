#pragma once
#include "libs.hpp"
#include "GlSubWin.hpp"

class GlSubWin;
#include "States/States.hpp"
class State;

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
    void update(bool regenerate);

private:
    void makeCurrentWidgetsInvisiable();
    void setCurrentPrimitiveType(PrimitiveType type);
    void makeCurrentWidgetsVisiable();
};

