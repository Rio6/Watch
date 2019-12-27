#ifndef SWMODE_H
#define SWMODE_H

#include "Mode.hpp"

class SWMode : public Mode {
    public:
        bool display();

    private:
        // if not running then this is elapsed time, else it's start time
        unsigned long time = 0;
        bool running = false;

        void draw();
};

#endif
