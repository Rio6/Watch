#ifndef TIMEMODE_H
#define TIMEMODE_H

#include "Mode.hpp"
#include "SetTimeMode.hpp"

class TimeMode : public Mode {
    public:
        bool display();
        void stop();

    private:
        static const int SET_BTN_HOLD = 3000;

        enum Extra {
            NONE,
            DATE,
            CLASS
        } extra;

        long timeSetBtn = 0;

        void printDate();
        void printTime();
        void printClass();
};

#endif
