#include "States.hpp"

statePoints::statePoints() : State() {
    auto si_pointsNumber = new SliderInput(500 + 40, 90, 180, 25, "Кол-во точек:");
    si_pointsNumber->bounds(1, 1000);
    si_pointsNumber->value(50);
    widgets.push_back(si_pointsNumber);

    auto label_choice = new Fl_Box(500 + 30, 122, 200, 30, "Тип размещения:");
    label_choice->box(FL_NO_BOX);
    label_choice->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_choice->labelsize(16);
    widgets.push_back(label_choice);

    auto choice_placamentType = new Fl_Choice(500 + 40, 140, 180, 25);
    choice_placamentType->add("По кругу");
    choice_placamentType->add("По квадрату");
    choice_placamentType->add("По фону (нормально)");
    choice_placamentType->add("По фону (равномерно)");
    choice_placamentType->value(1);
    widgets.push_back(choice_placamentType);

    auto button_choose_color = new Fl_Button(500+60, 175, 140, 30, "Задать цвет фона");
    button_choose_color->callback(callColorChooser_CB, (void*)this);

    // auto color_chooser = new Fl_Color_Chooser(500+40, 200, 180, 200);
}

void statePoints::callColorChooser_CB(Fl_Widget* w, void* statePtr){
    Fl_Button* bt = dynamic_cast<Fl_Button*>(w);
    statePoints* state = static_cast<statePoints*>(statePtr);
    assert(bt != nullptr);
    assert(state != nullptr);
    // std::cout << "Before: " << state->bkgColor << "\n";
    state->bkgColor = fl_show_colormap(state->bkgColor);
    // std::cout << "After: " << state->bkgColor << "\n";
}

void statePoints::setBkgColor(Fl_Color color){
    bkgColor = color;
}

Fl_Color statePoints::getBkgColor() const {
    return bkgColor;
}









stateLines::stateLines() : State() {
    auto si_pointsNumber = new SliderInput(500 + 40, 100, 180, 25, "Lines number:");
    si_pointsNumber->bounds(1, 1000);
    si_pointsNumber->value(50);
    widgets.push_back(si_pointsNumber);
}