#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    statePtr = std::make_unique<State>(this);
    glSubWin = new SimpleGL3Window(statePtr.get(), 0, 0, 600, 600);

    auto box_upper = new Fl_Box(glSubWin->w() + 10, 10, 230, 500, "Настройки");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    int leftBorder = glSubWin->w() + 10;

    // projection
    auto label_choice = new Fl_Box(leftBorder+15, 45, 150, 30, "Тип проецирования:");
    label_choice->box(FL_NO_BOX);
    label_choice->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_choice->labelsize(16);
    // +
    auto choice_projectionType = new Fl_Choice(leftBorder+15, 65, 200, 25);
    choice_projectionType->add("Перспективное");
    choice_projectionType->add("Ортогональное");
    choice_projectionType->value(0);
    choice_projectionType->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        State* state = static_cast<State*>(statePtr);
        switch (ch->value()){
            case 0: state->setProjectionType(ProjectionType::perspective); break;
            case 1: state->setProjectionType(ProjectionType::orthogonal); break;
            default:
                assert("Incorrect value in switch-lambda statement!\n" == nullptr);
                break;
        }
    }, statePtr.get());

    // action
    auto label_action = new Fl_Box(leftBorder+15, 100, 80, 30, "Действие:");
    label_action->box(FL_NO_BOX);
    label_action->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    label_action->labelsize(16);
    // +
    auto choice_action = new Fl_Choice(leftBorder+15, 120, 200, 25);
    choice_action->add("Перемещение");
    choice_action->add("Вращение");
    choice_action->add("Масштабирование");
    choice_action->value(static_cast<int>(statePtr->getActionType()));
    choice_action->callback([](Fl_Widget* w, void* statePtr){
        Fl_Choice* ch = dynamic_cast<Fl_Choice*>(w);
        State* state = static_cast<State*>(statePtr);
        switch (ch->value()){
            case 0: state->setActionType(ActionType::translate); break;
            case 1: state->setActionType(ActionType::rotate); break;
            case 2: state->setActionType(ActionType::scale); break;
            default:
                assert("Incorrect value in switch-lambda statement!\n" == nullptr);
                break;
        }
    }, statePtr.get());
    // +
    initXYZ_widgets(ActionType::translate, leftBorder, -20, 20);
    initXYZ_widgets(ActionType::rotate, leftBorder, 0, 360);
    initXYZ_widgets(ActionType::scale, leftBorder, 0, 5);

    makeVisibleXYZ_widget(static_cast<int>(statePtr->getActionType()));


    glSubWin->end();
}

void AppWindow::makeVisibleActionWidgets(ActionType type){
    makeVisibleXYZ_widget(static_cast<int>(type));
}

void AppWindow::updateGraphicsWindow(){
    glSubWin->update();
}

void AppWindow::initXYZ_widgets(ActionType action, int leftBorder, int leftValue, int rightValue){
    assert(leftValue <= rightValue);
    static std::array<std::string, 3> labels = {"X:", "Y:", "Z:"};
    int beginY_Slider = 160;
    int indentBetweenLabelAndSlider = 5;
    int indentBetweenSliders = 30;
    for (int i = 0; i < 3; i++){
        auto label = new Fl_Box(leftBorder+8, 
                                beginY_Slider + indentBetweenLabelAndSlider + indentBetweenSliders*i,
                                30, 30,
                                labels[i].c_str());
        label->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
        label->labelsize(13);
        XYZ_widgets.at(static_cast<int>(action)).push_back(label);

        auto slider = new Fl_Value_Slider(leftBorder+32,
                                          beginY_Slider + indentBetweenSliders*i,
                                          180, 25);
        slider->step(0.1);
        slider->align(FL_ALIGN_LEFT);
        slider->type(FL_HOR_SLIDER);
        slider->bounds(leftValue, rightValue);
        slider->value(0);
        callbackXYZInfo* dataPtr = new callbackXYZInfo {statePtr.get(), action, i};
        callbackData.push_back(dataPtr);
        slider->callback([](Fl_Widget* w, void* callbackData){
            Fl_Value_Slider* ch = dynamic_cast<Fl_Value_Slider*>(w);
            callbackXYZInfo* data = static_cast<callbackXYZInfo*>(callbackData);
            auto xyz = data->statePtr->getXYZ(data->action);
            xyz.at(data->coordinateNumber) = ch->value();
            data->statePtr->setXYZ(xyz, data->action);
        }, (void*)dataPtr);
        XYZ_widgets.at(static_cast<int>(action)).push_back(slider);
    }
}

void AppWindow::makeVisibleXYZ_widget(int index){
    for (auto &widgets : XYZ_widgets)
        for (auto &widget : widgets)
            widget->hide();
    for (auto &widget: XYZ_widgets.at(index))
        widget->show();
}