#pragma once
#include "libs.hpp"
#include "SimpleGL3Window.hpp"
#include "State.hpp"
class State;

class AppWindow : public Fl_Window {
    struct callbackXYZInfo {
        State* statePtr;
        bool action;
        int coordinateNumber;
        callbackXYZInfo(State* ptr, bool act, int num)
        : statePtr(ptr), action(act), coordinateNumber(num){ };
    };
private:
    SimpleGL3Window *glSubWin = nullptr;
    std::unique_ptr<State> statePtr;

public:
    AppWindow(int W,int H,const char*L=0);
    ~AppWindow() override = default;
    void updateGraphicsWindow();
};

