#ifndef SWMODE_H
#define SWMODE_H

#include "Mode.hpp"

class SWMode : public Mode {
    public:
        bool display();

    private:
        static const int NUM_LAPS = 20;
        unsigned long laps[NUM_LAPS];
        // if not running then this is elapsed time, else it's start time
        unsigned long time = 0; // centiseconds
        int currentLap = -1;
        int maxLap = 0;
        bool running = false;

        void draw();
};

#endif
