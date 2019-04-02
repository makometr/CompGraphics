#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H,const char*L)
    : Fl_Gl_Window(X,Y,W,H,L)
{
    end();
    U = new double[m+1+9];
    // points = new double[pointsNum];
    controlPoints = new glm::vec2[n];
    auto step = 1.0 / m;
    std::cout << "U: ";
    for (size_t i = 0; i <= m; i++){
        U[i] = step * i;
        std::cout << U[i] << " ";
    }
    for (size_t i = m+1; i < m+9; i++){
        U[i] = 1;
        // std::cout << U[i] << " ";
    }
    // U[0] = -1.0f;
    std::cout << "\n";

    // for (size_t i = 0; i < pointsNum; i++){
    //     points[i] = std::sqrt((double)i/100);
    //     std::cout << points[i] << " ";
    // }
    controlPoints[0] = {125.0,125.0};
    controlPoints[1] = {375.0,125.0};
    controlPoints[2] = {375.0,375.0};
    // controlPoints[3] = {125.0,375.0};
    // controlPoints[4] = {125.0,125.0};
    // controlPoints[5] = {375.0,125.0};
    // controlPoints[6] = {375.0,375.0};
    // controlPoints[7] = {125.0,375.0};
    // controlPoints[8] = {50.0,125.0};

    // controlPoints[0] = {50.0,100.0};
    // controlPoints[1] = {500.0,0.0};
    // controlPoints[2] = {500.0,500.0};
    // controlPoints[3] = {0.0,500.0};
    // controlPoints[4] = {0.0,0.0};
    // controlPoints[5] = {250.0,250.0};
    // controlPoints[6] = {500.0,0.0};
    // controlPoints[7] = {250.0,250.0};
    // controlPoints[8] = {500.0,500.0};
}

GlSubWin::~GlSubWin(){
    delete [] U;
    // delete [] points;
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
    glPolygonMode(GL_QUADS, GL_POINT);

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3);
    glColor3f(0,0,0);
    // glBegin(GL_LINES);
    //     glVertex2f(w()/2, h());
    //     glVertex2f(w()/2, 0);
    //     glVertex2f(0, h()/2);
    //     glVertex2f(w(), h()/2);
    // glEnd();
    
    // glBegin(GL_POINTS);
    // for (int i = 0; i < pointsNum; i++){
    //     glVertex2d(i/2, points[i]*100/2);
    // }
    // glEnd();

    // glBegin(GL_LINES);
    // for(size_t i = 0; i < pointsNum; ++i) {
    //     glVertex2d(1.0/pointsNum*i*w(), N(1, 2, 1.0/pointsNum*i)*h()); // TODO: Make i and p of N changable to see it's effect on result
    //     glVertex2d(1.0/pointsNum*(i+1)*w(), N(1, 2, 1.0/pointsNum*(i+1))*h());
    // }
    // glEnd();

    // for (int i_i = 1; i_i < 4; i_i++){
    glPointSize(5);
    glBegin(GL_POINTS);
    for(size_t i = 0; i <= m; ++i) {
        glVertex2d(1.0/m*i*w(), 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
        for(size_t i = 0; i < pointsNum; ++i) {
            glVertex2d(1.0/pointsNum*i*w(), N(0, 3, 1.0/pointsNum*i)*h()); // TODO: Make i and p of N changable to see it's effect on result
            glVertex2d(1.0/pointsNum*(i+1)*w(), N(0, 3, 1.0/pointsNum*(i+1))*h());
        }
    glEnd();
    // }
    glBegin(GL_POINTS);
    for(size_t i = 0; i < n; ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    for(size_t i = 0; i < n-1; ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
        glVertex2f(controlPoints[i+1].x, controlPoints[i+1].y);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(1.0f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for(size_t i = 0; i < pointsNum; ++i) {
        glm::vec2 p1 = C(3, 1.0/pointsNum*i),
                  p2 = C(3, 1.0/pointsNum*(i+1));
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);            
    }
    glEnd();

}

void GlSubWin::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    redraw();
}


float GlSubWin::N(int i, int p, double u){ // i номер,  p - степень
    if (p == 0){
        if (U[i] <= u && u < U[i+1])
            return 1;
        else 
            return 0;
    }
    return (u - U[i]) / (U[i+p] - U[i]) * N(i, p-1, u) + (U[i+p+1] - u) / (U[i+p+1] - U[i+1]) * N(i+1, p-1, u);
}

glm::vec2 GlSubWin::C(int p, double u){ 
    glm::vec2 result{0.0f};
    for(size_t i = 0; i < n; ++i)  {
        result += N(i, p, u) * controlPoints[i];
        std::cout << "   " << result.x << " " << result.y << std::endl;
        std::cout << "       N(i, p, u) = " << N(i, p, u) << " " << i << " " << p << " " << u << std::endl;
    }
    std::cout << u << " " << result.x << " " << result.y << std::endl;
    return result;
}
