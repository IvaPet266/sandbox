#include <iostream>


class Control {
private:
    bool run           = true;
    bool ctrl_pressed  = false;
    bool space     = false;
    int  particle_code = 0;
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

    void set_particle_code(int new_code) {
        particle_code = new_code;
        std::cout<< particle_code << std::endl;
    }
    int get_particle_code() {
        return particle_code;
    }

    void set_space(bool new_flag) {
        space = new_flag;
        std::cout<< space << std::endl;
    }
    bool get_space() {
        return space;
    }


};

Control control = Control();