#include <TimeLib.h>
#include <stdio.h>

#include "SWMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SWMode::display() {
    screen.fontColor(TS_8b_Blue, TS_8b_Black);

    debounce(TSButtonUpperRight) {
        running = !running;
        if(running && zeroed) {
            startTime = now();
            startMillis = millis();
        }
        zeroed = false;
        playSound();
    }

    debounce(TSButtonLowerRight) {
        if(!running) {
            time = 0;
            centi = 0;
            zeroed = true;
            playSound();
        }
    }

    debounce(TSButtonLowerLeft) {
        setMode(modes::ChTimeMode);
        return true;
    }

    if(running) {
        int newTime = now() - startTime;
        if(newTime != time) {
            time = newTime;
            startMillis = millis();
        } else {
            centi = (int) (((millis() - startMillis) / 10) % 100);
        }
    }

    draw();
    return true;
}

void SWMode::draw() {
    char topMsg[6];
    char botMsg[3];

    if(hour(time) > 0) {
        sprintf(topMsg, "%02d:%02d", hour(time), minute(time));
        sprintf(botMsg, "%02d", second(time));
    } else {
        sprintf(topMsg, "%02d:%02d", minute(time), second(time));
        sprintf(botMsg, "%02d", centi);
    }

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 - screen.getPrintWidth(topMsg), screen.yMax / 2 - 8);
    screen.print(topMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 + 3, screen.yMax / 2 - 3);
    screen.print(botMsg);
}
