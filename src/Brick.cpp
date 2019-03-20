#include <Arduino.h>
#include <cstdlib>
#include <math.h>

#include "Brick.hpp"
#include "main.hpp"

BrickMode::BrickMode() {
    std::srand(millis());
    reset();
}

void BrickMode::reset() {
    // clear screen
    screen.drawRect(0, 0, screen.xMax, screen.yMax, true, 0x00);
    playSound(622);

    for(int i = 0; i < bRows; i++) {
        for(int j = 0; j < bCols; j++) {
            Brick &b = bricks[i * bCols + j];
            b.color = std::rand() % 0xf0 + 0x0f;
            b.x = j * b.w + 4;
            b.y = (i+2) * b.h;
            b.hit = false;
        }
    }

    plat.x = (screen.xMax - plat.w) / 2;
    plat.y = screen.yMax - plat.h;

    ball.x = plat.x + (plat.w - ball.size) / 2;
    ball.y = plat.y - ball.size;

    ball.vel = 0;
    ball.angle = 4;
}

bool BrickMode::display() {

    debounceStart(screen, TSButtonUpperLeft) {
        setMode(modes::ChTimeMode);
        return true;
    } debounceEnd(TSButtonUpperLeft);

    long now = millis();
    int ct = (now - lastTime) / 10;
    if(!lastTime)
        ct = 0;
    lastTime = now;

    if(screen.getButtons(TSButtonLowerLeft)) {
        movePlat(-ct);
    }

    if(screen.getButtons(TSButtonLowerRight)) {
        movePlat(ct);
    }

    float vx = cos(ball.angle) * ball.vel;
    float vy = sin(ball.angle) * ball.vel;

    ball._x = ball.x;
    ball._y = ball.y;

    ball.x += round(vx) * ct;
    ball.y += round(vy) * ct;

    // collision to wall
    if(ball.x < ball.size && vx < 0) {
        ball.x = ball.size;
        ballCollision(M_PI / 2);
    } else if(ball.x > screen.xMax - ball.size && vx > 0) {
        ball.x = screen.xMax - ball.size;
        ballCollision(M_PI / 2);
    }
    if(ball.y < ball.size && vy < 0) {
        ball.y = ball.size;
        ballCollision(0);
    } else if(ball.y > screen.yMax + ball.size) {
        reset();
    }

    // collision to platform
    if(ball.x + ball.size > plat.x && ball.x < plat.x + plat.w &&
       ball.y + ball.size > plat.y && ball.y < plat.y + plat.h && vy > 0) {
        ball.y = plat.y - ball.size;
        ballCollision(0);
    }

    // collision to bricks
    int bricksLeft = bricks_c;
    for(Brick &brick : bricks) {
        if(brick.hit) {
            bricksLeft--;
            continue;
        }

        int xdiffl = brick.x - (ball.x + ball.size),
            xdiffr = (brick.x + brick.w) - ball.x,
            ydiffu = brick.y - (ball.y + ball.size),
            ydiffd = (brick.y + brick.h) - ball.y;

        if(xdiffl < 0 && xdiffr > 0 && ydiffu < 0 && ydiffd > 0) {
            // TODO proper collision on all directions
            ballCollision(0);
            brick.hit = true;
            brick.color = 0x00;
        }
    }

    if(bricksLeft == 0) reset();

    // draw
    for(Brick &brick : bricks) {
        screen.drawRect(brick.x+1, brick.y+1, brick.w-2, brick.h-2, true, brick.color);
    }

    if(plat.x != plat._x || plat.y != plat._y)
        screen.drawRect(plat._x, plat._y, plat.w, plat.h, true, 0x00); // clear last position
    screen.drawRect(plat.x, plat.y, plat.w, plat.h, true, 0xff);

    if(ball.x != ball._x || ball.y != ball._y)
        screen.drawRect(ball._x, ball._y, ball.size, ball.size, true, 0x00); // clear last position
    screen.drawRect(ball.x, ball.y, ball.size, ball.size, true, 0xff);

    return true;
}

void BrickMode::movePlat(int ct) {
    if(ball.vel == 0)
        ball.vel = startVel;
    plat._x = plat.x;
    plat._y = plat.y;

    plat.x = constrain(plat.x + ct * ball.vel * 2, 0, screen.xMax - plat.w);
}

void BrickMode::ballCollision(float norm) {
    playSound(523);
    ball.angle = 2 * norm - ball.angle;
    while(ball.angle < 0) ball.angle += M_PI * 2;
    while(ball.angle >= M_PI / 2) ball.angle -= M_PI * 2;
}
