#include <TimeLib.h>
#include <stdio.h>

#include "SWMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SWMode::display() {
    screen.fontColor(TS_8b_Blue, TS_8b_Black);

    debounceStart(screen, TSButtonLowerRight) {
        running = !running;
        if(running && zeroed) {
            startTime = now();
            startMillis = millis();
        }
        zeroed = false;
        playSound();
    } debounceEnd(TSButtonLowerRight);

    debounceStart(screen, TSButtonUpperLeft) {
        time = 0;
        centi = 0;
        zeroed = true;
        playSound();
    } debounceEnd(TSButtonUpperLeft);

    debounceStart(screen, TSButtonLowerLeft) {
        setMode(modes::BrickMode);
        return true;
    } debounceEnd(TSButtonLowerLeft);

    if(running) {
        time = now() - startTime;
        centi = (int) (((millis() - startMillis) / 10) % 100);
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
    uint8_t hmH = screen.getFontHeight();

    screen.setCursor((screen.xMax - screen.getPrintWidth(topMsg)) / 2, (screen.yMax - hmH) / 2);
    screen.print(topMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(botMsg)) / 2, (screen.yMax + hmH) / 2 + 2);
    screen.print(botMsg);
}
