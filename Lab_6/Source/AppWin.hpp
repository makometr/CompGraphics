#pragma once
#include "libs.hpp"
#include "SimpleGL3Window.hpp"
#include "State.hpp"
class State;

class AppWindow : public Fl_Window {
    struct callbackXYZInfo {
        State* statePtr;
        ActionType action;
        int coordinateNumber;
        callbackXYZInfo(State* ptr, ActionType act, int num)
        : statePtr(ptr), action(act), coordinateNumber(num){ };
    };
private:
    SimpleGL3Window *glSubWin = nullptr;
    std::unique_ptr<State> statePtr;
    std::array<std::vector<Fl_Widget*>, 3> XYZ_widgets;
    std::vector<callbackXYZInfo*> callbackData;

public:
    AppWindow(int W,int H,const char*L=0);
    ~AppWindow() override = default;
    void updateGraphicsWindow();
    void makeVisibleActionWidgets(ActionType type);

private:
    void initXYZ_widgets(ActionType type, int leftBorder, int leftValue, int rightValue);
    void makeVisibleXYZ_widget(int index);
};

