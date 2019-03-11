#include "libs.hpp"
#include "GlSubWin.hpp"
#include "AppWin.hpp"
#include <ctime>

int main() {
    std::srand(std::time(NULL));
    AppWindow win(750, 520, "Computer graphics. Lab 1-2.");
    // win.resizable(win);
    win.show();
    return(Fl::run());
}
  