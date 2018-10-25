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

#endif
