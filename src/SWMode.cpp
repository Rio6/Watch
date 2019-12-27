#include <TimeLib.h>
#include <stdio.h>

#include "SWMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SWMode::display() {
    screen.fontColor(TS_8b_Blue, TS_8b_Black);

    debounce(TSButtonUpperRight) {
        time = now() * 100 + elapsedMillis / 10 - time;
        running = !running;
        playSound();
    }

    debounce(TSButtonLowerRight) {
        if(!running) {
            time = 0;
            playSound();
        }
    }

    debounce(TSButtonLowerLeft) {
        setMode(modes::ChTimeMode);
        return true;
    }

    draw();
    return true;
}

void SWMode::draw() {
    char topMsg[6];
    char botMsg[3];

    unsigned long centis = running ? now() * 100 + elapsedMillis / 10 - time : time;
    time_t displayTime = centis / 100;

    if(hour(displayTime) > 0) {
        sprintf(topMsg, "%02d:%02d", hour(displayTime), minute(displayTime));
        sprintf(botMsg, "%02d", second(displayTime));
    } else {
        sprintf(topMsg, "%02d:%02d", minute(displayTime), second(displayTime));
        sprintf(botMsg, "%02ld", centis % 100);
    }

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 - screen.getPrintWidth(topMsg), screen.yMax / 2 - 8);
    screen.print(topMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 + 4, screen.yMax / 2 - 5);
    screen.print(botMsg);
}
