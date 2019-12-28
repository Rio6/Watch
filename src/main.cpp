#include <Arduino.h>
#include <TinyScreen.h>
#include <RTCZero.h>
#include <TimeLib.h>
#include <stdio.h>

#include "Mode.hpp"
#include "TimeMode.hpp"
#include "SetTimeMode.hpp"
#include "SWMode.hpp"
#include "ChTimeMode.hpp"
#include "NoteMode.hpp"
#include "battery.hpp"
#include "main.hpp"

const uint8_t BRIGHTNESS = 10;
const unsigned int DURATION = 5000;

RTCZero rtc;
TinyScreen screen = TinyScreen(TinyScreenPlus); //Create the TinyScreen object
byte debounce = 0;

// Time keeping between each second
static time_t lastTime;
static unsigned long lastMillis;
static int elapsedMillis = 0;

Mode *modes::TimeMode = new ::TimeMode();
Mode *modes::SetTimeMode = new ::SetTimeMode();
Mode *modes::SWMode = new ::SWMode();
Mode *modes::ChTimeMode = new ::ChTimeMode();
Mode *modes::NoteMode = new ::NoteMode();
Mode *mode = modes::TimeMode;

void setup() {
    rtc.begin();

    SerialUSB.begin(9600);

    pinMode(5, OUTPUT); // Speaker
    pinMode(6, INPUT); // Connected to pin 5, so set to input to prevent short circuit

    screen.begin();
    screen.setFlip(1);
    screen.fontColor(TS_8b_White,TS_8b_Black);
    screen.setBrightness(BRIGHTNESS);

#if(SET_TIME)
    char s_month[5];
    int month, day, year, hour, minute, second;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);
    sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);
    month = (strstr(month_names, s_month) - month_names) / 3;

    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month + 1, year - 2000);
#endif
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
    screen.clearScreen();
    mode->start();
    playSound();
}

void playSound(int freq, int duration) {
    tone(5, freq, duration);
}

void loop() {
    setTime(rtc.getEpoch());
    screen.clearScreen();
    for(long start = millis(); millis() - start < DURATION;) {

        // Time keeping between seconds
        time_t time = now();
        if(time != lastTime) {
            lastTime = time;
            lastMillis = millis();
            elapsedMillis = 0;
        } else {
            elapsedMillis = millis() - lastMillis;
        }

        bool active = mode->display();
        if(active) start = millis();

        float volt = getBattVoltage();
        if(volt < 3.5f)
            printBattery(volt);

        delay(10);
    }
    standby();
}

unsigned long centis() {
    return now() * 100 + elapsedMillis / 10;
}
