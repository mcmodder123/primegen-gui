#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <cmath>
#include <stdexcept>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <math.h>


bool isPrime(int num){
    if (num == 2) return 1;
    if (num <= 1) return 0;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}



void find(Fl_Widget *widget, void *data) {
    Fl_Box *box = (Fl_Box *)widget;
    Fl_Input *inputField = (Fl_Input *)data;

    Fl::check();

    const char *input_val = inputField->value();
    std::string input_str(input_val ? input_val : "");

    if (input_str.empty()) {
        box->label("Please enter a number");
        box->redraw();
        return;
    }


    try{
        int iterations = std::stoi(input_str);

        if (iterations <= 0) {
            box->label("Please enter a positive number");
            box->redraw();
            return;
        }

        int starting_num = 1;
        for (int n = 0; n < iterations;) {
            if (isPrime(starting_num)) {
                std::string num = std::to_string(starting_num);
                box->label(num.c_str());
                box->redraw();
                Fl::check();
                n++;
            }
            starting_num++;
        }
        box->redraw();
    }
    catch(const std::out_of_range &e){
        box->label("Too high of a number.");
        box->redraw();
    }
    catch(const std::invalid_argument &e){
        box->label("Please enter a number");
        box->redraw();
    }
}

int main(int argc, char **argv){
    Fl_Window *window = new Fl_Window(300, 180, "Prime number finder");
    Fl_Box *box = new Fl_Box(FL_DOWN_BOX, 20, 20, 260, 30, "Nth prime number to find:");
    Fl_Button *btn1 = new Fl_Button(70, 120, 150, 30, "Find Prime Number");
    Fl_Input *inputField = new Fl_Input(95, 70, 100, 30);
    btn1->callback(find, inputField);

    window->show();
    return Fl::run();
}
