#include <TimeLib.h>
#include <stdio.h>

#include "main.hpp"
#include "ChTimeMode.hpp"
#include "lunar.hpp"
#include "myFont.h"

bool ChTimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    bool active = false;

    debounce(TSButtonUpperRight) {
        showDate = !showDate;
        screen.clearScreen();
        active = true;
    }

    debounce(TSButtonLowerLeft){
        setMode(modes::TimeMode);
        return true;
    }

    if(showDate) printDate();

    printTime();

    return active;
}

void ChTimeMode::printDate() {
    time_t t = now();
    int y, m, d;
    getLunar(t, &y, &m, &d);

    char yMsg[4];
    char mMsg[4];
    char dMsg[3];

    int offset = y - 1864; // 1864 是甲子年
    sprintf(yMsg, "%c%c]", tiangan[offset%10], dizhi[offset%12]); // %c%c年

    if(m > 10)
        sprintf(mMsg, "%c%cd", nStr2[m/10], nStr1[m%10]); // %c%c月
    else if(m == 10)
        sprintf(mMsg, "Rd"); // 十月
    else if(m == 1)
        sprintf(mMsg, "fd"); // 正月
    else
        sprintf(mMsg, "%cd", nStr1[m]); // %c月

    sprintf(dMsg, "%c%c", nStr2[d/10], nStr1[d%10]);

    char msg[10];
    sprintf(msg, "%sA%s%s", yMsg, mMsg, dMsg); // %s　%s%s

    screen.setFont(song_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(msg)) / 2, 2);
    screen.print(msg);
}

void ChTimeMode::printTime() {
    time_t t = now();

    char hMsg[4];

    int h = hour(t);
    sprintf(hMsg, "%c%c", dizhi[((h+1) % 24) / 2], halfs[(h+1)%2]);

    screen.setFont(song_22ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 - screen.getPrintWidth(hMsg), screen.yMax / 2 - 10);
    screen.print(hMsg);

    int m = minute(t);
    char kMsg[3];
    sprintf(kMsg, "%cQ", nStr1[m/15+1]); // %c刻

    screen.setFont(song_8ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 + 3, screen.yMax / 2);
    screen.print(kMsg);
}
