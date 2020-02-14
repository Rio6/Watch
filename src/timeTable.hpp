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
            { 9*60-10, 10*60+22, 'A', "Calculus"},
            {10*60+22, 11*60+53, 'B', "Chemistry"},
            {11*60+53, 12*60+22, '-', "Lunch"},
            {12*60+22, 13*60+53, 'C', "Spanish"},
            {13*60+53, 15*60+18, 'D', "English"},
        }},
        {TUE, {
            { 9*60-10, 10*60+22, 'B', "Chemistry"},
            {10*60+22, 11*60+53, 'A', "Calculus"},
            {11*60+53, 12*60+22, '-', "Lunch"},
            {12*60+22, 13*60+53, 'D', "English"},
            {13*60+53, 15*60+18, 'C', "Spanish"},
        }},
        {WED, {
            { 9*60-10, 10*60+22, 'C', "Spanish"},
            {10*60+22, 11*60+53, 'D', "English"},
            {11*60+53, 12*60+22, '-', "Lunch"},
            {12*60+22, 13*60+53, 'A', "Calculus"},
            {13*60+53, 15*60+18, 'B', "Chemistry"},
        }},
        {THU, {
            { 9*60-10, 10*60+22, 'D', "English"},
            {10*60+22, 11*60+53, 'C', "Spanish"},
            {11*60+53, 12*60+22, '-', "Lunch"},
            {12*60+22, 13*60+53, 'B', "Chemistry"},
            {13*60+53, 15*60+18, 'A', "Calculus"},
        }},
        {FRI_ONE, {
            { 9*60-10,  9*60+58, 'A', "Calculus"},
            { 9*60+58, 10*60+58, 'F', "Focus"},
            {10*60+58, 11*60+55, 'B', "Chemistry"},
            {11*60+55, 12*60+15, '-', "Lunch"},
            {12*60+15, 13*60+22, 'C', "Spanish"},
            {13*60+22, 14*60+18, 'D', "English"},
        }},
        {FRI_TWO, {
            { 9*60-10,  9*60+58, 'C', "Spanish"},
            { 9*60+58, 10*60+58, 'F', "Focus"},
            {10*60+58, 11*60+55, 'D', "English"},
            {11*60+55, 12*60+15, '-', "Lunch"},
            {12*60+15, 13*60+22, 'A', "Calculus"},
            {13*60+22, 14*60+18, 'B', "Chemistry"},
        }}
    };
};

#endif
