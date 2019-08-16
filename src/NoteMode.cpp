#include <stdio.h>

#include "NoteMode.hpp"
#include "main.hpp"
#include "myFont.h"

bool NoteMode::display() {
    debounce(TSButtonUpperLeft) {
        setMode(modes::TimeMode);
        return true;
    }

    debounce(TSButtonLowerRight) {
        if(num > 0) num--;
    }

    debounce(TSButtonUpperRight) {
        num++;
    }

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
