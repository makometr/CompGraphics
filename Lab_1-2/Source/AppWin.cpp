#include "AppWin.hpp"

AppWindow::AppWindow(int W,int H,const char*L)
    : Fl_Window(W,H,L)
{
    glSubWin = new GlSubWin(10, 10, 500, 500);
    primitiveTypeStates.reserve(PrimitivesNumber + TestsNumber);

    box_upper = new Fl_Box(glSubWin->w() + 20, 10, 750-500-10-10-10, 300, "Primitive name:");
    box_upper->box(FL_UP_BOX); // for correct resizing this object should be owned by stateSmth below
    box_upper->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP);
    box_upper->labelfont(FL_BOLD);
    box_upper->labelsize(22);

    choice = new Fl_Choice(glSubWin->w() + 40, 37, 180, 25);
    // primitives
    choice->add("GL_POINTS",         "q", changePrimitive_CB, (void*)this);
    choice->add("GL_LINES",          "w", changePrimitive_CB, (void*)this);
    choice->add("GL_LINE_STRIP",     "e", changePrimitive_CB, (void*)this);
    choice->add("GL_LINE_LOOP",      "r", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLES",      "t", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLE_STRIP", "a", changePrimitive_CB, (void*)this);
    choice->add("GL_TRIANGLE_FAN",   "s", changePrimitive_CB, (void*)this);
    choice->add("QUADS",             "d", changePrimitive_CB, (void*)this);
    choice->add("GL_QUAD_STRIP",     "f", changePrimitive_CB, (void*)this);
    choice->add("_GL_POLYGON",       "g", changePrimitive_CB, (void*)this);
    // tests
    choice->add("TEST - SCISSOR",    "z", changePrimitive_CB, (void*)this);
    choice->add("TEST - ALPHA",      "x", changePrimitive_CB, (void*)this);
    choice->add("TEST - BLEND",      "c", changePrimitive_CB, (void*)this);
    choice->value(0);
    State* statePtr = nullptr;

    // Create widgets for 0-state: POINT
    statePtr = new statePoints(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));
    // primitiveTypeStates.push_back(std::make_unique<State>(this);

    // Create widgets for 1-state: LINES
    statePtr = new stateLines(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 2-state: LINE_STRIP
    statePtr = new stateLineStrips(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 3-state: LINE_LOOP
    statePtr = new stateLineLoop(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 4-state: TRIANGLES
    statePtr = new stateTriangles(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 5-state: TRIANGLE_STRIP
    statePtr = new stateTriangleStrip(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 6-state: TRIANGLE_STRIP_FAN
    statePtr = new stateTriangleFan(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 7-state: TRIANGLE_QUADS
    statePtr = new stateQuads(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 8-state: TRIANGLE_QUADS_STRIP
    statePtr = new stateQuadsStrip(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 9-state: POLYGON
    statePtr = new statePolygon(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 0-test: SCISSOR
    statePtr = new stateScissor(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    // Create widgets for 1-test: ALPHA
    statePtr = new stateAlpha(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));
    
    // Create widgets for 2-test: BLEND
    statePtr = new stateBlend(this);
    primitiveTypeStates.push_back(std::unique_ptr<State>(statePtr));

    end();
    changePrimitive(currentType);
}

void AppWindow::changePrimitive_CB(Fl_Widget* w, void* appWinPtr){
    Fl_Choice* widget = dynamic_cast<Fl_Choice*>(w);
    AppWindow* app_win = static_cast<AppWindow*>(appWinPtr);
    assert(widget != nullptr);
    app_win->changePrimitive(static_cast<PrimitiveType>(widget->value()));
}

void AppWindow::changePrimitive(PrimitiveType type){
    makeCurrentWidgetsInvisiable();
    setCurrentPrimitiveType(type);
    makeCurrentWidgetsVisiable();
    glSubWin->drawPrimitive(type, primitiveTypeStates.at(static_cast<int>(currentType)).get());
}

void AppWindow::update(bool regenerate){
    glSubWin->drawPrimitive(currentType, primitiveTypeStates.at(static_cast<int>(currentType)).get(), regenerate);
}

void AppWindow::makeCurrentWidgetsInvisiable(){
    primitiveTypeStates.at(static_cast<int>(currentType))->hideWidgets();
}

void AppWindow::makeAllWidgetsInvisible(){
    for (auto &state : primitiveTypeStates)
        state->hideWidgets();
}

void AppWindow::setCurrentPrimitiveType(PrimitiveType type){
    currentType = type;
}

void AppWindow::makeCurrentWidgetsVisiable(){
    primitiveTypeStates.at(static_cast<int>(currentType)).get()->showWidgets();
    auto newHeight = primitiveTypeStates.at(static_cast<int>(currentType)).get()->getNeededParentBoxHeight();
    box_upper->resize(box_upper->x(), box_upper->y(), box_upper->w(), newHeight);
}