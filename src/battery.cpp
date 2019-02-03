#include <Arduino.h>
#include <avr/dtostrf.h>

#include "main.hpp"

static float getVCC() {
    SYSCTRL->VREF.reg |= SYSCTRL_VREF_BGOUTEN;
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->SAMPCTRL.bit.SAMPLEN = 0x1;
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->INPUTCTRL.bit.MUXPOS = 0x19;         // Internal bandgap input
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->SWTRIG.bit.START = 1;  // Start conversion
    ADC->INTFLAG.bit.RESRDY = 1;  // Clear the Data Ready flag
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->SWTRIG.bit.START = 1;  // Start the conversion again to throw out first value
    while ( ADC->INTFLAG.bit.RESRDY == 0 );   // Waiting for conversion to complete
    uint32_t valueRead = ADC->RESULT.reg;
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    ADC->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
    while (ADC->STATUS.bit.SYNCBUSY == 1);
    SYSCTRL->VREF.reg &= ~SYSCTRL_VREF_BGOUTEN;
    float vcc = (1.1 * 1023.0) / valueRead;
    return vcc;
}

float getBattVoltage() {
    const int VBATTpin = A4;
    float VCC = getVCC();

    // Use resistor division and math to get the voltage
    float resistorDiv = 0.5;
    float ADCres = 1023.0;
    float battVoltageReading = analogRead(VBATTpin);
    battVoltageReading = analogRead(VBATTpin); // Throw out first value
    float battVoltage = VCC * battVoltageReading / ADCres / resistorDiv;

    return battVoltage;
}

void printBattery(float volt) {
    char msg[5];
    dtostrf(volt, 4, 1, msg);

    if(volt < 3.5f)
        screen.fontColor(TS_8b_Red,TS_8b_Black);
    else
        screen.fontColor(TS_8b_Green,TS_8b_Black);

    screen.setFont(liberationSansNarrow_8ptFontInfo);
    screen.setCursor(
            screen.xMax - screen.getPrintWidth(msg) - screen.getPrintWidth(" V"),
            screen.yMax - screen.getFontHeight() - 10);

    screen.print(msg);
    screen.print(" V");
}

void printBattery() {
    printBattery(getBattVoltage());
}
