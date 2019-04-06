#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    state = new State(this);
    glSubWin = new GlSubWin(10, 10, 500, 500, state);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 190, "Настройки");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    // points
    auto label_point = new Fl_Box(500 + 30, 40, 200, 30, "Точка:");
    boxTextSettings(label_point);
    // +
    auto choice_point = new Fl_Choice(500 + 40, 60, 180, 25);
    // for (int i = 0; i < numOfPoints; i++)
    //     choice_point->add(std::to_string(i));
    choice_point->add("1");
    choice_point->add("2");
    choice_point->add("3");
    choice_point->add("4");
    choice_point->value(0);
    choice_point->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w); assert(ch != nullptr);
        State* state = static_cast<State*>(statePtr);
        state->setCurrPoint(ch->value());
    }, (void*)state);

    // x
    auto label_x = new Fl_Box(500 + 30, 92, 200, 30, "X:");
    boxTextSettings(label_x);
    // +
    widgetX = new Fl_Value_Slider(500 + 40, 110, 180, 25);
    widgetX->step((int)1);
    widgetX->align(FL_ALIGN_LEFT);
    widgetX->type(FL_HOR_SLIDER);
    widgetX->bounds(0, 500);
    widgetX->value(state->getCurrPoint_X());
    widgetX->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w); assert(ch != nullptr);
        State* state = static_cast<State*>(statePtr);
        state->setCurrPoint_X((GLdouble)ch->value());
    }, (void*)state);

    // y
    auto label_y = new Fl_Box(500 + 30, 140, 200, 30, "Y:");
    boxTextSettings(label_y);
    // +
    widgetY = new Fl_Value_Slider(500 + 40, 160, 180, 25);
    widgetY->step((int)1);
    widgetY->align(FL_ALIGN_LEFT);
    widgetY->type(FL_HOR_SLIDER);
    widgetY->bounds(0, 500);
    widgetY->value(state->getCurrPoint_Y());
    widgetY->callback([](Fl_Widget* w, void* statePtr){
        Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w); assert(ch != nullptr);
        State* state = static_cast<State*>(statePtr);
        state->setCurrPoint_Y((GLdouble)ch->value());
    }, (void*)state);

    // // color
    // auto label_color = new Fl_Box(500 + 30, 140, 200, 30, "Цвет:");
    // boxTextSettings(label_color);
    // // +
    // auto choice_color = new Fl_Choice(500 + 40, 160, 180, 25);
    // choice_color->add("Случайный");
    // choice_color->add("Красный");
    // choice_color->add("Зелёный");
    // choice_color->add("Синий");
    // choice_color->add("ПурПурный");
    // choice_color->add("Циановый");
    // choice_color->add("Жёлтый");
    // choice_color->value(0);
    // choice_color->callback([](Fl_Widget* w, void* statePtr){
    //     Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w); assert(ch != nullptr);
    //     State* state = static_cast<State*>(statePtr);
    //     ElemColor newColor = ElemColor::random;
    //     switch (ch->value()){
    //         case 0: newColor = ElemColor::random; break;
    //         case 1: newColor = ElemColor::red; break;
    //         case 2: newColor = ElemColor::green; break;
    //         case 3: newColor = ElemColor::blue; break;
    //         case 4: newColor = ElemColor::magneta; break;
    //         case 5: newColor = ElemColor::cyan; break;
    //         case 6: newColor = ElemColor::yellow; break;
    //         default: assert("Incorrect value in switch statement!\n" == nullptr); break;
    //     }
    //     // state->setElemColor(newColor);
    //     state->callUpdateGraphics();
    // }, (void*)state);
}


void AppWindow::update(){
    // label_error->hide();
    glSubWin->drawUpdated();
}

void AppWindow::updateXY(Coord curCoord){
    widgetX->value(curCoord.first);
    widgetY->value(curCoord.second);
}


void AppWindow::boxTextSettings(Fl_Box* box) {
    box->box(FL_NO_BOX);
    box->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box->labelsize(16);
}

// void AppWindow::makeVisiblePointWidgets(size_t pointNum){
//     for (auto &widget : widgets)
//         widget->hide();
//     widgets.at(2*pointNum)->visible();
//     widgets.at(2*pointNum+1)->visible();
// }