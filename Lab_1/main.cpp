#include "libs.hpp" 

int main() {
    Fl_Gl_Window win(500, 300, "OpenGL Test App");
    win.resizable(win);
    win.show();
    return(Fl::run());
}
  