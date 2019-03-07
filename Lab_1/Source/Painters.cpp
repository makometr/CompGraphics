#include "Painters.hpp"

RGB IPainter::Fl_Color_To_RGB(Fl_Color color) {
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    // std:: cout << "Color after conversation: "  << r << " " << g << " " << b << " " << "\n";
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
        default: assert("Invalid switch statement!\n" == nullptr);
    }

}

void LinePainter::operator()(State* statePtr, bool redraw){
    stateLines* state = dynamic_cast<stateLines*>(statePtr);
    assert(state != nullptr);

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // length
    LineLength choosedLength = state->getLength();
    int length = 0;
    switch (choosedLength){
        case LineLength::small:  length = 150; break;
        case LineLength::middle: length = 300; break;
        case LineLength::large:  length = 400; break;
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    //color
    LineColor choosedColor = state->getLineColor();
    switch (choosedColor){
        case LineColor::red:    glColor3f(1.0f, 0.0f, 0.0f); break;
        case LineColor::green:  glColor3f(0.0f, 1.0f, 0.0f); break;
        case LineColor::blue:   glColor3f(0.0f, 0.0f, 1.0f); break;
        case LineColor::random: {
            auto r = static_cast<float>(std::rand() % 256) / 256;
            auto g = static_cast<float>(std::rand() % 256) / 256;
            auto b = static_cast<float>(std::rand() % 256) / 256;
            glColor3f(r,g,b); 
            break;
        }
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    size_t number = state->getPointsNumber();
    number % 2 == 1 ? number-- : number;
    while (number > 0){
        glBegin(GL_LINES);
            // auto x_1 = std::rand() % 500;
            // auto y_1 = std::rand() % 500;
            auto x_1 = 250;
            auto y_1 = 250;
            glVertex2d(x_1, y_1);
            auto x_2 = (std::rand() % length) - length / 2 + x_1;
            auto y_2 = (std::rand() % length) - length / 2 + y_1;
            glVertex2d(x_2, y_2);
        glEnd();
        number -= 2;
    }
}

void LineStripPainter::operator()(State* statePtr, bool redraw){
    stateLineStrips* state = dynamic_cast<stateLineStrips*>(statePtr);
    assert(state != nullptr);

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // length
    LineLength choosedLength = state->getLength();
    int length = 0;
    switch (choosedLength){
        case LineLength::small:  length = 150; break;
        case LineLength::middle: length = 300; break;
        case LineLength::large:  length = 400; break;
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    //color
    LineColor choosedColor = state->getLineColor();
    switch (choosedColor){
        case LineColor::red:    glColor3f(1.0f, 0.0f, 0.0f); break;
        case LineColor::green:  glColor3f(0.0f, 1.0f, 0.0f); break;
        case LineColor::blue:   glColor3f(0.0f, 0.0f, 1.0f); break;
        case LineColor::random: {
            auto r = static_cast<float>(std::rand() % 256) / 256;
            auto g = static_cast<float>(std::rand() % 256) / 256;
            auto b = static_cast<float>(std::rand() % 256) / 256;
            glColor3f(r,g,b); 
            break;
        }
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    size_t number = state->getPointsNumber();
    // number % 2 == 1 ? number-- : number;
    glBegin(GL_LINE_STRIP);
    auto prev_x = std::rand() % 500;
    auto prev_y = std::rand() % 500;
    glVertex2d(prev_x, prev_y);
    while (number > 1){
            auto new_x = std::abs((std::rand() % length) - length / 2 + prev_x);
            auto new_y = std::abs((std::rand() % length) - length / 2 + prev_y);
            prev_x = new_x;
            prev_y = new_y;
            glVertex2d(new_x, new_y);
        number -= 1;
    }
    glEnd();
}