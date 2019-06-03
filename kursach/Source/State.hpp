#pragma once
#include "libs.hpp"
#include "AppWin.hpp"
class AppWindow;

class State {
private:
    AppWindow *appWinPtr = nullptr;
    bool isAxesDrawing = false;
    bool isNormalsDrawing = false;
    RGBArray rgbArray {0, 0, 0};

public:
    State(AppWindow* ptr) : appWinPtr(ptr) { };

    bool getIsAxesDrawn() const;
    void setIsAxesDrawn(bool newProjectionType);

    bool getIsNormalsDrawn() const;
    void setIsNormalsDrawn(bool newActionType);

    RGBArray getRGB() const;
    void setRGB(RGBArray newRGB);

private:
    void updateGraphics();
};