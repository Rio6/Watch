#ifndef MAIN_H
#define MAIN_H

#include <TinyScreen.h>
#include <RTCZero.h>

#include "Mode.hpp"

#define debounceStart(screen, btn) \
    if(screen.getButtons(btn)) {\
        bool run = !(debounce & btn);\
        debounce |= btn;\
        if(run)

#define debounceEnd(btn) \
    } else debounce &= ~btn

extern RTCZero rtc;
extern TinyScreen screen;

extern Mode *mode;
namespace modes {
    extern Mode *TimeMode, *SetTimeMode, *SWMode, *ChTimeMode;
};

extern byte debounce;

void nextMode();
void setMode(Mode*);

void playSound(int freq = 2637, int duration = 50);

#endif
