#include <Arduino.h>
#include <TinyScreen.h>
#include <RTCZero.h>
#include <TimeLib.h>
#include <stdio.h>

#include "TimeMode.hpp"
#include "SWMode.hpp"
#include "battery.h"

const uint8_t BRIGHTNESS = 10;
const unsigned int DURATION = 5000;

RTCZero rtc;
TinyScreen screen = TinyScreen(TinyScreenPlus); //Create the TinyScreen object

const int modeC = 2;
int modeI = 0;
Mode *stdModes[modeC] = {new TimeMode(), new SWMode()};
Mode *mode = stdModes[modeI];

void setup() {
    rtc.begin();

    screen.begin();
    screen.setFlip(1);
    screen.fontColor(TS_8b_White,TS_8b_Black);
    screen.setBrightness(BRIGHTNESS);

    char s_month[5];
    int month, day, year, hour, minute, second;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);
    sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);
    month = (strstr(month_names, s_month) - month_names) / 3;

    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month + 1, year - 2000);
}

void standby() {
    screen.off();

    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT1), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT2), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT3), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT4), [](){}, LOW);

    rtc.standbyMode();

    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT1));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT2));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT3));
    detachInterrupt(digitalPinToInterrupt(TSP_PIN_BT4));

    screen.on();
}

void nextMode() {
    mode->stop();
    modeI++;
    modeI %= modeC;
    mode = stdModes[modeI];
    mode->start();
}

void setMode(Mode *newMode) {
    mode->stop();
    mode = newMode;
    mode->start();
}

void loop() {
    setTime(rtc.getHours(), rtc.getMinutes(), rtc.getSeconds(),
            rtc.getDay(), rtc.getMonth(), rtc.getYear() + 2000);

    bool debounce = false;
    for(long start = millis(); millis() - start < DURATION;) {
        if(screen.getButtons(TSButtonLowerLeft)) {
            if(!debounce) {
                nextMode();
            }
            debounce = true;
        } else debounce = false;

        bool active = mode->display();
        if(active) start = millis();

        if(getBattVoltage() < 3.5f)
            printBattery();
    }
    standby();
}
