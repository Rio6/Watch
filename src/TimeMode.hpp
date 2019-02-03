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

        SetTimeMode settingMode = SetTimeMode();

        enum Extra {
            NONE,
            DATE,
            CLASS
        } extra;

        bool dbcDate = true;
        bool dbcClass = true;
        long timeSetBtn = 0;

        void printDate();
        void printTime();
        void printClass();
};

#endif
