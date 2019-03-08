#include "States.hpp"

statePolygon::statePolygon(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 386;
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
    slider_number->bounds(1, 60);
    slider_number->value(9);
    slider_number->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(ch != nullptr);
        assert(state != nullptr);
        state->setPointsNumber((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number);

    // number of vertex
    auto label_color_1 = new Fl_Box(500 + 30, 122, 200, 30, "Тип фигуры:");
    label_color_1->box(FL_NO_BOX);
    label_color_1->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_1->labelsize(16);
    widgets.push_back(label_color_1);
    // +
    auto choice_color_1 = new Fl_Choice(500 + 40, 140, 180, 25);
    choice_color_1->add("4-угольник");
    choice_color_1->add("5-угольник");
    choice_color_1->add("6-угольник");
    choice_color_1->add("7-угольник");
    choice_color_1->add("8-угольник");
    choice_color_1->add("9-угольник");
    choice_color_1->add("10-угольник");
    choice_color_1->value(0);
    choice_color_1->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        statePolygon* state = static_cast<statePolygon*>(statePtr);
        assert(ch != nullptr); assert(state != nullptr);
        switch (ch->value()){
            case 0: state->setVertexNumber(4); break;
            case 1: state->setVertexNumber(5); break;
            case 2: state->setVertexNumber(6); break;
            case 3: state->setVertexNumber(7); break;
            case 4: state->setVertexNumber(8); break;
            case 5: state->setVertexNumber(9); break;
            case 6: state->setVertexNumber(10); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_1);

    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 321, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(bt != nullptr);
        assert(state != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 356, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr); assert(appWin != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}


// -------------------- set --------------------
void statePolygon::setPointsNumber(size_t newNumber){
    pointsNumber = newNumber;
}

void statePolygon::setVertexNumber(size_t newNumber){
    vertexNumber = newNumber;
}
    

void statePolygon::setBkgColor(Fl_Color color){
    bkgColor = color;
}
    
void statePolygon::setElemColor(ElemColor elem_color){
    color = elem_color;
}


// -------------------- get --------------------
size_t statePolygon::getPointsNumber() const {
    return pointsNumber;
}

size_t statePolygon::getVertexNumber() const{
    return vertexNumber;
}

Fl_Color statePolygon::getBkgColor() const {
    return bkgColor;
}

ElemColor statePolygon::getElemColor() const {
    return color;
}
