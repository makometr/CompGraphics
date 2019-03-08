#include "Painters.hpp"

RGB IPainter::Fl_Color_To_RGB(Fl_Color color) {
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    // std:: cout << "Color after conversation: "  << r << " " << g << " " << b << " " << "\n";
    return {r,g,b};
}

void IPainter::applyColor(ElemColor color){
    switch (color){
        case ElemColor::red:    glColor3f(1.0f, 0.0f, 0.0f); break;
        case ElemColor::green:  glColor3f(0.0f, 1.0f, 0.0f); break;
        case ElemColor::blue:   glColor3f(0.0f, 0.0f, 1.0f); break;
        case ElemColor::random: {
            auto r = static_cast<float>(std::rand() % 256) / 256;
            auto g = static_cast<float>(std::rand() % 256) / 256;
            auto b = static_cast<float>(std::rand() % 256) / 256;
            glColor3f(r,g,b); 
            break;
        }
        default: assert("Invalid switch statement!\n" == nullptr);
    }
}

void PointPainter::operator()(State* statePtr, bool redraw){
    statePoints* state = dynamic_cast<statePoints*>(statePtr);
    assert(state != nullptr);

    // background TODO invert color of points
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
    auto [r_part,g_part,b_part] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r_part/255, g_part/255, b_part/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // length
    LineLength choosedLength = state->getLength();
    int length = 0;
    switch (choosedLength){
        case LineLength::small:  length = 200; break;
        case LineLength::middle: length = 350; break;
        case LineLength::large:  length = 500; break;
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    //color
    ElemColor choosedColor = state->getElemColor();
    applyColor(choosedColor);

    size_t number = state->getPointsNumber();
    number % 2 == 1 ? number-- : number;
    while (number > 0){
        glBegin(GL_LINES);
            if (choosedColor == ElemColor::random) applyColor(choosedColor);
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
    ElemColor choosedColor = state->getElemColor();
    applyColor(choosedColor);

    size_t number = state->getPointsNumber();
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


void LineLoopPainter::operator()(State* statePtr, bool redraw){
    stateLineLoop* state = dynamic_cast<stateLineLoop*>(statePtr);
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
    ElemColor choosedColor = state->getLoopColor();
    applyColor(choosedColor);

    size_t number = state->getPointsNumber();
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


void TrianglesPainter::operator()(State* statePtr, bool redraw){
    stateTriangles* state = dynamic_cast<stateTriangles*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [color_1, color_2, color_3] = state->getTripleElemColor();
    size_t number = state->getPointsNumber();
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < number; i++){
             if (i % 3 == 0) applyColor(color_1);
        else if (i % 3 == 1) applyColor(color_2);
        else if (i % 3 == 2) applyColor(color_3);

        auto x = std::rand() % 500;
        auto y = std::rand() % 500;
        glVertex2f(x,y);
    }
    glEnd();
}

void TriangleStripPainter::operator()(State* statePtr, bool redraw){
    stateTriangleStrip* state = dynamic_cast<stateTriangleStrip*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [color_1, color_2, color_3] = state->getTripleElemColor();
    size_t number = state->getPointsNumber();
    glBegin(GL_TRIANGLE_STRIP);
    for (size_t i = 0; i < number; i++){
             if (i % 3 == 0) applyColor(color_1);
        else if (i % 3 == 1) applyColor(color_2);
        else if (i % 3 == 2) applyColor(color_3);

        auto x = std::rand() % 500;
        auto y = std::rand() % 500;
        glVertex2f(x,y);
    }
    glEnd();
}

void TriangleFanPainter::operator()(State* statePtr, bool redraw){
    stateTriangleFan* state = dynamic_cast<stateTriangleFan*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [color_1, color_2, color_3] = state->getTripleElemColor();
    size_t number = state->getPointsNumber();
    glBegin(GL_TRIANGLE_FAN);
    for (size_t i = 0; i < number; i++){
             if (i % 3 == 0) applyColor(color_1);
        else if (i % 3 == 1) applyColor(color_2);
        else if (i % 3 == 2) applyColor(color_3);

        auto x = std::rand() % 500;
        auto y = std::rand() % 500;
        glVertex2f(x,y);
    }
    glEnd();
}

void QuadsPainter::operator()(State* statePtr, bool redraw){

}

void QuadStripPainter::operator()(State* statePtr, bool redraw){

}

void PolygonPainter::operator()(State* statePtr, bool redraw){

}