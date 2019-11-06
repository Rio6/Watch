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

    const std::array<std::pair<int,int>, 17> FRIDAY_ONES {{
        {9, 6}, {9, 20}, {10, 4}, {10, 18}, {11, 8}, {11, 29}, {12, 13}, {1, 10}, {1, 24}, {2, 7}, {2, 28}, {3, 13}, {4, 17}, {5, 1}, {5, 22}, {6, 5}, {6, 19}
    }};

    const std::array<std::pair<int,int>, 16> FRIDAY_TWOS {{
        {9, 13}, {9, 27}, {10, 11}, {11, 1}, {11, 15}, {12, 6}, {12, 20}, {1, 17}, {1, 31}, {2, 21}, {3, 6}, {4, 3}, {4, 24}, {5, 8}, {5, 29}, {6, 12}
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
            { 9*60+ 0, 10*60+22, 'B', "Physics"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'A', "Metal"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'D', "Jazz Band"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'C', "Programming"},
        }},
        {WED, {
            { 9*60+ 0, 10*60+22, 'C', "Programming"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'D', "Jazz Band"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'A', "Metal"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'B', "Physics"},
        }},
        {THU, {
            { 9*60+ 0, 10*60+22, 'D', "Jazz Band"},
            {10*60+22, 10*60+32, '-', "Break"},
            {10*60+32, 11*60+53, 'C', "Programming"},
            {11*60+53, 12*60+32, '-', "Lunch"},
            {12*60+32, 13*60+53, 'B', "Physics"},
            {13*60+53, 13*60+56, '-', "Break"},
            {13*60+56, 15*60+18, 'A', "Metal"},
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
            { 9*60+ 0,  9*60+57, 'C', "Programming"},
            { 9*60+57, 10*60+59, '-', "Break"},
            {10*60+59, 11*60+55, 'D', "Jazz Band"},
            {11*60+55, 12*60+25, '-', "Lunch"},
            {12*60+25, 13*60+22, 'A', "Metal"},
            {13*60+22, 14*60+18, 'B', "Physics"},
        }}
    };
};

#endif
