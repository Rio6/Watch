#ifndef BRICK_H
#define BRICK_H

#include <cstdint>

#include "Mode.hpp"

struct Brick {
    int x, y;
    int w = 9, h = 5;
    uint8_t color;
    bool hit = false;
};

struct Ball {
    int x, y;
    int _x, _y; // for clearing the screen
    int size = 3;
    float vel, angle;
};

struct Platform {
    int x, y;
    int _x, _y;
    int w = 15, h = 3;
};

class BrickMode : public Mode {
    public:
        BrickMode();

        void reset();
        void start();
        bool display();

    private:
        static const int bCols = 10;
        static const int bRows = 3;
        static const int bricks_c = bCols * bRows;

        Brick bricks[bricks_c];
        Ball ball;
        Platform plat;
        float startVel = 1;

        long lastTime = 0;

        void movePlat(int);
        void ballCollision(float norm);
};

#endif
