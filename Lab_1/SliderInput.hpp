#include "libs.hpp"

class SliderInput : public Fl_Group {
private:
    Fl_Int_Input *input;
    Fl_Slider *slider;

public:
    SliderInput(int x, int y, int w, int h, const char *l);
    int  value() const;
    void value(int val);

    void minumum(int val);
    int  minumum() const;

    void maximum(int val);
    int  maximum() const;

    void bounds(int low, int high);

private:
    void Slider_CB2();
    static void Slider_CB(Fl_Widget *w, void *data);
    void Input_CB2();
    static void Input_CB(Fl_Widget *w, void *data);
};