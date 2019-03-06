#include "Painters.hpp"

RGB IPainter::Fl_Color_To_RGB(Fl_Color color) {
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    std:: cout << "Color after conversation: "  << r << " " << g << " " << b << " " << "\n";
    return {r,g,b};
}

// PointPainter::PointPainter() : IPainter(), dis(0,360), gen(rd) {
//     // gen.seed(rd);   
// }

void PointPainter::operator()(State* statePtr, bool redraw){
    statePoints* state = dynamic_cast<statePoints*>(statePtr);
    assert(state != nullptr);

    // background
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    size_t number = state->getPointsNumber();
    std::cout << "NOW :" << number << "\n";
    GLdouble center_x = 500 / 2;
    GLdouble center_y = 500 / 2;
    PointPlacement placement = state->getPlacementType();
    switch (placement){
        case PointPlacement::circle: {
            GLdouble r = 200;
            // // std::random_device rd;  //Will be used to obtain a seed for the random number engine
            // // std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
            // std::default_random_engine gen;
            // // std::uniform_real_distribution<> dis(0.0, 360.0);
            // std::normal_distribution<> dis{120, 20};

            glBegin(GL_POINTS);
                glColor3f(0.0f, 1.0f, 0.0f); 
                for (size_t n = 0; n < number; ++n) {
                    // GLdouble angle = dis(gen);
                    GLdouble angle = (std::rand() % 3600) / 10;
                    auto x = r * std::cos(angle) + center_x;
                    auto y = r * std::sin(angle) + center_y;
                    glVertex2d(x, y);
            }
            glEnd();
            break;
        }
        case PointPlacement::rect: {
            GLdouble edge = 200;
            glColor3f(0.0f, 1.0f, 0.0f);
            for (size_t i = 0; i < number; i++){
                int side = rand() % 4;
                GLdouble pos = (std::rand() % (int)edge) - edge / 2;
                int y = center_x;
                int x = center_y;
                switch (side) {
                    case 0:
                        x += edge / 2;
                        y += pos;
                        break;
                    case 2:
                        x -= edge / 2;
                        y += pos;
                        break;
                    case 1:
                        x += pos;
                        y += edge / 2;
                        break;
                    case 3:
                        x += pos;                        
                        y -= edge / 2;
                        break;
                    default:
                        break;
                }
                glBegin(GL_POINTS);
                    glVertex2d(x, y);
                glEnd();
            }
        }
            break;
        case PointPlacement::normal: {
            glColor3f(0.0f, 1.0f, 0.0f);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> dis{250, 80};
            glBegin(GL_POINTS);
            for (size_t i = 0; i < number; i++){
                auto x = dis(gen);
                auto y = dis(gen);
                glVertex2d(x, y);
            }
            glEnd();
        }
            break;
        case PointPlacement::uniform: {
            glColor3f(0.0f, 1.0f, 0.0f);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, 500);
            glBegin(GL_POINTS);
            for (size_t i = 0; i < number; i++){
                auto x = dis(gen);
                auto y = dis(gen);
                glVertex2d(x, y);
            }
            glEnd();
        }
            break;
        default:
            break;
    }

}

void LinePainter::operator()(State* statePtr, bool redraw){
    stateLines* state = dynamic_cast<stateLines*>(statePtr);
    assert(state != nullptr);

    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor4f(1.0f,0.0f,1.0f, 0.6f);
        glVertex2f(20,30);
        glColor4f(0.0f,1.0f,0.0f, 0.6f);
        // glColor3ub(0,255,0);
        glVertex2f(20,40);
        glColor4f(1.0f,1.0f,0.0f, 0.6f);
        glVertex2f(40,40);
        glColor4f(0.0f,0.0f,1.0f, 0.6f);
        glVertex2f(40,30);
    glEnd();
}