#include <Arduino.h>
#include <TimeLib.h>
#include <stdio.h>

#include "TimeMode.hpp"
#include "SetTimeMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool TimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    if(screen.getButtons(TSButtonUpperRight)) {
        if(!debounce) {
            showDate = !showDate;
            screen.clearScreen();
        }
        debounce = true;
    } else debounce = false;

    if(screen.getButtons(TSButtonUpperLeft)) {
        if(timeSetBtn < 0) {
            timeSetBtn = millis();
        } else if(millis() - timeSetBtn > SET_BTN_HOLD) {
            setMode(new SetTimeMode());
            timeSetBtn = -1;
            return true;
        }
    } else timeSetBtn = -1;

    if(showDate) {
        printDate();
    }

    printTime();

    return debounce || timeSetBtn > 0;
}

void TimeMode::stop() {
    screen.clearScreen();
}

void TimeMode::printDate() {
    char msg[10];
    sprintf(msg, "%02d/%02d %s", month(), day(), dayShortStr(weekday()));

    screen.setFont(liberationSansNarrow_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(msg)) / 2, 2);
    screen.print(msg);
}

void TimeMode::printTime() {
    char hmMsg[6];
    char secMsg[3];

    sprintf(hmMsg, "%02d:%02d", hour(), minute());
    sprintf(secMsg, "%02d", second());

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    uint8_t hmH = screen.getFontHeight();

    screen.setCursor((screen.xMax - screen.getPrintWidth(hmMsg)) / 2, (screen.yMax - hmH) / 2);
    screen.print(hmMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(secMsg)) / 2, (screen.yMax + hmH) / 2 + 2);
    screen.print(secMsg);
}
