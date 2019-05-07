#include <stdio.h>

#include "NoteMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool NoteMode::display() {
    debounceStart(screen, TSButtonUpperLeft) {
        setMode(modes::TimeMode);
        return true;
    } debounceEnd(TSButtonUpperLeft);

    debounceStart(screen, TSButtonLowerLeft) {
        if(num > 0) num--;
    } debounceEnd(TSButtonLowerLeft);

    debounceStart(screen, TSButtonLowerRight) {
        num++;
    } debounceEnd(TSButtonLowerRight);

    char msg[3];
    sprintf(msg, "%2d", num % 100);

    screen.setFont(liberationSansNarrow_edited_22ptFontInfo);
    screen.fontColor(TS_8b_Gray, TS_8b_Black);
    screen.setCursor((screen.xMax - screen.getPrintWidth(msg)) / 2, (screen.yMax - screen.getFontHeight()) / 2);
    screen.print(msg);

    return true;
}

int NoteMode::getNum() {
    return num;
}
