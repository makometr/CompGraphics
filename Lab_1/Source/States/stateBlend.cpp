#include "States.hpp"

stateBlend::stateBlend(AppWindow* ptr) : State(ptr) {
    State::parentBoxHeight = 262;
    auto toogle = new Fl_Check_Button(500+38, 65, 200, 30, "Режим активирован");
    toogle->down_box(FL_DOWN_BOX);
    toogle->labelsize(16);
    toogle->value(0);
    toogle->callback([](Fl_Widget* w, void* statePtr){
        Fl_Check_Button* t = dynamic_cast<Fl_Check_Button*>(w);
        stateBlend* state = static_cast<stateBlend*>(statePtr);
        assert(t != nullptr);
        State::setAlphaTest((bool)t->value());
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(toogle);

    // sfactor
    auto label_color_s = new Fl_Box(500 + 30, 95, 200, 30, "Параметр sfactor:");
    label_color_s->box(FL_NO_BOX);
    label_color_s->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_s->labelsize(16);
    widgets.push_back(label_color_s);
    // +
    auto choice_color_s = new Fl_Choice(500 + 40, 115, 180, 25);
    choice_color_s->add("ZERO");
    choice_color_s->add("ONE");
    choice_color_s->add("DST_COLOR");
    choice_color_s->add("ONE_MINUS_DST_COLOR");
    choice_color_s->add("SRC_ALPHA");
    choice_color_s->add("ONE_MINUS_SRC_ALPHA");
    choice_color_s->add("DST_ALPHA");
    choice_color_s->add("ONE_MINUS_DST_ALPHA");
    choice_color_s->add("SRC_ALPHA_SATURATE");
    choice_color_s->value(0);
    choice_color_s->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateBlend* state = static_cast<stateBlend*>(statePtr);
        assert(ch != nullptr);
        switch (ch->value()){
            case 0: state->setSFactor(GL_ZERO); break;
            case 1: state->setSFactor(GL_ONE); break;
            case 2: state->setSFactor(GL_DST_COLOR); break;
            case 3: state->setSFactor(GL_ONE_MINUS_DST_COLOR); break;
            case 4: state->setSFactor(GL_SRC_ALPHA); break;
            case 5: state->setSFactor(GL_ONE_MINUS_SRC_ALPHA); break;
            case 6: state->setSFactor(GL_DST_ALPHA); break;
            case 7: state->setSFactor(GL_ONE_MINUS_DST_ALPHA); break;
            case 8: state->setSFactor(GL_SRC_ALPHA_SATURATE); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_s);

    // dfactor
    auto label_color_d = new Fl_Box(500 + 30, 142, 200, 30, "Параметр dfactor:");
    label_color_d->box(FL_NO_BOX);
    label_color_d->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_color_d->labelsize(16);
    widgets.push_back(label_color_d);
    // +
    auto choice_color_d = new Fl_Choice(500 + 40, 162, 180, 25);
    choice_color_d->add("ZERO");
    choice_color_d->add("ONE");
    choice_color_d->add("SRC_COLOR");
    choice_color_d->add("ONE_MINUS_SRC_COLOR");
    choice_color_d->add("SRC_ALPHA");
    choice_color_d->add("ONE_MINUS_SRC_ALPHA");
    choice_color_d->add("DST_ALPHA");
    choice_color_d->add("ONE_MINUS_DST_ALPHA");
    choice_color_d->value(0);
    choice_color_d->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        stateBlend* state = static_cast<stateBlend*>(statePtr);
        assert(ch != nullptr);
        switch (ch->value()){
            case 0: state->setDFactor(GL_ZERO); break;
            case 1: state->setDFactor(GL_ONE); break;
            case 2: state->setDFactor(GL_SRC_COLOR); break;
            case 3: state->setDFactor(GL_ONE_MINUS_SRC_COLOR); break;
            case 4: state->setDFactor(GL_SRC_ALPHA); break;
            case 5: state->setDFactor(GL_ONE_MINUS_SRC_ALPHA); break;
            case 6: state->setDFactor(GL_DST_ALPHA); break;
            case 7: state->setDFactor(GL_ONE_MINUS_DST_ALPHA); break;
            default: assert("Incorrect value in switch statement!\n" == nullptr); break;
        }
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(choice_color_d);


    // bkg color
    auto button_choose_color = new Fl_Button(500+60, 197, 140, 30, "Задать цвет фона");
    button_choose_color->callback([](Fl_Widget* w, void* statePtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        stateBlend* state = static_cast<stateBlend*>(statePtr);
        assert(bt != nullptr);
        state->setBkgColor(fl_show_colormap(state->getBkgColor()));
        state->callUpdateGraphics(true);
    }, (void*)this);
    widgets.push_back(button_choose_color);

    auto button_regenerate = new Fl_Button(500+60, 232, 140, 30, "Перегенерировать");
    button_regenerate->callback([](Fl_Widget* w, void* appWinPtr){
        Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
        AppWindow* appWin = static_cast<AppWindow*>(appWinPtr);
        assert(bt != nullptr);
        appWin->update(true);
    }, (void*)button_regenerate->parent());
    widgets.push_back(button_regenerate);

    hideWidgets();
}

void stateBlend::setSFactor(GLuint newFactor){
    sfactor = newFactor;
}

GLuint stateBlend::getSFactor() const {
    return sfactor;
}

void stateBlend::setDFactor(GLuint newFactor){
    dfactor = newFactor;
}

GLuint stateBlend::getDFactor() const {
    return dfactor;
}

void stateBlend::setBkgColor(Fl_Color color){
    bkgColor = color;
}

Fl_Color stateBlend::getBkgColor() const {
    return bkgColor;
}