#pragma once
#include <stdarg.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#define GLEW_STATIC 1
#include <GL/glew.h>


inline Fl_Text_Display *outputText = nullptr; // shared between output_win() and add_output()

void add_output(const char *format, ...);