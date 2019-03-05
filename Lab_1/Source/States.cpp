#include "States.hpp"
#include "AppWin.hpp"

// ----- State ---------------------------------------------------------
void State::hideWidgets(){
    for (auto &widget : widgets)
        widget->hide();
}

void State::callUpdateGraphics(bool regenerate){
    appWinPtr->update(regenerate);
}

void State::showWidgets(){
    for (auto &widget : widgets)
        widget->show();
}

const State* State::getState(){
    return this;
}

size_t State::getNeededParentBoxHeight(){
    return parentBoxHeight;
}

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
    auto appPtr = State::appWinPtr;
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

void statePoints::setBkgColor(Fl_Color color){ bkgColor = color; }
void statePoints::setPointsNumber(size_t newNumber) { pointsNumber = newNumber; }
void statePoints::setPlacementType(PointPlacement newType){ placement = newType; }

Fl_Color statePoints::getBkgColor() const { return bkgColor; }
size_t statePoints::getPointsNumber() const { return pointsNumber; }
PointPlacement statePoints::getPlacementType() const { return placement; }




stateLines::stateLines(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 290;
    // numbers
    auto label_number = new Fl_Box(500 + 30, 70, 200, 30, "Количество линий:");
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
    slider_number->value(50);
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
    auto label_color = new Fl_Box(500 + 30, 170, 200, 30, "Цвет линий:");
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
            case 0: state->setLineColor(LineColor::random); break;
            case 1: state->setLineColor(LineColor::red); break;
            case 2: state->setLineColor(LineColor::green); break;
            case 3: state->setLineColor(LineColor::blue); break;
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
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(bt != nullptr);
        assert(state != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 260, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr); assert(appWin != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}


void stateLines::setPointsNumber(size_t newNumber){ pointsNumber = newNumber; }
void stateLines::setLength(LineLength newLength){ length = newLength; }
void stateLines::setBkgColor(Fl_Color color){ bkgColor = color; }
void stateLines::setLineColor(LineColor newColor){ linesColor = newColor; }

size_t stateLines::getPointsNumber() const { return pointsNumber; }
LineLength stateLines::getLength() const { return length; }
Fl_Color stateLines::getBkgColor() const { return bkgColor; }
LineColor stateLines::getLineColor() const { return linesColor; }