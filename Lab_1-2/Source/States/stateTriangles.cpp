#include "States.hpp"

stateTriangles::stateTriangles(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 338;
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
    slider_number->value(pointsNumber);
    slider_number->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        statePoints* state = static_cast<statePoints*>(statePtr);
        assert(ch != nullptr);
        state->setPointsNumber((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number);

    // color edge_1
    auto label_color_1 = new Fl_Box(500 + 30, 122, 200, 30, "Цвет вершины 1:");
    label_color_1->box(FL_NO_BOX);
    label_color_1->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_1->labelsize(16);
    widgets.push_back(label_color_1);
    // +
    auto choice_color_1 = new Fl_Choice(500 + 40, 140, 180, 25);
    choice_color_1->add("Случайный");
    choice_color_1->add("Красный");
    choice_color_1->add("Зелёный");
    choice_color_1->add("Синий");
    choice_color_1->value(0);
    choice_color_1->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateTriangles* state = static_cast<stateTriangles*>(statePtr);
        assert(ch != nullptr);
        auto currColor = state->getTripleElemColor();
        switch (ch->value()){
            case 0: std::get<0>(currColor) = ElemColor::random; break;
            case 1: std::get<0>(currColor) = ElemColor::red; break;
            case 2: std::get<0>(currColor) = ElemColor::green; break;
            case 3: std::get<0>(currColor) = ElemColor::blue; break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->setTripleColor(currColor);
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_1);

    // color edge_2
    auto label_color_2 = new Fl_Box(500 + 30, 170, 200, 30, "Цвет вершины 2:");
    label_color_2->box(FL_NO_BOX);
    label_color_2->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_2->labelsize(16);
    widgets.push_back(label_color_2);
    // +
    auto choice_color_2 = new Fl_Choice(500 + 40, 190, 180, 25);
    choice_color_2->add("Случайный");
    choice_color_2->add("Красный");
    choice_color_2->add("Зелёный");
    choice_color_2->add("Синий");
    choice_color_2->value(0);
    choice_color_2->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateTriangles* state = static_cast<stateTriangles*>(statePtr);
        assert(ch != nullptr);
        auto currColor = state->getTripleElemColor();
        switch (ch->value()){
            case 0: std::get<1>(currColor) = ElemColor::random; break;
            case 1: std::get<1>(currColor) = ElemColor::red; break;
            case 2: std::get<1>(currColor) = ElemColor::green; break;
            case 3: std::get<1>(currColor) = ElemColor::blue; break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->setTripleColor(currColor);
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_2);

    // color edge_3
    auto label_color_3 = new Fl_Box(500 + 30, 218, 200, 30, "Цвет вершины 3:");
    label_color_3->box(FL_NO_BOX);
    label_color_3->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_3->labelsize(16);
    widgets.push_back(label_color_3);
    // +
    auto choice_color_3 = new Fl_Choice(500 + 40, 238, 180, 25);
    choice_color_3->add("Случайный");
    choice_color_3->add("Красный");
    choice_color_3->add("Зелёный");
    choice_color_3->add("Синий");
    choice_color_3->value(0);
    choice_color_3->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateTriangles* state = static_cast<stateTriangles*>(statePtr);
        assert(ch != nullptr);
        auto currColor = state->getTripleElemColor();
        switch (ch->value()){
            case 0: std::get<2>(currColor) = ElemColor::random; break;
            case 1: std::get<2>(currColor) = ElemColor::red; break;
            case 2: std::get<2>(currColor) = ElemColor::green; break;
            case 3: std::get<2>(currColor) = ElemColor::blue; break;
            default:
                assert("Incorrect value in switch statement!\n" == nullptr);
                break;
        }
        state->setTripleColor(currColor);
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_3);

    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 273, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateTriangles* state = static_cast<stateTriangles*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 308, 140, 30, "Перегенерировать");
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
void stateTriangles::setPointsNumber(size_t newNumber){
    pointsNumber = newNumber;
}

void stateTriangles::setBkgColor(Fl_Color color){
    bkgColor = color;
}
    
void stateTriangles::setTripleColor(TripleColors tripleCol){
    colors = tripleCol;
}


// -------------------- get --------------------
size_t stateTriangles::getPointsNumber() const {
    return pointsNumber;
}

Fl_Color stateTriangles::getBkgColor() const {
    return bkgColor;
}

TripleColors stateTriangles::getTripleElemColor() const {
    return colors;
}
