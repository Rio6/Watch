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
            { 9*60+ 0, 10*60+21, 'A', "Spanish"},
            {10*60+21, 10*60+30, '-', "Break"},
            {10*60+30, 11*60+51, 'B', "Chemistry"},
            {11*60+51, 12*60+30, '-', "Lunch"},
            {12*60+30, 13*60+55, 'C', "Geography"},
            {13*60+51, 13*60+55, '-', "Break"},
            {13*60+55, 15*60+16, 'D', "Phsychology"}
        }},
        {TUE, {
            { 9*60+ 0,  9*60+50, 'B', "Chemistry"},
            { 9*60+50, 10*60+52, 'F', "Focus"},
            {10*60+52, 11*60+ 0, '-', "Break"},
            {11*60+ 0, 11*60+51, 'A', "Spanish"},
            {11*60+51, 12*60+30, '-', "Lunch"},
            {12*60+30, 13*60+55, 'D', "Phsychology"},
            {13*60+51, 13*60+55, '-', "Break"},
            {13*60+55, 15*60+16, 'C', "Geography"}
              }},
        {WED, {
            { 9*60+ 0, 10*60+21, 'C', "Geography"},
            {10*60+21, 10*60+30, '-', "Break"},
            {10*60+30, 11*60+51, 'D', "Phsychology"},
            {11*60+51, 12*60+30, '-', "Lunch"},
            {12*60+30, 13*60+55, 'A', "Spanish"},
            {13*60+51, 13*60+55, '-', "Break"},
            {13*60+55, 15*60+16, 'B', "Chemistry"}
        }},
        {THU, {
            { 9*60+ 0,  9*60+50, 'D', "Phsychology"},
            { 9*60+50, 10*60+52, 'F', "Focus"},
            {10*60+52, 11*60+ 0, '-', "Break"},
            {11*60+ 0, 11*60+51, 'C', "Geography"},
            {11*60+51, 12*60+30, '-', "Lunch"},
            {12*60+30, 13*60+55, 'B', "Chemistry"},
            {13*60+51, 13*60+55, '-', "Break"},
            {13*60+55, 15*60+16, 'A', "Spanish"}
        }},
        {FRI_ONE, {
            { 9*60+ 0, 10*60+12, 'A', "Spanish"},
            {10*60+12, 10*60+14, '-', "Break"},
            {10*60+14, 11*60+26, 'B', "Chemistry"},
            {11*60+26, 11*60+46, '-', "Lunch"},
            {11*60+46, 12*60+59, 'C', "Geography"},
            {12*60+59, 14*60+12, 'D', "Phsychology"}
        }},
        {FRI_TWO, {
            { 9*60+ 0, 10*60+12, 'C', "Geography"},
            {10*60+12, 10*60+14, '-', "Break"},
            {10*60+14, 11*60+26, 'D', "Phsychology"},
            {11*60+26, 11*60+46, '-', "Lunch"},
            {11*60+46, 12*60+59, 'A', "Spanish"},
            {12*60+59, 14*60+12, 'B', "Chemistry"}
        }}
    };
};
