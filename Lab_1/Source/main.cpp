#include "libs.hpp"
#include "GlSubWin.hpp"
#include "AppWin.hpp"

int main() {
    AppWindow win(750, 520, "OpenGL Test App");
    win.resizable(win);
    win.show();
    return(Fl::run());
}
  