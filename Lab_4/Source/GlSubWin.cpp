#include "GlSubWin.hpp"
#include "AppWin.hpp"

GlSubWin::GlSubWin(int X,int Y,int W,int H,State* state, const char*L)
    : Fl_Gl_Window(X,Y,W,H,L), statePtr(state)
{
    end();
    U = new double[m];
    // points = new double[pointsNum];
    controlPoints = new glm::vec2[n];
    std::cout << "U: ";
    // auto step = 1.0 / (m-p-p);
    // for (size_t i = 0; i <= p; ++i) {
    //     U[i] = 0.0;
    //     std::cout << U[i] << " ";
    // }
    // for (size_t i = p+1; i < m-p; i++){
    //     U[i] = step * (i-p);
    //     std::cout << U[i] << " ";
    // }
    // for (size_t i = m-p; i <= m; i++){
    //     U[i] = 1.0;
    //     std::cout << U[i] << " ";
    // }

    auto step = 1.0 / (m);
    for (size_t i = 0; i < m; i++){
        U[i] = step * i;
        std::cout << U[i] << " ";
    }
    // for (size_t i = m+1; i < m+9; i++){
    //     U[i] = 1;
    //     // std::cout << U[i] << " ";
    // }
    // U[0] = -1.0f;
    std::cout << "\n";

    // for (size_t i = 0; i < pointsNum; i++){
    //     points[i] = std::sqrt((double)i/100);
    //     std::cout << points[i] << " ";
    // }
    controlPoints[0] = {125.0,125.0};
    controlPoints[1] = {375.0,125.0};
    controlPoints[2] = {375.0,375.0};
    controlPoints[3] = {125.0,375.0};
    controlPoints[4] = {125.0,125.0};
    controlPoints[5] = {375.0,125.0};
    controlPoints[6] = {375.0,375.0};
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
        // std::cout << "   " << result.x << " " << result.y << std::endl;
        std::cout << "       N(i, p, u) = " << N(i, p, u) << " " << i << " " << p << " " << u << std::endl;
        // std::cout << "       controlPoints[i] = " << controlPoints[i].x << std::endl;
    }
    std::cout << u << " " << result.x << " " << result.y << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    return result;
}

void GlSubWin::drawUpdated(){
    redraw();
}