#include "bot.h"

Bot::Bot(Paddle& paddle, const Ball& ball, int difficulty)
    : paddle(paddle), ball(ball), difficulty(difficulty) {
}

void Bot::update() {
    int ballY = ball.getRect().y;
    int paddleY = paddle.getRect().y;

    // Adjust the bot's movement speed and reaction delay based on the difficulty level
    int speed = Paddle::PADDLE_SPEED;
    int reactionDelay = 0;

    if (difficulty == 1) {
        speed *= 2.0; // Easy: slower speed
        reactionDelay = 6; // Easy: longer delay
    }
    else if (difficulty == 2) {
        speed *= 3.0; // Medium: normal speed
        reactionDelay = 2; // Medium: shorter delay
    }
    else if (difficulty == 3) {
        speed *= 4.5; // Hard: faster speed
        reactionDelay = 0; // Hard: no delay
    }

    static int frameCounter = 0;
    if (frameCounter < reactionDelay) {
        frameCounter++;
        return;
    }
    frameCounter = 0;

    if (ballY < paddleY) {
        paddle.move(true);
    }
    else if (ballY > paddleY + Paddle::PADDLE_HEIGHT) {
        paddle.move(false);
    }
}

