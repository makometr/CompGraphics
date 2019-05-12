#pragma once
#include <stdarg.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <array>
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Slider.H>
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <Gl/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SOIL/SOIL.h"

enum class ProjectionType : int {
    perspective = 0,
    orthogonal = 1, 
};

enum class ActionType : int {
    translate = 0,
    rotate = 1,
    scale = 2,
};