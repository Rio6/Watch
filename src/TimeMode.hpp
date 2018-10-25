#ifndef TIMEMODE_H
#define TIMEMODE_H

#include "Mode.hpp"

class TimeMode : public Mode {
    public:
        bool display();
        void stop();

    private:
        static const int SET_BTN_HOLD = 3000;

        bool showDate;
        bool debounce = false;
        long timeSetBtn = 0;

        void printDate();
        void printTime();
};

#endif
