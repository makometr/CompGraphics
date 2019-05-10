#include "libs.hpp"
#include "SimpleGL3Window.hpp"
#include "AppWin.hpp"

int main(int argc, char **argv) {
    Fl::use_high_res_GL(1);
    AppWindow* topwin = new AppWindow(800, 500, "TEST Learn Open GL");
    topwin->end();
    topwin->show(argc, argv);
    Fl::run();
}

void add_output(const char *format, ...) {
    va_list args;
    char line_buffer[10000];
    va_start(args, format);
    vsnprintf(line_buffer, sizeof(line_buffer)-1, format, args);
    va_end(args);
    outputText->buffer()->append(line_buffer);
    outputText->scroll(10000, 0);
    outputText->redraw();
}