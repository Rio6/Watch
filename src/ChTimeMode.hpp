#ifndef CHTIMEMODE_H
#define CHTIMEMODE_H

#include "Mode.hpp"

class ChTimeMode : public Mode {
    public:
        bool display();

    private:
        void printDate();
        void printTime();
        bool showDate = false;
};

#endif
