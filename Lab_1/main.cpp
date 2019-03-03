#include "libs.hpp"
#include "AppWin.hpp"
#include "GlSubWin.hpp"

int main() {
    AppWindow win(500, 300, "OpenGL Test App");
    win.resizable(win);
    win.show();
    return(Fl::run());
}
  