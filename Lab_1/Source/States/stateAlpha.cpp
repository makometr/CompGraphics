#include "States.hpp"

stateAlpha::stateAlpha(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 482;
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

    // alpha
    auto label_number_alpha = new Fl_Box(500 + 30, 95, 200, 30, "Значение параметра:");
    label_number_alpha->box(FL_NO_BOX);
    label_number_alpha->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_number_alpha->labelsize(16);
    widgets.push_back(label_number_alpha);
    // +
    auto slider_number_alpha = new Fl_Value_Slider(500 + 40, 115, 180, 25);
    slider_number_alpha->step((int)1);
    slider_number_alpha->align(FL_ALIGN_LEFT);
    slider_number_alpha->type(FL_HOR_SLIDER);
    slider_number_alpha->bounds(0, 100);
    slider_number_alpha->value(alpha);
    slider_number_alpha->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        state->setAlpha((int)ch->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(slider_number_alpha);

    // param
    auto label_color_param = new Fl_Box(500 + 30, 142, 200, 30, "Параметр функции");
    label_color_param->box(FL_NO_BOX);
    label_color_param->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_param->labelsize(16);
    widgets.push_back(label_color_param);
    // +
    auto choice_color_param = new Fl_Choice(500 + 40, 162, 180, 25);
    choice_color_param->add("NEVER");
    choice_color_param->add("LESS");
    choice_color_param->add("EQUAL");
    choice_color_param->add("LEQUAL");
    choice_color_param->add("GREATER");
    choice_color_param->add("NOTEQUAL");
    choice_color_param->add("GEQUAL");
    choice_color_param->add("ALWAYS");
    choice_color_param->value(7);
    choice_color_param->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(ch != nullptr);
        switch (ch->value()){
            case 0: state->setParameter(GL_NEVER); break;
            case 1: state->setParameter(GL_LESS); break;
            case 2: state->setParameter(GL_EQUAL); break;
            case 3: state->setParameter(GL_LEQUAL); break;
            case 4: state->setParameter(GL_GREATER); break;
            case 5: state->setParameter(GL_NOTEQUAL); break;
            case 6: state->setParameter(GL_GEQUAL); break;
            case 7: state->setParameter(GL_ALWAYS); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_param);




    // color edge upper
    auto label_color_u = new Fl_Box(500 + 30, 205, 200, 30, "Цвет верхней грани:");
    label_color_u->box(FL_NO_BOX);
    label_color_u->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_u->labelsize(16);
    widgets.push_back(label_color_u);
    // +
    auto choice_color_u = new Fl_Choice(500 + 40, 225, 180, 25);
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
    auto label_alpha_u = new Fl_Box(500 + 30, 252, 200, 30, "Прозрачность верхней грани:");
    label_alpha_u->box(FL_NO_BOX);
    label_alpha_u->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_alpha_u->labelsize(16);
    widgets.push_back(label_alpha_u);
    // +
    auto slider_alpha_u = new Fl_Value_Slider(500 + 40, 272, 180, 25);
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
    auto label_color_l = new Fl_Box(500 + 30, 315, 200, 30, "Цвет нижней грани:");
    label_color_l->box(FL_NO_BOX);
    label_color_l->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_l->labelsize(16);
    widgets.push_back(label_color_l);
    // +
    auto choice_color_l = new Fl_Choice(500 + 40, 335, 180, 25);
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
    auto label_alpha_l = new Fl_Box(500 + 30, 362, 200, 30, "Прозрачность нижней грани:");
    label_alpha_l->box(FL_NO_BOX);
    label_alpha_l->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_alpha_l->labelsize(16);
    widgets.push_back(label_alpha_l);
    // +
    auto slider_alpha_l = new Fl_Value_Slider(500 + 40, 382, 180, 25);
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

    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 417, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateAlpha* state = static_cast<stateAlpha*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 452, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}

void stateAlpha::setParameter(GLuint newParam){
    param = newParam;
}

GLuint stateAlpha::getParameter() const {
    return param;
}

void stateAlpha::setAlpha(int newAlpha){
    alpha = newAlpha;
}

int stateAlpha::getAlpha() const {
    return alpha;
}

void stateAlpha::setUpperColor(ElemColor newUpperColor){
    upperColor = newUpperColor;
}

ElemColor stateAlpha::getUpperColor() const {
    return upperColor;
}

void stateAlpha::setLowerColor(ElemColor newLowerColor){
    lowerColor = newLowerColor;
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