#include <iostream>


class Control {
private:
    bool run = true;
    bool ctrl_pressed = false;
public:
    void set_run(bool new_flag) {
        run = new_flag;
    }
    bool get_run() {
        return run;
    }

    void set_ctrl(bool new_flag) {
        ctrl_pressed = new_flag;
        std::cout<< ctrl_pressed << std::endl;
    }
    bool get_ctrl() {
        return ctrl_pressed;
    }


};

Control control = Control();