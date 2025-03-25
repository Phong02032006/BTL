
#pragma once
#include "Paddle.h"
#include "Ball.h"

class Bot {
public:
    Bot(Paddle& paddle, const Ball& ball, int difficulty);

    void update();

private:
    Paddle& paddle;
    const Ball& ball;
    int difficulty;
};
