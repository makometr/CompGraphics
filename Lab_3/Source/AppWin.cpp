#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    state = new State(this);
    glSubWin = new GlSubWin(10, 10, 500, 500, state);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 300, "Primitive name:");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);


    // numbers
    auto label_number = new Fl_Box(500 + 30, 70, 200, 30, "Количество точек:");
    label_number->box(FL_NO_BOX);
    label_number->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number->labelsize(16);
    // +
    auto slider_number = new Fl_Value_Slider(500 + 40, 90, 180, 25);
    slider_number->step((int)1);
    slider_number->align(FL_ALIGN_LEFT);
    slider_number->type(FL_HOR_SLIDER);
    slider_number->bounds(0, 360);
    slider_number->value(0);
    slider_number->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setAngle((GLdouble)ch->value());
        state->callUpdateGraphics();
    }, (void*)state);
}

void AppWindow::update(){
    glSubWin->drawUpdated();
}