#include "States.hpp"

// ----- statePoints --------------------------------------------------
statePoints::statePoints(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 240;
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
    slider_number->value(100);
    slider_number->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setPointsNumber((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number);

    // placement
    auto label_choice = new Fl_Box(500 + 30, 122, 200, 30, "Тип размещения:");
    label_choice->box(FL_NO_BOX);
    label_choice->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_choice->labelsize(16);
    widgets.push_back(label_choice);
    // +
    auto choice_placamentType = new Fl_Choice(500 + 40, 140, 180, 25);
    choice_placamentType->add("По кругу");
    choice_placamentType->add("По квадрату");
    choice_placamentType->add("По фону (нормально)");
    choice_placamentType->add("По фону (равномерно)");
    choice_placamentType->value(0);
    choice_placamentType->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        switch (ch->value()){
            case 0: state->setPlacementType(PointPlacement::circle); break;
            case 1: state->setPlacementType(PointPlacement::rect); break;
            case 2: state->setPlacementType(PointPlacement::normal); break;
            case 3: state->setPlacementType(PointPlacement::uniform); break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->callUpdateGraphics(true);
        
    }, (void*)this);
    widgets.push_back(choice_placamentType);

    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 175, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(bt != nullptr); assert(state != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 210, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr); assert(appWin != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}

void statePoints::setBkgColor(Fl_Color color){
    bkgColor = color;
}

void statePoints::setPointsNumber(size_t newNumber) {
    pointsNumber = newNumber;
}

void statePoints::setPlacementType(PointPlacement newType){
    placement = newType;
}


Fl_Color statePoints::getBkgColor() const {
    return bkgColor;
}

size_t statePoints::getPointsNumber() const {
    return pointsNumber;
}

PointPlacement statePoints::getPlacementType() const {
    return placement;
}
