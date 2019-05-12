#include "libs.hpp"
#include "SimpleGL3Window.hpp"
#include "AppWin.hpp"

int main(int argc, char **argv) {
    Fl::use_high_res_GL(1);
    AppWindow* topwin = new AppWindow(850, 600, "TEST Learn Open GL");
    topwin->end();
    topwin->show(argc, argv);
    Fl::run();
}