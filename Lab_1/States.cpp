#include "States.hpp"

statePoints::statePoints() : State() {
    auto si_pointsNumber = new SliderInput(500 + 40, 100, 180, 25, "Points number:");
    si_pointsNumber->bounds(1, 1000);
    si_pointsNumber->value(50);
    widgets.push_back(si_pointsNumber);

    auto choice_placamentType = new Fl_Choice(500 + 40, 140, 180, 25, "Размещение:");
    choice_placamentType->add("Saas");
    widgets.push_back(choice_placamentType);
}

stateLines::stateLines() : State() {
    auto si_pointsNumber = new SliderInput(500 + 40, 100, 180, 25, "Lines number:");
    si_pointsNumber->bounds(1, 1000);
    si_pointsNumber->value(50);
    widgets.push_back(si_pointsNumber);
}