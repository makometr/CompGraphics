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
#include <assert.h>

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