#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H, State* state, const char*L)
    : Fl_Gl_Window(X,Y,W,H,L), statePtr(state)
{
    end();
}

GlSubWin::~GlSubWin(){
}

void GlSubWin::FixViewport(int W,int H) {
    glViewport(0,0,W,H);
    glOrtho(0,W,0,H,-1,1);
}

void GlSubWin::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    redraw();
}

void GlSubWin::draw() {
    if (!valid()){ // first time? init
        valid(1);
        FixViewport(w(), h());
    }
    glPolygonMode(GL_FRONT, GL_LINE);
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    applyColor(statePtr->getElemColor());

    sideLength = (GLdouble)statePtr->getLength();
    std::cout << statePtr->getLength() << "\n";
    std::vector<glm::vec2> triangleVertices = {
        { 0,  sideLength},
        {-sideLength, -sideLength},
        { sideLength, -sideLength}
    };
    try {
        Fractal(triangleVertices, statePtr->getDeep());
    }
    catch (const std::bad_alloc&) {
        statePtr->badAllocTrigger();
        return;
    }
}

void GlSubWin::Fractal(std::vector<glm::vec2> &verteces, int deep){
    if (deep == 0){
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(w()/2, h()/2, 0.0f));
        glBegin(GL_TRIANGLES);
            for (auto &i :verteces){
                auto tmp = (trans * glm::vec4(i, 0.0f, 1.0f));
                i.x = tmp.x;
                i.y = tmp.y;
                glVertex2d(i.x, i.y);
            }
        glEnd();
        return;
    }

    auto left = verteces;
    auto right = verteces;

    figureCenter(verteces); // instead of center
    figureLeft(left);
    figureRight(right);

    verteces.insert(std::end(verteces), std::begin(left), std::end(left));
    verteces.insert(std::end(verteces), std::begin(right), std::end(right));
    Fractal(verteces, deep-1);
}

void GlSubWin::figureCenter(std::vector<glm::vec2> &verteces){
    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(0, sideLength*2/3, 0)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0/3, 1.0/3, 1)); // First

    for (auto& i : verteces) {
        auto tmp = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        i.x = tmp.x;
        i.y = tmp.y;
    }
}

void GlSubWin::figureLeft(std::vector<glm::vec2> &verteces){
    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(-sideLength*2/3, 0, 0)); // Third
    transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0, 1.0/3, 1.0)); // First

    for (auto& i : verteces) {
        auto tmp = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        i.x = tmp.x;
        i.y = tmp.y;
    }
}

void GlSubWin::figureRight(std::vector<glm::vec2> &verteces){ 
    glm::mat4 transformMatrix = glm::mat4(1.0);

    transformMatrix = glm::translate(transformMatrix, glm::vec3(sideLength*2/3, 0, 0)); // Third
    transformMatrix = glm::rotate(transformMatrix, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0, 1.0/3, 1.0)); // First

    for (auto& i : verteces) {
        auto tmp = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        i.x = tmp.x;
        i.y = tmp.y;
    }
}

void GlSubWin::drawUpdated(){
    redraw();
}

void GlSubWin::applyColor(ElemColor color, double alpha){
    switch (color){
        case ElemColor::red:     glColor4f(1.0f, 0.0f, 0.0f, alpha); break;
        case ElemColor::green:   glColor4f(0.0f, 1.0f, 0.0f, alpha); break;
        case ElemColor::blue:    glColor4f(0.0f, 0.0f, 1.0f, alpha); break;
        case ElemColor::magneta: glColor4f(1.0f, 0.0f, 1.0f, alpha); break;
        case ElemColor::cyan :   glColor4f(0.0f, 1.0f, 1.0f, alpha); break;
        case ElemColor::yellow:  glColor4f(1.0f, 1.0f, 0.0f, alpha); break;
        case ElemColor::random: {
            auto r = static_cast<float>(std::rand() % 256) / 256;
            auto g = static_cast<float>(std::rand() % 256) / 256;
            auto b = static_cast<float>(std::rand() % 256) / 256;
            glColor4f(r,g,b, alpha); 
            break;
        }
        default: assert("Invalid switch statement!\n" == nullptr); break;
    }
}