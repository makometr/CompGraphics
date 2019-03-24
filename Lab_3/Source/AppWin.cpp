#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    state = new State(this);
    glSubWin = new GlSubWin(10, 10, 500, 500, state);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 190, "Фрактал:");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    // deep
    auto label_deep = new Fl_Box(500 + 30, 40, 200, 30, "Количество повторений:");
    label_deep->box(FL_NO_BOX);
    label_deep->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_deep->labelsize(16);
    // +
    auto slider_deep = new Fl_Value_Slider(500 + 40, 60, 180, 25);
    slider_deep->step((int)1);
    slider_deep->align(FL_ALIGN_LEFT);
    slider_deep->type(FL_HOR_SLIDER);
    slider_deep->bounds(0, 20);
    slider_deep->value(0);
    slider_deep->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setDeep((GLdouble)ch->value());
        state->callUpdateGraphics();
    }, (void*)state);

    // length
    auto label_length = new Fl_Box(500 + 30, 92, 200, 30, "Длина");
    label_length->box(FL_NO_BOX);
    label_length->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_length->labelsize(16);
    // +
    auto slider_length = new Fl_Value_Slider(500 + 40, 110, 180, 25);
    slider_length->step((int)1);
    slider_length->align(FL_ALIGN_LEFT);
    slider_length->type(FL_HOR_SLIDER);
    slider_length->bounds(10, 200);
    slider_length->value(0);
    slider_length->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        State* state = static_cast<State*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setDeep((GLdouble)ch->value());
        state->callUpdateGraphics();
    }, (void*)state);

    // color
    auto label_color = new Fl_Box(500 + 30, 140, 200, 30, "Цвет:");
    label_color->box(FL_NO_BOX);
    label_color->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color->labelsize(16);
    // +
    auto choice_color = new Fl_Choice(500 + 40, 160, 180, 25);
    choice_color->add("Случайный");
    choice_color->add("Красный");
    choice_color->add("Зелёный");
    choice_color->add("Синий");
    choice_color->add("ПурПурный");
    choice_color->add("Циановый");
    choice_color->add("Жёлтый");
    choice_color->value(0);
    choice_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w); assert(ch != nullptr);
        State* state = static_cast<State*>(statePtr);
        ElemColor newColor = ElemColor::random;
        switch (ch->value()){
            case 0: newColor = ElemColor::random; break;
            case 1: newColor = ElemColor::red; break;
            case 2: newColor = ElemColor::green; break;
            case 3: newColor = ElemColor::blue; break;
            case 4: newColor = ElemColor::magneta; break;
            case 5: newColor = ElemColor::cyan; break;
            case 6: newColor = ElemColor::yellow; break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->setElemColor(newColor);
        state->callUpdateGraphics();
    }, (void*)state);
}

void AppWindow::update(){
    glSubWin->drawUpdated();
}