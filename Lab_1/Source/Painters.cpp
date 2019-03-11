#include "Painters.hpp"

RGB IPainter::Fl_Color_To_RGB(Fl_Color color) {
    unsigned rgb = (unsigned)fl_color_average(color, FL_WHITE, 1.0);
    unsigned r = rgb>> 24 & 255;
    unsigned g = rgb>> 16 & 255;
    unsigned b = rgb>> 8 & 255;
    // std:: cout << "Color after conversation: "  << r << " " << g << " " << b << " " << "\n";
    return {r,g,b};
}

void IPainter::applyColor(ElemColor color, double alpha){
    switch (color){
        case ElemColor::red:    glColor4f(1.0f, 0.0f, 0.0f, alpha); break;
        case ElemColor::green:  glColor4f(0.0f, 1.0f, 0.0f, alpha); break;
        case ElemColor::blue:   glColor4f(0.0f, 0.0f, 1.0f, alpha); break;
        case ElemColor::random: {
            auto r = static_cast<float>(std::rand() % 256) / 256;
            auto g = static_cast<float>(std::rand() % 256) / 256;
            auto b = static_cast<float>(std::rand() % 256) / 256;
            glColor4f(r,g,b, alpha); 
            break;
        }
        default: assert("Invalid switch statement!\n" == nullptr);
    }
}

void PointPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    statePoints* state = dynamic_cast<statePoints*>(statePtr);
    assert(state != nullptr);

    // background TODO invert color of points
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    size_t number = state->getPointsNumber();
    GLdouble center_x = winWidth / 2;
    GLdouble center_y = winHeight / 2;
    PointPlacement placement = state->getPlacementType();
    switch (placement){
        case PointPlacement::circle: {
            GLdouble r = std::min(winHeight, winWidth)/2 - 50;
            glBegin(GL_POINTS);
                glColor3f(0.0f, 1.0f, 0.0f); 
                for (size_t n = 0; n < number; ++n) {
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
            glBegin(GL_POINTS);
            for (size_t i = 0; i < number; i++){
                int side = rand() % 4;
                GLdouble pos = (std::rand() % (int)edge) - edge / 2;
                int x = center_x;
                int y = center_y;
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
                    glVertex2d(x, y);
            }
            glEnd();
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

void LinePainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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
        case LineLength::small:  length = 0.45 * std::min(winWidth, winHeight); break;
        case LineLength::middle: length = 0.70 * std::min(winWidth, winHeight); break;
        case LineLength::large:  length = 1.00 * std::min(winWidth, winHeight); break;
        default: assert("Invalid switch statement!\n" == nullptr);
    }

    //color
    ElemColor choosedColor = state->getElemColor();
    applyColor(choosedColor);

    // width
    glLineWidth(2);

    size_t number = state->getPointsNumber();
    number % 2 == 1 ? number-- : number;
    while (number > 0){
        glBegin(GL_LINES);
            if (choosedColor == ElemColor::random) applyColor(choosedColor);
            auto x_1 = winWidth / 2;
            auto y_1 = winHeight / 2;
            glVertex2d(x_1, y_1);
            auto x_2 = (std::rand() % length) - length / 2 + x_1;
            auto y_2 = (std::rand() % length) - length / 2 + y_1;
            glVertex2d(x_2, y_2);
        glEnd();
        number -= 2;
    }
}

void LineStripPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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
        case LineLength::small:  length = 0.30 * std::min(winWidth, winHeight); break;
        case LineLength::middle: length = 0.45 * std::min(winWidth, winHeight); break;
        case LineLength::large:  length = 0.60 * std::min(winWidth, winHeight); break;
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


void LineLoopPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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
        case LineLength::small:  length = 0.30 * std::min(winWidth, winHeight); break;
        case LineLength::middle: length = 0.45 * std::min(winWidth, winHeight); break;
        case LineLength::large:  length = 0.60 * std::min(winWidth, winHeight); break;
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


void TrianglesPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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

        auto x = std::rand() % winWidth;
        auto y = std::rand() % winHeight;
        glVertex2f(x,y);
    }
    glEnd();
}

void TriangleStripPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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

        auto x = std::rand() % winWidth;
        auto y = std::rand() % winHeight;
        glVertex2f(x,y);
    }
    glEnd();
}

void TriangleFanPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
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

        auto x = std::rand() % winWidth;
        auto y = std::rand() % winHeight;
        glVertex2f(x,y);
    }
    glEnd();
}

void QuadsPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    stateQuads* state = dynamic_cast<stateQuads*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [color_1, color_2, color_3, color_4] = state->getTetradColor();
    size_t number = state->getPointsNumber();
    glBegin(GL_QUADS);
    for (size_t i = 0; i < number; i++){
             if (i % 4 == 0) applyColor(color_1);
        else if (i % 4 == 1) applyColor(color_2);
        else if (i % 4 == 2) applyColor(color_3);
        else if (i % 4 == 3) applyColor(color_4);

        auto x = std::rand() % winWidth;
        auto y = std::rand() % winHeight;
        glVertex2f(x,y);
    }
    glEnd();
}

void QuadStripPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    stateQuadsStrip* state = dynamic_cast<stateQuadsStrip*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [color_1, color_2, color_3, color_4] = state->getTetradColor();
    size_t number = state->getPointsNumber();
    glBegin(GL_QUAD_STRIP);
    for (size_t i = 0; i < number; i++){
             if (i % 4 == 0) applyColor(color_1);
        else if (i % 4 == 1) applyColor(color_2);
        else if (i % 4 == 2) applyColor(color_3);
        else if (i % 4 == 3) applyColor(color_4);

        auto x = std::rand() % winWidth;
        auto y = std::rand() % winHeight;
        glVertex2f(x,y);
    }
    glEnd();
}

void PolygonPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    statePolygon* state = dynamic_cast<statePolygon*>(statePtr);
    assert(state != nullptr);  

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    ElemColor color = state->getElemColor();
    size_t pointsNumber = state->getPointsNumber();
    GLdouble circleInterval = 360 / pointsNumber;
    GLdouble begin = 0;

    glBegin(GL_POLYGON);
    for (size_t i = 0; i < pointsNumber; i++){
        GLdouble angle = (GLdouble)(std::rand() % (int)circleInterval * 10) / 10 + begin;
        GLdouble x = (GLdouble)(std::rand() % (winWidth / 2 - 50) + 50) * std::cos(angle) + winWidth / 2;
        GLdouble y = (GLdouble)(std::rand() % (winHeight / 2 - 50) + 50) * std::sin(angle) + winWidth / 2;
        applyColor(color);
        glVertex2f(x,y);
        begin += circleInterval;
    }
    glEnd();
}



void ScissorPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    stateScissor* state = dynamic_cast<stateScissor*>(statePtr);
    assert(state != nullptr);

    // bkg color
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glScissor(state->getX(),
              state->getY(),
              state->getWidth(),
              state->getHeight()
    );

    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(6);
    glBegin(GL_LINES);
        glColor4f(0, 0, 1, 0.4);
        glVertex2f(0, 0);
        glColor4f(0, 0, 1, 1);
        glVertex2f(500, 500);
        glVertex2f(500, 0);
        glColor4f(0, 0, 1, 0.4);
        glVertex2f(0, 500);
    glEnd();
}

void AlphaPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    stateAlpha* state = dynamic_cast<stateAlpha*>(statePtr);
    assert(state != nullptr);

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    GLdouble alpha = (GLdouble)state->getAlpha() / 100;
    GLdouble alphaLower = (GLdouble)state->getLowerAlpha() / 100;
    GLdouble alphaUpper = (GLdouble)state->getUpperAlpha() / 100;
    glAlphaFunc(state->getParameter(), alpha);

    glBegin(GL_QUADS);
        IPainter::applyColor(state->getLowerColor(), alphaLower);
        glVertex2f(10, 10);
        glVertex2f(400, 10);
        IPainter::applyColor(state->getUpperColor(), alphaUpper);
        glVertex2f(490, 490);
        glVertex2f(100, 490);
    glEnd();
}

void BlendPainter::operator()(State* statePtr, int winWidth, int winHeight, bool redraw){
    stateBlend* state = dynamic_cast<stateBlend*>(statePtr);
    assert(state != nullptr);

    // bkg color
    auto [r,g,b] = IPainter::Fl_Color_To_RGB(state->getBkgColor());
    glClearColor(r/255, g/255, b/255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // blend
    glBlendFunc(state->getSFactor(), state->getDFactor());

    // circles
    GLdouble pi     = acos(-1.0);
    GLdouble radius = 100.0;
    GLdouble step   = 0.01;
    GLdouble theta;

    // 1
    glBegin(GL_TRIANGLE_FAN);
    for (GLfloat a = 0.0; a < 360.0; a += step) {
        theta = 2.0 * pi * a / 180.0;
        IPainter::applyColor(ElemColor::red);
        glVertex3f(radius * cos(theta) + 175, radius * sin(theta)+300, 0.0f);
    }
    glEnd();

    // 2
    glBegin(GL_TRIANGLE_FAN);
    for (GLfloat a = 0.0; a < 360.0; a += step) {
        theta = 2.0 * pi * a / 180.0;
        IPainter::applyColor(ElemColor::green);
        glVertex3f(radius * cos(theta) + 325, radius * sin(theta)+300, 0.0f);
    }
    glEnd();

    // 3
    glBegin(GL_TRIANGLE_FAN);
    for (GLfloat a = 0.0; a < 360.0; a += step) {
        theta = 2.0 * pi * a / 180.0;
        IPainter::applyColor(ElemColor::blue);
        glVertex3f(radius * cos(theta) + 250, radius * sin(theta)+175, 0.0f);
    }
    glEnd();
}