#ifndef MAIN_H
#define MAIN_H

//#define SET_TIME 0 // set this through PLATFORMIO_SRC_BUILD_FLAGS="-DSET_TIME=1"

#include <TinyScreen.h>
#include <RTCZero.h>

#include "Mode.hpp"

extern RTCZero rtc;
extern TinyScreen screen;

extern Mode *mode;
namespace modes {
    extern Mode *TimeMode, *SetTimeMode, *SWMode, *ChTimeMode, *BrickMode, *NoteMode;
};

extern byte debounce;
#define debounce(btn) \
    if(!screen.getButtons(btn)) {\
        debounce &= ~btn;\
    } else if(!(debounce & btn) && (debounce |= btn))

extern int elapsedMillis;

void nextMode();
void setMode(Mode*);

void playSound(int freq = 2637, int duration = 50);

#endif
