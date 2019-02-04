#ifndef SETTIMEMODE_H
#define SETTIMEMODE_H

#include "Mode.hpp"

class SetTimeMode : public Mode {
    public:
        bool display();
        void start();
        void stop();
        bool isStd() {return false;};

    private:
        static const int BLINK_TIME = 1000;

        bool dbcReturn = true;
        bool dbcInc = true;
        bool dbcDec = true;
        bool dbcFocus = true;

        enum Focus {
            HOUR,
            MIN,
            SEC,
            YEAR,
            MONTH,
            DAY,
            FOCUS_C
        } focus = HOUR;

        void printTime();
};

#endif
