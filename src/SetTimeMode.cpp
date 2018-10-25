#include <TimeLib.h>
#include <stdio.h>

#include "SetTimeMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SetTimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    if(screen.getButtons(TSButtonUpperLeft)) {
        if(!dbcReturn) {
            setMode(stdModes[0]);
            return true;
        }
    } else dbcReturn = false;

    printTime();

    return true;
}

void SetTimeMode::stop() {
    if(mode == this)
        delete mode;
}

void SetTimeMode::printTime() {
    char hmMsg[6];
    char secMsg[3];

    sprintf(hmMsg, "%02d:%02d", hour(), minute());
    sprintf(secMsg, "%02d", second());

    if(millis() % BLINK_TIME < BLINK_TIME / 2) {
        switch(focus) {
            case HOUR:
                hmMsg[0] = hmMsg[1] = ' ';
                break;
            case MIN:
                hmMsg[3] = hmMsg[4] = ' ';
                break;
            case SEC:
                secMsg[0] = secMsg[1] = ' ';
                break;
        }
    }

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    uint8_t hmH = screen.getFontHeight();

    screen.setCursor((screen.xMax - screen.getPrintWidth(hmMsg)) / 2, (screen.yMax - hmH) / 2);
    screen.print(hmMsg);

    screen.setFont(liberationSansNarrow_16ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(secMsg)) / 2, (screen.yMax + hmH) / 2 + 2);
    screen.print(secMsg);

    screen.setCursor(0, 0);
}
