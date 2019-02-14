#include <TimeLib.h>
#include <stdio.h>

#include "SetTimeMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SetTimeMode::display() {
    screen.fontColor(TS_8b_Green,TS_8b_Black);

    debounceStart(screen, TSButtonUpperLeft) {
        setMode(modes::TimeMode);
        return true;
    } debounceEnd(TSButtonUpperLeft);

    debounceStart(screen, TSButtonLowerLeft) {
        focus = static_cast<Focus>((focus + 1) % FOCUS_C);
    } debounceEnd(TSButtonLowerLeft);

    int adj = 0;

    debounceStart(screen, TSButtonUpperRight) {
        adj += 1;
    } debounceEnd(TSButtonUpperRight);

    debounceStart(screen, TSButtonLowerRight) {
        adj -= 1;
    } debounceEnd(TSButtonLowerRight);

    if(adj) {
        switch(focus) {
            case SEC:
                adjustTime(adj);
                break;
            case MIN:
                adjustTime(adj * SECS_PER_MIN);
                break;
            case HOUR:
                adjustTime(adj * SECS_PER_HOUR);
                break;
            case DAY:
                adjustTime(adj * SECS_PER_DAY);
                break;
            case MONTH:
                {
                    int monthDays[]={31, (year() % 4 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                    int thisMonth = month() - 1;
                    int today = day();
                    int whyDoMonthsHaveDifferentDays = 0;

                    if(adj < 0) {
                        int lastMonth = thisMonth > 0 ? thisMonth - 1 : 11;
                        if(today > monthDays[lastMonth])
                            whyDoMonthsHaveDifferentDays = today;
                        else
                            whyDoMonthsHaveDifferentDays = monthDays[lastMonth];
                    } else {
                        int nextMonth = (thisMonth + 1) % 12;
                        if(today > monthDays[nextMonth])
                            whyDoMonthsHaveDifferentDays = monthDays[thisMonth] - today + monthDays[nextMonth];
                        else
                            whyDoMonthsHaveDifferentDays = monthDays[thisMonth];
                    }

                    adjustTime(adj * SECS_PER_DAY * whyDoMonthsHaveDifferentDays);
                }
                break;
            case YEAR:
                {
                    int y = year();

                    int whyDoYearsHaveDifferentDays = 365;
                    if((adj > 0 && ((y % 4 == 0 && month() <= 2) || (y % 4 == 3 && month() > 2))) ||
                            (adj < 0 && ((y % 4 == 1 && month() <= 2) || (y % 4 == 0 && month() > 2))))
                        whyDoYearsHaveDifferentDays = 366;

                    adjustTime(adj * SECS_PER_DAY * whyDoYearsHaveDifferentDays);
                }
                break;
            default:
                break;
        }
    }

    printTime();

    return true;
}

void SetTimeMode::start() {
    focus = HOUR;
}

void SetTimeMode::stop() {
    rtc.setEpoch(now());
    screen.clearScreen();
}

void SetTimeMode::printTime() {
    char hmMsg[6];
    char secMsg[3];
    char dateMsg[11];

    sprintf(hmMsg, "%02d:%02d", hour(), minute());
    sprintf(secMsg, "%02d", second());
    sprintf(dateMsg, "%04d/%02d/%02d", year(), month(), day());

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
            case YEAR:
                for(int i = 0; i < 4; i++)
                    dateMsg[i] = ' ';
                break;
            case MONTH:
                dateMsg[5] = dateMsg[6] = ' ';
                break;
            case DAY:
                dateMsg[8] = dateMsg[9] = ' ';
                break;
            default:
                break;
        }
    }

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    uint8_t hmH = screen.getFontHeight();

    screen.setCursor((screen.xMax - screen.getPrintWidth(hmMsg)) / 2, (screen.yMax - hmH) / 2);
    screen.print(hmMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(secMsg)) / 2, (screen.yMax + hmH) / 2 + 2);
    screen.print(secMsg);

    screen.setFont(liberationSansNarrow_edited_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(dateMsg)) / 2, 2);
    screen.print(dateMsg);
}
