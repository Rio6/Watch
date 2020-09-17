#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <map>
#include <array>
#include <vector>
#include <utility>
namespace timeTable {
    struct Class {
        int startTime;
        int endTime;
        char *name;
    };

    enum SchoolDay {
        MON = 2, // weekDay() start with 1 from Sunday
        TUE,
        WED,
        THU,
        FRI,
        NOS
    };

    const std::map<SchoolDay, std::vector<Class>> CLASSES {
        {MON, {
            { 8*60+20,  9*60+20, "121 OFC"},
            { 9*60+20, 10*60+20, "115 OFC"},
            {11*60+20, 12*60+20, "100 LEC"},
            {13*60+20, 14*60+20, "116 OFC"},
            {14*60+20, 15*60+50, "102 LEC"},
        }},
        {TUE, {
            {10*60+20, 12*60+20, "121 TUT"},
            {15*60+20, 17*60+20, "116 TUT"},
        }},
        {WED, {
            { 8*60+20,  9*60+20, "121 OFC"},
            { 9*60+20, 10*60+20, "115 OFC"},
            {11*60+20, 12*60+20, "100 LEC"},
            {13*60+20, 14*60+20, "116 OFC"},
            {14*60+20, 15*60+50, "102 LEC"},
        }},
        {THU, {
            { 8*60+20, 11*60+20, "110 LAB"},
            {12*60+20, 13*60+20, "116 OFC"},
            {13*60+20, 14*60+20, "115 OFC"},
        }},
        {FRI, {
            { 8*60+20,  9*60+20, "121 OFC"},
            { 9*60+20, 10*60+20, "115 OFC"},
            {11*60+20, 12*60+20, "100 LEC"},
            {12*60+20, 13*60+20, "102 OFC"},
            {13*60+20, 16*60+20, "100 TUT"},
        }}
    };
};

#endif
