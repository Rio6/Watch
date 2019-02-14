#include <Arduino.h>
#include <TinyScreen.h>
#include <RTCZero.h>
#include <TimeLib.h>
#include <stdio.h>

#include "Mode.hpp"
#include "TimeMode.hpp"
#include "SetTimeMode.hpp"
#include "SWMode.hpp"
#include "battery.h"
#include "main.hpp"

const uint8_t BRIGHTNESS = 10;
const unsigned int DURATION = 5000;

RTCZero rtc;
TinyScreen screen = TinyScreen(TinyScreenPlus); //Create the TinyScreen object

Mode *modes::TimeMode = new ::TimeMode();
Mode *modes::SetTimeMode = new ::SetTimeMode();
Mode *modes::SWMode = new ::SWMode();
Mode *mode = modes::TimeMode;

byte debounce = 0;

void setup() {
    rtc.begin();

    SerialUSB.begin(9600);

    screen.begin();
    screen.setFlip(1);
    screen.fontColor(TS_8b_White,TS_8b_Black);
    screen.setBrightness(BRIGHTNESS);
/*
    char s_month[5];
    int month, day, year, hour, minute, second;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);
    sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);
    month = (strstr(month_names, s_month) - month_names) / 3;

    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month + 1, year - 2000);
    */
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

void setMode(Mode *newMode) {
    mode->stop();
    mode = newMode;
    mode->start();
    playSound();
}

void playSound(int freq, int duration) {
    tone(5, freq, duration);
}

void loop() {
    setTime(rtc.getEpoch());
    for(long start = millis(); millis() - start < DURATION;) {

        bool active = mode->display();
        if(active) start = millis();

        float volt = getBattVoltage();
        if(volt < 3.5f || volt > 4.1f)
            printBattery(volt);
    }
    standby();
}
