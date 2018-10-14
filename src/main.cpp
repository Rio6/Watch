#include <Arduino.h>
#include <TinyScreen.h> //include TinyScreen library
#include <RTCZero.h> //include the Arduino Zero's Real Time Clock library
#include <TimeLib.h> //include the Arduino Time library
#include <stdio.h>  // include the C++ standard IO library

// Create an rtc object
RTCZero rtc;

// We'll dynamically change these values to set the current initial time
// No need to change them here.
byte seconds = 0;
byte minutes = 45;
byte hours = 9;

// We'll dynamically change these values to set the current initial date
// The preset values are only examples.
byte days = 13;
byte months = 3;
byte years = 16;

int brightness = 15; // We'll set it, 3 - 15 based on time of day

TinyScreen display = TinyScreen(TinyScreenPlus); //Create the TinyScreen object

void setup() {
    char s_month[5];
    int tmonth, tday, tyear, thour, tminute, tsecond;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    display.begin();                            //Initializes TinyScreen board
    display.setFlip(1);                         //Flips the TinyScreen rightside up for O Watch
    display.on();                               //Turns TinyScreen display on
    display.fontColor(TS_8b_White,TS_8b_Black); //Set the font color, font background

    rtc.begin(); // initialize RTC

    // Set the time and date. Change this to your current date and time.
    // setTime(16,19,00,12,3,2016);    //values in the order hr,min,sec,day,month,year

    // Let's be lazy and let the compiler set the current date and time for us.
    // This will be a few seconds off due to the time it takes to compile the
    // .ino file and upload the app. But pretty close.

    // __DATE__ is a C++ preprocessor string with the current date in it.
    // It will look something like 'Mar  13  2016'.
    // So we need to pull those values out and convert the month string to a number.
    sscanf(__DATE__, "%s %d %d", s_month, &tday, &tyear);

    // Similarly, __TIME__ will look something like '09:34:17' so get those numbers.
    sscanf(__TIME__, "%d:%d:%d", &thour, &tminute, &tsecond);

    // Find the position of this month's string inside month_names, do a little
    // pointer subtraction arithmetic to get the offset, and divide the
    // result by 3 since the month names are 3 chars long.
    tmonth = (strstr(month_names, s_month) - month_names) / 3;

    months = tmonth + 1;  // The RTC library expects months to be 1 - 12.
    days = tday;
    years = tyear - 2000; // The RTC library expects years to be from 2000.
    hours = thour;
    minutes = tminute;
    seconds = tsecond;

    rtc.setTime(hours, minutes, seconds);
    rtc.setDate(days, months, years);

    // Using empty lambda because NULL doesn't work
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT1), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT2), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT3), [](){}, LOW);
    attachInterrupt(digitalPinToInterrupt(TSP_PIN_BT4), [](){}, LOW);
}

void displayTime() {

    display.on();

    for (int i = 1; i < 5; i++) // Display for 5*1000 milliseconds (5 seconds), update display each second
    {
        // To correctly handle switching date at midnight while the time display is on,
        // update -everything-, not just the seconds.

        display.setFont(liberationSansNarrow_12ptFontInfo);   //Set the font type

        // Get the complete date and time now since they're used for the weekday
        // and brightness calculations.
        months = rtc.getMonth();
        days = rtc.getDay();
        years = rtc.getYear();
        hours = rtc.getHours();
        minutes = rtc.getMinutes();
        seconds = rtc.getSeconds();

        if(hours <= 12)
            brightness = hours + 3; // 0 hours = 3 brightness, noon = 15
        else if(hours >= 18)
            brightness = (24 - hours) * 2 + 2;  // 23 hours = 4 brightness, 18 hours = 14
        else
            brightness = 15; // full brightness all afternoon
        if(brightness < 3)
            brightness = 3;
        if(brightness > 15)
            brightness = 15;
        display.setBrightness(brightness);                  //Set display brightness 0 - 15


        // Print date in US format MM:DD:YY (Switch the order in which day, month, year that you like to use)
        display.setCursor(15,8); //Set the cursor where you want to start printing the date
        if(months < 10) display.print(0); //print a leading 0 if hour value is less than 0
        display.print(months);
        display.print("/");
        days = rtc.getDay();
        if(days < 10) display.print(0);
        display.print(days); 
        display.print("/20");
        display.print(years);

        display.setCursor(30,25); //Set the cursor where you want to start printing the date  
        setTime(hours,minutes,seconds,days,months,2000 +  years);    //values in the order hr,min,sec,day,month,year
        display.print(dayStr(weekday()));

        display.setFont(liberationSansNarrow_16ptFontInfo);   //Set the font type

        // display time in HH:MM:SS 24 hour format
        display.setCursor(20,45); //Set the cursor where you want to start printing the time
        if(hours < 10) display.print(0); //print a leading 0 if hour value is less than 0
        display.print(hours);
        display.print(":");
        if(minutes < 10) display.print(0); //print a leading 0 if minute value is less than 0
        display.print(minutes);
        display.print(":");
        if(seconds < 10) display.print(0); //print a leading 0 if seconds value is less than 0
        display.print(seconds);
        display.print(" "); //just a empty space after the seconds
        delay(1000); //display for 1 seconds
    }

    display.off();                               //Turns TinyScreen display off
}

void loop() {
    displayTime();
    rtc.standbyMode();
}
