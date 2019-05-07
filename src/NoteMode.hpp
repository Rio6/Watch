#ifndef NOTEMODE_H
#define NOTEMODE_H

#include "Mode.hpp"

class NoteMode : public Mode {
    public:
        bool display();
        int getNum();

    private:
        int num = 0;
};

#endif
