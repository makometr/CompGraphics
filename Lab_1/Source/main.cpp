#include "libs.hpp"
#include "GlSubWin.hpp"
#include "AppWin.hpp"
#include <ctime>

int main() {
    std::srand(std::time(NULL));
    AppWindow win(750, 520, "OpenGL Test App");
    win.resizable(win);
    win.show();
    return(Fl::run());
}
  