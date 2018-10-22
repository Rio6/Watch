#include <Arduino.h>
#include <TimeLib.h>
#include <stdio.h>

#include "TimeMode.hpp"
#include "main.h"

bool TimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    if(screen.getButtons(TSButtonUpperRight)) {
        if(!debounce) {
            showDate = !showDate;
            screen.clearScreen();
        }
        debounce = true;
    } else debounce = false;

    if(showDate) {
        printDate();
    }

    printTime();

    return debounce;
}

void TimeMode::printDate() {
    char msg[13];
    sprintf(msg, "%04d/%02d/%02d %s", year(), month(), day(), dayShortStr(weekday()));

    screen.setFont(liberationSansNarrow_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(msg)) / 2, 2);
    screen.print(msg);
}

void TimeMode::printTime() {
    char hmMsg[6];
    char secMsg[3];

    sprintf(hmMsg, "%02d:%02d", hour(), minute());
    sprintf(secMsg, "%02d", second());

    screen.setFont(liberationSansNarrow_22ptFontInfo);
    uint8_t hmH = screen.getFontHeight();

    screen.setCursor((screen.xMax - screen.getPrintWidth(hmMsg)) / 2, (screen.yMax - hmH) / 2);
    screen.print(hmMsg);

    screen.setFont(liberationSansNarrow_16ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(secMsg)) / 2, (screen.yMax + hmH) / 2 + 2);
    screen.print(secMsg);
}
