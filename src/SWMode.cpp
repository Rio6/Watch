#include <TimeLib.h>
#include <stdio.h>

#include "SWMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool SWMode::display() {
    screen.fontColor(TS_8b_Blue, TS_8b_Black);

    debounce(TSButtonUpperRight) {
        /*
         * When starting, `time` is the centiseconds elapsed in the last run.
         * Taking that amount away from current time results the starting time
         * for the next run.
         *
         * When stopping, `time` is the start time of this run. Taking that away
         * from current time results in elapsed time
         */
        time = centis() - time;
        running = !running;
        currentLap = -1;
        screen.clearScreen();
        playSound();
    }

    debounce(TSButtonUpperLeft) {
        if(running) {
            if(maxLap < NUM_LAPS) {
                maxLap++;
            }
            if(++currentLap >= maxLap) currentLap = 0;
            laps[currentLap] = centis() - time;
        } else if(++currentLap >= maxLap) currentLap = -1;
        screen.clearScreen();
    }

    debounce(TSButtonLowerRight) {
        if(!running) {
            time = 0;
            currentLap = -1;
            maxLap = 0;
            screen.clearScreen();
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
    char lapMsg[7];

    unsigned long elapsed = currentLap >= 0 ? laps[currentLap]
                            : running ? centis() - time
                            : time;
    time_t displayTime = elapsed / 100;

    if(hour(displayTime) > 0) {
        sprintf(topMsg, "%02d:%02d", hour(displayTime), minute(displayTime));
        sprintf(botMsg, "%02d", second(displayTime));
    } else {
        sprintf(topMsg, "%02d:%02d", minute(displayTime), second(displayTime));
        sprintf(botMsg, "%02ld", elapsed % 100);
    }

    if(currentLap >= 0) {
        sprintf(lapMsg, "lap %d", currentLap+1);
    } else {
        lapMsg[0] = '\0';
    }

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 - screen.getPrintWidth(topMsg), screen.yMax / 2 - 8);
    screen.print(topMsg);

    screen.setFont(liberationSansNarrow_edited_16ptFontInfo);
    screen.setCursor(screen.xMax * 2 / 3 + 4, screen.yMax / 2 - 5);
    screen.print(botMsg);

    screen.setFont(liberationSansNarrow_8ptFontInfo);
    screen.setCursor((screen.xMax - screen.getPrintWidth(lapMsg)) / 2, 4);
    screen.print(lapMsg);
}
