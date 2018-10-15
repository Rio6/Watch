#include <Arduino.h>
#include <TinyScreen.h>
#include <RTCZero.h>
#include <stdio.h>

#include "TimeMode.hpp"

RTCZero rtc;
TinyScreen screen = TinyScreen(TinyScreenPlus); //Create the TinyScreen object

TimeMode modes[] = {TimeMode()};

void setup() {
    char s_month[5];
    int month, day, year, hour, minute, second;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    screen.begin();
    screen.setFlip(1);
    screen.fontColor(TS_8b_White,TS_8b_Black);

    rtc.begin();

    // Let's be lazy and let the compiler set the current date and time for us.
    // This will be a few seconds off due to the time it takes to compile the
    // .ino file and upload the app. But pretty close.

    // __DATE__ is a C++ preprocessor string with the current date in it.
    // It will look something like 'Mar  13  2016'.
    // So we need to pull those values out and convert the month string to a number.
    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);

    // Similarly, __TIME__ will look something like '09:34:17' so get those numbers.
    sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);

    // Find the position of this month's string inside month_names, do a little
    // pointer subtraction arithmetic to get the offset, and divide the
    // result by 3 since the month names are 3 chars long.
    month = (strstr(month_names, s_month) - month_names) / 3;

    rtc.setTime(hour, minute, second);
    // The RTC library expects months to be 1 - 12 andyears to be from 2000.
    rtc.setDate(day, month + 1, year - 2000);
}

void standby() {
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT1), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT2), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT3), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT4), [](){}, LOW);

    rtc.standbyMode();

    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT1));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT2));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT3));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT4));
}

void loop() {
    modes[0].display();
    standby();
}
