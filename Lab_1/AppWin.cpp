#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new GlSubWin(10, 10, 500, 500);
    primitiveTypeStates.reserve(StatesNumber);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 300, "Primitive name:");
    box_upper->box(FL_UP_BOX);
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    choice = new Fl_Choice(glSubWin->w() + 40, 37, 180, 25);
    choice->add("GL_POINTS",         "q", changePrimitive_CB, (void*)this);
    choice->add("GL_LINES",          "w", changePrimitive_CB, (void*)this);
    choice->add("GL_LINE_STRIP",     "e", changePrimitive_CB, (void*)this);
    choice->add("GL_LINE_LOOP",      "r", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLES",      "t", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLE_STRIP", "a", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLE_FAN",   "s", changePrimitive_CB, (void*)this);
    choice->add("QUADS",             "d", changePrimitive_CB, (void*)this);
    choice->add("GL_QUAD_STRIP",     "f", changePrimitive_CB, (void*)this);
    choice->add("GL_POLYGON",        "g", changePrimitive_CB, (void*)this);
    choice->value(0);

    State* statePtr = nullptr;
    // Create widgets for 0-state: POINT
    statePtr = new statePoints();
    // primitiveTypeStates.push_back(statePtr);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));
    // choice_placamentType_1->type(FL_VERT_FILL_SLIDER);
    // choice_placamentType_1->color(FL_INDIANRED, FL_RED);

    // Create widgets for 1-state: LINE
    statePtr = new stateLines();
    // primitiveTypeStates.push_back(statePtr);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));
    primitiveTypeStates.at(1).get()->hideWidgets();

    end();
}

void AppWindow::changePrimitive_CB(Fl_Widget* w, void* appWinPtr){
    Fl_Choice* widget = dynamic_cast<Fl_Choice*>(w);
    AppWindow* app_win = static_cast<AppWindow*>(appWinPtr);
    assert(widget != nullptr);
    assert(app_win != nullptr);
    std::cout << "Value: " << widget->value() << "\n";

    app_win->changePrimitive(static_cast<PrimitiveType>(widget->value()));
}

void AppWindow::changePrimitive(PrimitiveType type){
    makeCurrentWidgetsInvisiable();
    setCurrentPrimitiveType(type);
    makeCurrentWidgetsVisiable();

    glSubWin->setPrimitiveType(type);
}

void AppWindow::makeCurrentWidgetsInvisiable(){
    primitiveTypeStates.at(static_cast<int>(currentType)).get()->hideWidgets();
}

void AppWindow::setCurrentPrimitiveType(PrimitiveType type){
    currentType = type;
}

void AppWindow::makeCurrentWidgetsVisiable(){
    primitiveTypeStates.at(static_cast<int>(currentType)).get()->showWidgets();
}

// ----- States -------

void State::hideWidgets(){
    for (auto &widget : widgets)
        widget->hide();
}

void State::showWidgets(){
    for (auto &widget : widgets)
        widget->show();
}

const State* State::getState(){
    return this;
}