#include "SliderInput.hpp"

SliderInput::SliderInput(int x, int y, int w, int h, const char *l=0)
    : Fl_Group(x,y,w,h,l)
{
    int in_w = 40;
    input  = new Fl_Int_Input(x, y, in_w, h);
    input->callback(Input_CB, (void*)this);
    input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);

    slider = new Fl_Slider(x+in_w, y, w-in_w, h);
    slider->type(1);
    slider->callback(Slider_CB, (void*)this);

    bounds(1, 10);     // some usable default
    value(5);          // some usable default
    end();             // close the group
}

// MINIMAL ACCESSORS --  Add your own as needed
int SliderInput::value() const {
    return ((int)(slider->value() + 0.5));
}

void SliderInput::value(int val){
    slider->value(val);
    Slider_CB2();
}

void SliderInput::minumum(int val) {
    slider->minimum(val);
}

int SliderInput::minumum() const {
    return((int)slider->minimum());
}

void SliderInput::maximum(int val) {
    slider->maximum(val);
}

int SliderInput::maximum() const {
    return((int)slider->maximum());
}

void SliderInput::bounds(int low, int high){
    slider->bounds(low, high);
}


// CALLBACK HANDLERS
void SliderInput::Slider_CB2() {
    static int recurse = 0;
    if ( recurse ) { 
        return;
    } else {
        recurse = 1;
        char s[80];
        sprintf(s, "%d", (int)(slider->value() + .5));
        // fprintf(stderr, "SPRINTF(%d) -> '%s'\n", (int)(slider->value()+.5), s);
        input->value(s); // pass slider's value to input
        recurse = 0;
    }
}

void SliderInput::Slider_CB(Fl_Widget *w, void *data) {
    ((SliderInput*)data)->Slider_CB2();
}

void SliderInput::Input_CB2() {
    static int recurse = 0;
    if ( recurse ) {
        return;
    } else {
        recurse = 1;
        int val = 0;
        if ( sscanf(input->value(), "%d", &val) != 1 ) {
            val = 0;
            std::cout << "Error: not ba able to read value from input fl::Widget\n";
        }
        // check borders
        if (val > (int)slider->maximum()) val = (int)slider->maximum();
        if (val < (int)slider->minimum()) val = (int)slider->minimum();

        //set new value to input
        char s[80];
        sprintf(s, "%d", val);
        input->value(s);

        // pass input's value to slider
        slider->value(val);
        recurse = 0;
    }
}
void SliderInput::Input_CB(Fl_Widget *w, void *data) {
    ((SliderInput*)data)->Input_CB2();
}

