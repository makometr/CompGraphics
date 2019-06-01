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
    statePtr->badAllocOff();
    glPolygonMode(GL_FRONT, GL_LINE);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    applyColor(statePtr->getElemColor());

    sideLength = (GLdouble)statePtr->getLength();
    std::vector<glm::vec2> figureVertices = {
        { -sideLength,  sideLength*0.7f},
        { sideLength,  sideLength*0.7f},
        { sideLength, -sideLength*0.7f},
        {-sideLength, -sideLength*0.7f}
    };
    std::vector<glm::vec2> downRect;
    for (auto &point : figureVertices)
        downRect.push_back({point.x+sideLength*0.03, point.y-sideLength*0.7f*1.5});

    std::vector<glm::vec2> rotatedRect;
    glm::mat4 transformMatrix = glm::mat4(1.0); // Единичная матрица.
    transformMatrix = glm::translate(transformMatrix, glm::vec3(-sideLength*1.1, 0, 0)); // Третье
    transformMatrix = glm::rotate(transformMatrix, glm::radians(60.0f), glm::vec3(0.0f,0.0f,1.0f));
    for (auto &point : figureVertices){
        auto tmp = (transformMatrix * glm::vec4(point, 0.0f, 1.0f));
        rotatedRect.push_back({tmp.x+sideLength*0.03, tmp.y-sideLength*0.7f*1.5});
    }
    transformMatrix = glm::mat4(1.0); // Единичная матрица.
    transformMatrix = glm::translate(transformMatrix, glm::vec3(sideLength*1.05, sideLength*0.1, 0)); // Третье
    transformMatrix = glm::rotate(transformMatrix, glm::radians(-60.0f), glm::vec3(0.0f,0.0f,1.0f));
    for (auto &point : figureVertices){
        auto tmp = (transformMatrix * glm::vec4(point, 0.0f, 1.0f));
        rotatedRect.push_back({tmp.x+sideLength*0.03, tmp.y-sideLength*0.7f*1.5});
    }
    std::vector<glm::vec2> smallRect = {
        { -sideLength*0.1, -1.6*sideLength},
        {  sideLength*0.1, -1.62*sideLength},
        {  sideLength*0.1, -2.12*sideLength},
        { -sideLength*0.1, -2.1*sideLength}
    };

    figureVertices.insert(figureVertices.end(), downRect.begin(), downRect.end());
    figureVertices.insert(figureVertices.end(), rotatedRect.begin(), rotatedRect.end());
    figureVertices.insert(figureVertices.end(), smallRect.begin(), smallRect.end());

    transformMatrix = glm::mat4(1.0); // Единичная матрица.
    transformMatrix = glm::translate(transformMatrix, glm::vec3(0, sideLength/2, 0));
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0/2.4, 1.0/2.4, 1.0/2.4));
    for (auto& i : figureVertices)
        i = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
    
    try {
        Fractal(figureVertices, statePtr->getDeep());
    }
    catch (const std::bad_alloc&) {
        statePtr->badAllocOn();
        return;
    }
}

void GlSubWin::Fractal(std::vector<glm::vec2> &verteces, int deep){
    if (deep == 0){
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(w()/2, h()/2, 0.0f));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_QUADS);
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
    auto center = verteces;
    verteces.clear();

    figureLeft(left);
    verteces.insert(std::end(verteces), std::begin(left), std::end(left));
    left.clear();
    left.shrink_to_fit();

    figureRight(right);
    verteces.insert(std::end(verteces), std::begin(right), std::end(right)); 
    right.clear();
    right.shrink_to_fit();

    figureCenter(center);
    verteces.insert(std::end(verteces), std::begin(center), std::end(center));
    center.clear();
    center.shrink_to_fit();
    Fractal(verteces, deep-1);
}

void GlSubWin::figureCenter(std::vector<glm::vec2> &verteces){
    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(0, -sideLength*0.1, 0)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(0.7, 0.7, 0.7)); // First
    for (auto& i : verteces)
        i = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
    
    std::vector<glm::vec2> down;
    transformMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, sideLength*0.5, 0)); // Second
    for (const auto& i : verteces){
        auto newPoint = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        down.push_back(newPoint);
    }
    verteces.insert(std::end(verteces), std::begin(down), std::end(down));
    down.clear();
    down.shrink_to_fit();
}

void GlSubWin::figureLeft(std::vector<glm::vec2> &verteces){
    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(-sideLength/3.5, -sideLength/4, 0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(60.0f), glm::vec3(0.0f,0.0f,1.0f));
    transformMatrix = glm::scale(transformMatrix, glm::vec3(0.7, 0.7, 0.7));

    for (auto& i : verteces)
        i = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
}

void GlSubWin::figureRight(std::vector<glm::vec2> &verteces){ 
    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(sideLength/3.5, -sideLength/4, 0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(-60.0f), glm::vec3(0.0f,0.0f,1.0f));
    transformMatrix = glm::scale(transformMatrix, glm::vec3(0.7, 0.7, 0.7));

    for (auto& i : verteces)
        i = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
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