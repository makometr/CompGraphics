#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    statePtr = std::make_unique<State>(this);
    glSubWin = new SimpleGL3Window(statePtr.get(), 0, 0, 1030, 720);

    auto box_upper = new Fl_Box(glSubWin->w() + 10, 10, 230, 500, "Настройки");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    int leftBorder = glSubWin->w() + 10;

    auto choice_axis = new Fl_Check_Button(leftBorder+15, 35, 150, 30, "Оси координат");
    choice_axis->labelsize(16);
    choice_axis->value(statePtr->getIsAxesDrawn());
    choice_axis->callback([](Fl_Widget* w, void* statePtr){
        Fl_Check_Button* ch = dynamic_cast<Fl_Check_Button*>(w);
        State* state = static_cast<State*>(statePtr);
        state->setIsAxesDrawn(static_cast<bool>(ch->value()));
    }, statePtr.get());

    auto choice_normal = new Fl_Check_Button(leftBorder+15, 60, 150, 30, "Векторы нормалей");
    choice_normal->labelsize(16);
    choice_normal->value(statePtr->getIsNormalsDrawn());
    choice_normal->callback([](Fl_Widget* w, void* statePtr){
        Fl_Check_Button* ch = dynamic_cast<Fl_Check_Button*>(w);
        State* state = static_cast<State*>(statePtr);
        state->setIsNormalsDrawn(static_cast<bool>(ch->value()));
    }, statePtr.get());

    // action
    auto label_action = new Fl_Box(leftBorder+50, 100, 80, 30, "RGB-палитра фигур:");
    label_action->box(FL_NO_BOX);
    label_action->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_action->labelsize(16);

    auto slider_r = new Fl_Value_Slider(leftBorder+32,125 + 30*0, 180, 25, "R");
    slider_r->step(1.0);
    slider_r->align(FL_ALIGN_LEFT);
    slider_r->type(FL_HOR_SLIDER);
    slider_r->bounds(0, 255);
    slider_r->value(statePtr->getRGB().at(0));
    slider_r->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        auto rgb = state->getRGB();
        rgb.at(0) = ch->value();
    }, statePtr.get());

    auto slider_g = new Fl_Value_Slider(leftBorder+32,125 + 30*1, 180, 25, "G");
    slider_g->step(1.0);
    slider_g->align(FL_ALIGN_LEFT);
    slider_g->type(FL_HOR_SLIDER);
    slider_g->bounds(0, 255);
    slider_g->value(statePtr->getRGB().at(1));
    slider_g->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        auto rgb = state->getRGB();
        rgb.at(1) = ch->value();
    }, statePtr.get());

    auto slider_b = new Fl_Value_Slider(leftBorder+32,125 + 30*2, 180, 25, "B");
    slider_b->step(1.0);
    slider_b->align(FL_ALIGN_LEFT);
    slider_b->type(FL_HOR_SLIDER);
    slider_b->bounds(0, 255);
    slider_b->value(statePtr->getRGB().at(2));
    slider_b->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        auto rgb = state->getRGB();
        rgb.at(2) = ch->value();
    }, statePtr.get());
    glSubWin->end();
}

void AppWindow::updateGraphicsWindow(){
    glSubWin->update();
}