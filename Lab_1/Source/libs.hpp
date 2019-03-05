#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/fl_show_colormap.H>
#include <FL/Fl_Button.H>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <memory>

constexpr size_t StatesNumber = 10;

enum class PrimitiveType : int
{
    POINTS         = 0,
    LINES          = 1,
    LINE_STRIP     = 2,
    LINE_LOOP      = 3,
    TRIANGLES      = 4,
    TRIANGLE_STRIP = 5,
    TRIANGLE_FAN   = 6,
    QUADS          = 7,
    QUAD_STRIP     = 8,
    POLYGON        = 9
};

enum class PointPlacement : int {
    circle  = 0,
    rect    = 1,
    normal  = 2,
    uniform = 3
};

enum class LineLength : int {
    small = 0,
    middle = 1,
    large = 2
};

enum class LineColor : int {
    random = 0,
    red = 1,
    green = 2,
    blue = 3,
};