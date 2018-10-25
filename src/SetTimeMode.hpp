#ifndef SETTIMEMODE_H
#define SETTIMEMODE_H

#include "Mode.hpp"

class SetTimeMode : public Mode {
    public:
        bool display();
        void stop();

    private:
        static const int BLINK_TIME = 1000;

        bool dbcReturn = true;
        enum {
            HOUR,
            MIN,
            SEC
        } focus = HOUR;

        void printTime();
};

#endif
