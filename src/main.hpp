#ifndef MAIN_H
#define MAIN_H

#include <TinyScreen.h>
#include <RTCZero.h>

#include "Mode.hpp"

extern RTCZero rtc;
extern TinyScreen screen;

extern Mode *stdModes[];
extern Mode *mode;

void nextMode();
void setMode(Mode*);

void playSound(int freq = 2637, int duration = 50);

#endif
