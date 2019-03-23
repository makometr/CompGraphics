#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H, State* state, const char*L)
    : Fl_Gl_Window(X,Y,W,H,L), statePtr(state)
{
    end();
    // primitives
}

GlSubWin::~GlSubWin(){
}

void GlSubWin::FixViewport(int W,int H) {
    glViewport(0,0,W,H);
    glOrtho(0,W,0,H,-1,1);
}

void GlSubWin::draw() {
    if (!valid()){ // first time? init
        valid(1);
        FixViewport(w(), h());
    }
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_LINES);
    //     glVertex2d(0,0);
    //     glVertex2d(500,500);
    //     glVertex2d(500, 0);
    //     glVertex2d(0,500);
    // glEnd();

    // L = 100
    std::vector<glm::vec2> triangleVertices = {
        { 0,  100},
        {-100, -100},
        { 100, -100}
    };
    // glm::mat4 trans = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f)), glm::vec3(statePtr->getAngle(), -statePtr->getAngle(), 0.0f));
    glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(statePtr->getAngle(), statePtr->getAngle(), 0.0f));

    std::vector <glm::vec2> center = triangleVertices;
    std::vector <glm::vec2> left = triangleVertices;
    std::vector <glm::vec2> right = triangleVertices;

    figureCenter(center, 10);
    figureLeft(left, 10);
    figureRight(right, 10);

    std::vector <glm::vec2> resultedVerteces;
    resultedVerteces.reserve(center.size() + left.size() + right.size());
    resultedVerteces.insert(std::end(resultedVerteces), std::begin(center), std::end(center));
    resultedVerteces.insert(std::end(resultedVerteces), std::begin(left), std::end(left));
    resultedVerteces.insert(std::end(resultedVerteces), std::begin(right), std::end(right));

    glBegin(GL_TRIANGLES);
        for (auto &i :resultedVerteces){
            auto tmp = (trans * glm::vec4(i, 0.0f, 1.0f));
            i.x = tmp.x;
            i.y = tmp.y;
            glVertex2d(i.x, i.y);
            std::cout << i.x << " " << i.y << "\n";
        }
    glEnd();

    glPolygonMode(GL_FRONT, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);

    glMatrixMode(GL_MODELVIEW);

    // glPushMatrix();
    //     glTranslated(250, 250, 0);
    //     glDrawArrays(GL_TRIANGLES, 0, 3);
    //     GLfloat mat[16];
    //     glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    // glPopMatrix();

    // figureCenter(3);

    // glPushMatrix();
    //     glTranslated(250, 250, 0);
    //     glTranslated(-150/3, 150/3 , 0);
    //     glScaled(1.0/3, 1,1);
    //     glRotatef(90, 0.0f, 0.0f, 1.0f);
    //     // glRotatef(statePtr->getAngle(), 0.0f, 0.0f, 1.0f);
    //     glDrawArrays(GL_TRIANGLES, 0, 3);
    // glPopMatrix();


    glDisableClientState(GL_VERTEX_ARRAY);

}

void GlSubWin::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    redraw();
}

void GlSubWin::figureCenter(std::vector<glm::vec2> &verteces, int deep, int cur){
    if (deep - cur == 0) return;

    glm::mat4 transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(0, 100*2/3, 0)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0/3, 1.0/3, 1)); // First

    for (auto& i : verteces) {
        auto tmp = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        i.x = tmp.x;
        i.y = tmp.y;
    }
}

void GlSubWin::figureLeft(std::vector<glm::vec2> &verteces, int deep, int cur){
    if (deep - cur == 0) return;

    glm::mat4 transformMatrix = glm::mat4(1.0);

    transformMatrix = glm::translate(transformMatrix, glm::vec3(-100*2/3, 0, 0)); // Third
    transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f)); // Second
    transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0, 1.0/3, 1.0)); // First

    for (auto& i : verteces) {
        auto tmp = (transformMatrix * glm::vec4(i, 0.0f, 1.0f));
        i.x = tmp.x;
        i.y = tmp.y;
    }
}

void GlSubWin::figureRight(std::vector<glm::vec2> &verteces, int deep, int cur){
    if (deep - cur == 0) return;

    glm::mat4 transformMatrix = glm::mat4(1.0);

    transformMatrix = glm::translate(transformMatrix, glm::vec3(100*2/3, 0, 0)); // Third
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