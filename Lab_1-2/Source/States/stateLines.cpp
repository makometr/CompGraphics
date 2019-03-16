#include "States.hpp"

stateLines::stateLines(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 290;
    // numbers
    auto label_number = new Fl_Box(500 + 30, 70, 200, 30, "Количество точек:");
    label_number->box(FL_NO_BOX);
    label_number->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number->labelsize(16);
    widgets.push_back(label_number);
    // +
    auto slider_number = new Fl_Value_Slider(500 + 40, 90, 180, 25);
    slider_number->step((int)1);
    slider_number->align(FL_ALIGN_LEFT);
    slider_number->type(FL_HOR_SLIDER);
    slider_number->bounds(1, 1000);
    slider_number->value(pointsNumber);
    slider_number->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateLines* state = static_cast<stateLines*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setPointsNumber((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number);

    // length
    auto label_length = new Fl_Box(500 + 30, 122, 200, 30, "Средняя длина:");
    label_length->box(FL_NO_BOX);
    label_length->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_length->labelsize(16);
    widgets.push_back(label_length);
    // +
    auto choice_length = new Fl_Choice(500 + 40, 140, 180, 25);
    choice_length->add("Малая");
    choice_length->add("Средняя");
    choice_length->add("Большая");
    choice_length->value(0);
    choice_length->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateLines* state = static_cast<stateLines*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        switch (ch->value()){
            case 0: state->setLength(LineLength::small); break;
            case 1: state->setLength(LineLength::middle); break;
            case 2: state->setLength(LineLength::large); break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->callUpdateGraphics(true);
        
    }, (void*)this);
    widgets.push_back(choice_length);

    // color lines
    auto label_color = new Fl_Box(500 + 30, 170, 200, 30, "Цвет точек:");
    label_color->box(FL_NO_BOX);
    label_color->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color->labelsize(16);
    widgets.push_back(label_color);
    // +
    auto choice_color = new Fl_Choice(500 + 40, 190, 180, 25);
    choice_color->add("Случайный");
    choice_color->add("Красный");
    choice_color->add("Зелёный");
    choice_color->add("Синий");
    choice_color->value(0);
    choice_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateLines* state = static_cast<stateLines*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        switch (ch->value()){
            case 0: state->setElemColor(ElemColor::random); break;
            case 1: state->setElemColor(ElemColor::red); break;
            case 2: state->setElemColor(ElemColor::green); break;
            case 3: state->setElemColor(ElemColor::blue); break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->callUpdateGraphics(true);
        
    }, (void*)this);
    widgets.push_back(choice_color);

    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 225, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateLines* state = static_cast<stateLines*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 260, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}

void stateLines::setPointsNumber(size_t newNumber){
    pointsNumber = newNumber;
}

void stateLines::setLength(LineLength newLength){
    length = newLength;
}

void stateLines::setBkgColor(Fl_Color color){
    bkgColor = color;
}

void stateLines::setElemColor(ElemColor newColor){
    linesColor = newColor;
}


size_t stateLines::getPointsNumber() const {
    return pointsNumber;
}

LineLength stateLines::getLength() const {
    return length;
}

Fl_Color stateLines::getBkgColor() const {
    return bkgColor;
}

ElemColor stateLines::getElemColor() const {
    return linesColor;
}

