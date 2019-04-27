#include "libs.hpp"
#include "SimpleGL3Window.hpp"

void add_output(const char *format, ...);


void toggle_double(Fl_Widget *wid, void *data) {
    static bool doublebuff = true;
    doublebuff = !doublebuff;
    SimpleGL3Window *glwin = (SimpleGL3Window*)data;
    int flags = glwin->mode();
    if (doublebuff) flags |= FL_DOUBLE; else flags &= ~FL_DOUBLE;
    glwin->mode(flags);
    glwin->reset();
}


Fl_Text_Display *output; // shared between output_win() and add_output()

void output_win(SimpleGL3Window *gl) {
    output = new Fl_Text_Display(300,0,500, 280);
    Fl_Light_Button *lb = new Fl_Light_Button(300, 280, 500, 20, "Double-Buffered");
    lb->callback(toggle_double);
    lb->user_data(gl);
    lb->value(1);
    output->buffer(new Fl_Text_Buffer());
}


void add_output(const char *format, ...) {
    va_list args;
    char line_buffer[10000];
    va_start(args, format);
    vsnprintf(line_buffer, sizeof(line_buffer)-1, format, args);
    va_end(args);
    output->buffer()->append(line_buffer);
    output->scroll(10000, 0);
    output->redraw();
}


int main(int argc, char **argv) {
    Fl::use_high_res_GL(1);
    Fl_Window *topwin = new Fl_Window(800, 300);
    SimpleGL3Window *win = new SimpleGL3Window(0, 0, 300, 300);
    win->end();
    output_win(win);
    topwin->end();
    topwin->resizable(win);
    topwin->label("Click GL panel to reshape");
    topwin->show(argc, argv);
    Fl::run();
}