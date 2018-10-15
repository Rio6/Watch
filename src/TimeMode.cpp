#include <Arduino.h>
#include <TimeLib.h>

#include "TimeMode.hpp"
#include "main.h"

const uint8_t TimeMode::BRIGHTNESS = 10;
const int TimeMode::DURATION = 5;

void TimeMode::display() {
    screen.on();
    screen.setBrightness(BRIGHTNESS);

    for(counter = 0; counter < DURATION; counter++) {
        setTime(rtc.getHours(), rtc.getMinutes(), rtc.getSeconds(),
                rtc.getDay(), rtc.getMonth(), rtc.getYear() + 2000);

        if(showDate) {
            printDate();
        }
        printTime();

        delay(1000);
    }

    screen.off();
}

void TimeMode::button(int btn) {
    if(btn == 1) {
        showDate = !showDate;
        if(showDate) {
            printDate();
        } else {
            screen.clearScreen();
            printTime();
        }
    }
    counter = 0;
}

void TimeMode::printDate() {
    screen.setFont(liberationSansNarrow_12ptFontInfo);   //Set the font type

    int y = year(), m = month(), d = day();

    screen.setCursor(15,8); //Set the cursor where you want to start printing the date
    screen.print(y);
    screen.print("/");
    if(m < 10) screen.print(0); //print a leading 0 if hour value is less than 0
    screen.print(m);
    screen.print("/");
    if(d < 10) screen.print(0);
    screen.print(d);

    screen.setCursor(30,25); //Set the cursor where you want to start printing the date
    screen.print(dayStr(weekday()));
}

void TimeMode::printTime() {
    screen.setFont(liberationSansNarrow_16ptFontInfo);   //Set the font type
    screen.setCursor(20,45); //Set the cursor where you want to start printing the time

    int h = hour(), m = minute(), s = second();

    if(h < 10) screen.print(0); //print a leading 0 if hour value is less than 0
    screen.print(h);
    screen.print(":");
    if(m < 10) screen.print(0); //print a leading 0 if minute value is less than 0
    screen.print(m);
    screen.print(":");
    if(s < 10) screen.print(0); //print a leading 0 if seconds value is less than 0
    screen.print(s);
    screen.print(" "); //just a empty space after the seconds
    screen.setCursor(15,8); //Set the cursor where you want to start printing the date
}
