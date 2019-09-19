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
        char block;
        char *name;
    };

    enum SchoolDay {
        MON = 2, // weekDay() start with 1 from Sunday
        TUE,
        WED,
        THU,
        FRI_ONE,
        FRI_TWO,
        NOS
    };

    const std::array<std::pair<int,int>, 16> FRIDAY_ONES {{
        {9, 7}, {9, 21}, {10, 5}, {10, 26}, {11, 9}, {11, 30}, {12, 14}, {1, 11}, {1, 25}, {2, 8}, {3, 1}, {3, 15}, {4, 26}, {5, 17}, {5, 31}, {6, 14}
    }};

    const std::array<std::pair<int,int>, 16> FRIDAY_TWOS {{
        {9, 14}, {9, 28}, {10, 12}, {11, 2}, {11, 16}, {12, 7}, {12, 21}, {1, 18}, {2, 1}, {2, 15}, {3, 8}, {4, 5}, {5, 3}, {5, 24}, {6, 7}, {6, 21}
    }};

    const std::map<SchoolDay, std::vector<Class>> CLASSES {
        {MON, {
            { 9*60+ 0, 10*60+22, 'A', "Metal"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'B', "Physics"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'C', "Programming"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'D', "Jazz Band"},
        }},
        {TUE, {
            { 9*60+ 0, 10*60+22, 'A', "Physics"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'B', "Metal"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'C', "Jazz Band"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'D', "Programming"},
        }},
        {WED, {
            { 9*60+ 0, 10*60+22, 'A', "Programming"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'B', "Jazz Band"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'C', "Metal"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'D', "Physics"},
        }},
        {THU, {
            { 9*60+ 0, 10*60+22, 'A', "Jazz Band"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'B', "Programming"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'C', "Physics"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'D', "Metal"},
        }},
        {FRI_ONE, {
            { 9*60+ 0,  9*60+57, 'A', "Metal"},
            { 9*60+57, 10*60+59, '-', "Break"},
            {10*60+59, 11*60+55, 'B', "Physics"},
            {11*60+55, 12*60+25, '-', "Lunch"},
            {12*60+25, 13*60+22, 'C', "Programming"},
            {13*60+22, 14*60+18, 'D', "Jazz Band"},
        }},
        {FRI_TWO, {
            { 9*60+ 0,  9*60+57, 'A', "Programming"},
            { 9*60+57, 10*60+59, '-', "Break"},
            {10*60+59, 11*60+55, 'B', "Jazz Band"},
            {11*60+55, 12*60+25, '-', "Lunch"},
            {12*60+25, 13*60+22, 'C', "Metal"},
            {13*60+22, 14*60+18, 'D', "Physics"},
        }}
    };
};

#endif
