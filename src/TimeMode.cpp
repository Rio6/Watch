#include <TimeLib.h>
#include <stdio.h>
#include <algorithm>

#include "TimeMode.hpp"
#include "main.hpp"
#include "myFont.h"
#include "timeTable.hpp"
#include "NoteMode.hpp"

bool TimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    bool active = false;

    debounce(TSButtonUpperRight) {
        extra = extra != DATE ? DATE : NONE;
        screen.clearScreen();
        active = true;
    }

    debounce(TSButtonLowerRight) {
        extra = extra != CLASS ? CLASS : NONE;
        screen.clearScreen();
        active = true;
    }

    debounce(TSButtonLowerLeft) {
        setMode(modes::SWMode);
        return true;
    }

    if(screen.getButtons(TSButtonUpperLeft)) {
        debounce |= TSButtonUpperLeft;
        if(timeSetBtn >= 0) {
            if(timeSetBtn == 0) {
                timeSetBtn = millis();
                active = true;
            } else if(millis() - timeSetBtn > SET_BTN_HOLD) {
                setMode(modes::SetTimeMode);
                timeSetBtn = -1;
                return true;
            }
        }
    } else {
        if(timeSetBtn >= 0 && debounce & TSButtonUpperLeft) {
            setMode(modes::NoteMode);
            return true;
        }
        timeSetBtn = 0;
        debounce &= ~TSButtonUpperLeft;
    }

    if(extra == DATE) printDate();
    else if(extra == CLASS) printClass();

    printTime();

    // Print notes
    NoteMode *note = static_cast<NoteMode*>(modes::NoteMode);
    if(note->getNum() > 0) {
        char msg[3];
        sprintf(msg, "%2d", note->getNum() % 100);
        screen.setFont(liberationSansNarrow_16ptFontInfo);
        screen.fontColor(TS_8b_Gray, TS_8b_Black);
        screen.setCursor(2, screen.yMax - screen.getFontHeight());
        screen.print(msg);
    } else {
        screen.drawRect(0, screen.yMax - 10, 40, 10, true, 0);
    }

    return active;
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

void TimeMode::printClass() {
    using namespace timeTable;

    int wday = weekday();
    SchoolDay sday;

    if(wday > 6 || wday < 2) {
        sday = NOS;
    } else if(wday == 6) {
        int m = month(), d = day();
        if(std::find(FRIDAY_ONES.begin(), FRIDAY_ONES.end(), std::make_pair(m, d)) != FRIDAY_ONES.end()) {
            sday = FRI_ONE;
        } else if(std::find(FRIDAY_TWOS.begin(), FRIDAY_TWOS.end(), std::make_pair(m, d)) != FRIDAY_TWOS.end()) {
            sday = FRI_TWO;
        } else {
            sday = NOS;
        }
    } else {
        sday = static_cast<SchoolDay>(wday);
    }

    char msg[13];
    int time = hour() * 60 + minute();
    bool hasClass = false;

    if(CLASSES.count(sday) > 0) {
        for(auto i = std::begin(CLASSES.at(sday)); i != std::end(CLASSES.at(sday)); i++) {
            const Class &c = *i;
            if(time >= c.startTime && time < c.endTime) {
                sprintf(msg, "%.10s Blk: %c", c.name, c.block);
                hasClass = true;
                break;
            }
        }
    }

    if(!hasClass) sprintf(msg, "no class");

    screen.setFont(liberationSansNarrow_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(msg)) / 2, 2);
    screen.print(msg);
}

void TimeMode::start() {
    timeSetBtn = -1;
}
