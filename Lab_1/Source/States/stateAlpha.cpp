#include "States.hpp"

stateAlpha::stateAlpha(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 337;
    auto toogle = new Fl_Check_Button(500+38, 65, 200, 30, "Режим активирован");
    toogle->down_box(FL_DOWN_BOX);
    toogle->labelsize(16);
    toogle->value(0);
    toogle->callback([](Fl_Widget* w, void* statePtr){
        Fl_Check_Button* t = dynamic_cast<Fl_Check_Button*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(t != nullptr);
        State::setAlphaTest((bool)t->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(toogle);

    // color edge upper
    auto label_color_u = new Fl_Box(500 + 30, 95, 200, 30, "Цвет верхней грани:");  // 95
    label_color_u->box(FL_NO_BOX);
    label_color_u->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_u->labelsize(16);
    widgets.push_back(label_color_u);
    // +
    auto choice_color_u = new Fl_Choice(500 + 40, 115, 180, 25);
    choice_color_u->add("Случайный");
    choice_color_u->add("Красный");
    choice_color_u->add("Зелёный");
    choice_color_u->add("Синий");
    choice_color_u->value(0);
    choice_color_u->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        switch (ch->value()){
            case 0: state->setUpperColor(ElemColor::random); break;
            case 1: state->setUpperColor(ElemColor::red); break;
            case 2: state->setUpperColor(ElemColor::green); break;
            case 3: state->setUpperColor(ElemColor::blue); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_u);

    // upper alpha
    auto label_alpha_u = new Fl_Box(500 + 30, 145, 200, 30, "Прозрачность верхней грани:");
    label_alpha_u->box(FL_NO_BOX);
    label_alpha_u->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_alpha_u->labelsize(16);
    widgets.push_back(label_alpha_u);
    // +
    auto slider_alpha_u = new Fl_Value_Slider(500 + 40, 165, 180, 25);
    slider_alpha_u->step((int)1);
    slider_alpha_u->align(FL_ALIGN_LEFT);
    slider_alpha_u->type(FL_HOR_SLIDER);
    slider_alpha_u->bounds(0, 100);
    slider_alpha_u->value(lowerAlpha);
    slider_alpha_u->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        state->setUpperAlpha((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_alpha_u);

    // color edge lower
    auto label_color_l = new Fl_Box(500 + 30, 201, 200, 30, "Цвет нижней грани:");
    label_color_l->box(FL_NO_BOX);
    label_color_l->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_l->labelsize(16);
    widgets.push_back(label_color_l);
    // +
    auto choice_color_l = new Fl_Choice(500 + 40, 221, 180, 25);
    choice_color_l->add("Случайный");
    choice_color_l->add("Красный");
    choice_color_l->add("Зелёный");
    choice_color_l->add("Синий");
    choice_color_l->value(0);
    choice_color_l->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        switch (ch->value()){
            case 0: state->setLowerColor(ElemColor::random); break;
            case 1: state->setLowerColor(ElemColor::red); break;
            case 2: state->setLowerColor(ElemColor::green); break;
            case 3: state->setLowerColor(ElemColor::blue); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_l);


    // lower alpha
    auto label_alpha_l = new Fl_Box(500 + 30, 251, 200, 30, "Прозрачность нижней грани:");
    label_alpha_l->box(FL_NO_BOX);
    label_alpha_l->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_alpha_l->labelsize(16);
    widgets.push_back(label_alpha_l);
    // +
    auto slider_alpha_l = new Fl_Value_Slider(500 + 40, 271, 180, 25);
    slider_alpha_l->step((int)1);
    slider_alpha_l->align(FL_ALIGN_LEFT);
    slider_alpha_l->type(FL_HOR_SLIDER);
    slider_alpha_l->bounds(0, 100);
    slider_alpha_l->value(lowerAlpha);
    slider_alpha_l->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        state->setLowerAlpha((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_alpha_l);

    // bkg color lower
    auto button_choose_color = new Fl_Button(500+60, 307, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    hideWidgets();
}

void stateAlpha::setParameter(AlphaParameter newParam){
    param = newParam;
}

AlphaParameter stateAlpha::getParameter() const {
    return param;
}

void stateAlpha::setUpperColor(ElemColor newUpperColor){

}

ElemColor stateAlpha::getUpperColor() const {
    return upperColor;
}

void stateAlpha::setLowerColor(ElemColor newLowerColor){

}

ElemColor stateAlpha::getLowerColor() const {
    return lowerColor;
}

void stateAlpha::setLowerAlpha(int newLowerAlpha){
    lowerAlpha = newLowerAlpha;
}

int stateAlpha::getLowerAlpha() const {
    return lowerAlpha;
}

void stateAlpha::setUpperAlpha(int newUpperAlpha){
    upperAlpha = newUpperAlpha;
}

int stateAlpha::getUpperAlpha() const {
    return upperAlpha;
}

void stateAlpha::setBkgColor(Fl_Color color){
    bkgColor = color;
}

Fl_Color stateAlpha::getBkgColor() const {
    return bkgColor;
}