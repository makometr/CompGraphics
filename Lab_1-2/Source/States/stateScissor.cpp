#include "States.hpp"

stateScissor::stateScissor(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 337;
    auto toogle = new Fl_Check_Button(500+38, 65, 200, 30, "Режим активирован");
    toogle->down_box(FL_DOWN_BOX);
    toogle->labelsize(16);
    toogle->value(0);
    toogle->callback([](Fl_Widget* w, void* statePtr){
        Fl_Check_Button* t = dynamic_cast<Fl_Check_Button*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(t != nullptr);
        State::setScissorTest((bool)t->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(toogle);

    // x
    auto label_number_x = new Fl_Box(500 + 30, 95, 200, 30, "Начальный X:");
    label_number_x->box(FL_NO_BOX);
    label_number_x->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number_x->labelsize(16);
    widgets.push_back(label_number_x);
    // +
    auto slider_number_x = new Fl_Value_Slider(500 + 40, 115, 180, 25);
    slider_number_x->step((int)1);
    slider_number_x->align(FL_ALIGN_LEFT);
    slider_number_x->type(FL_HOR_SLIDER);
    slider_number_x->bounds(0, 500);
    slider_number_x->value(x);
    slider_number_x->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(ch != nullptr);
        state->setX((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number_x);

    // y
    auto label_number_y = new Fl_Box(500 + 30, 147, 200, 30, "Начальный Y:");
    label_number_y->box(FL_NO_BOX);
    label_number_y->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number_y->labelsize(16);
    widgets.push_back(label_number_y);
    // +
    auto slider_number_y = new Fl_Value_Slider(500 + 40, 167, 180, 25);
    slider_number_y->step((int)1);
    slider_number_y->align(FL_ALIGN_LEFT);
    slider_number_y->type(FL_HOR_SLIDER);
    slider_number_y->bounds(0, 500);
    slider_number_y->value(y);
    slider_number_y->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(ch != nullptr);
        state->setY((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number_y);

    // width
    auto label_number_w = new Fl_Box(500 + 30, 199, 200, 30, "Ширина:");
    label_number_w->box(FL_NO_BOX);
    label_number_w->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number_w->labelsize(16);
    widgets.push_back(label_number_w);
    // +
    auto slider_number_w = new Fl_Value_Slider(500 + 40, 219, 180, 25);
    slider_number_w->step((int)1);
    slider_number_w->align(FL_ALIGN_LEFT);
    slider_number_w->type(FL_HOR_SLIDER);
    slider_number_w->bounds(0, 500);
    slider_number_w->value(width);
    slider_number_w->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(ch != nullptr);
        state->setWidth((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number_w);

    // height
    auto label_number_h = new Fl_Box(500 + 30, 251, 200, 30, "Высота:");
    label_number_h->box(FL_NO_BOX);
    label_number_h->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number_h->labelsize(16);
    widgets.push_back(label_number_h);
    // +
    auto slider_number_h = new Fl_Value_Slider(500 + 40, 271, 180, 25);
    slider_number_h->step((int)1);
    slider_number_h->align(FL_ALIGN_LEFT);
    slider_number_h->type(FL_HOR_SLIDER);
    slider_number_h->bounds(0, 500);
    slider_number_h->value(height);
    slider_number_h->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(ch != nullptr);
        state->setHeight((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number_h);



    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 307, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateScissor* state = static_cast<stateScissor*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    hideWidgets();
}

void stateScissor::setX(int newX){
    x = newX;
}

int stateScissor::getX() const{
    return x;
}


void stateScissor::setY(int newY){
    y = newY;
}

int stateScissor::getY() const{
    return y;
}


void stateScissor::setWidth(int newWidth){
    width = newWidth;
}

int stateScissor::getWidth() const {
    return width;
}


void stateScissor::setHeight(int newHeight){
    height = newHeight;
}

int stateScissor::getHeight() const {
    return height;
}

void stateScissor::setBkgColor(Fl_Color color){
    bkgColor = color;
}

Fl_Color stateScissor::getBkgColor() const {
    return bkgColor;
}