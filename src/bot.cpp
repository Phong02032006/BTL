#include "bot.h"
#include <cmath>

Bot::Bot(Paddle& paddle, const Ball& ball, int difficulty)
    : paddle(paddle), ball(ball), difficulty(difficulty) {
}

void Bot::update() {
    int ballY = ball.getRect().y;
    int paddleY = paddle.getRect().y;

    // Adjust the bot's movement speed and reaction delay based on the difficulty level
    float speed = Paddle::PADDLE_SPEED;
    int reactionDelay = 0;
    float predictionFactor = 1.0f;

    if (difficulty == 1) {
        speed *= 0.75; // Easy: slower speed
        reactionDelay = 6; // Easy: longer delay
        predictionFactor = 0.5f; // Easy: less accurate prediction
    }
    else if (difficulty == 2) {
        speed *= 1.0; // Medium: normal speed
        reactionDelay = 2; // Medium: shorter delay
        predictionFactor = 0.75f; // Medium: moderately accurate prediction
    }
    else if (difficulty == 3) {
        speed *= 1.5; // Hard: faster speed
        reactionDelay = 0; // Hard: no delay
        predictionFactor = 1.0f; // Hard: accurate prediction
    }

    static int frameCounter = 0;
    if (frameCounter < reactionDelay) {
        frameCounter++;
    }
    else {
        frameCounter = 0;
    }


    // Predict the future position of the ball
    int predictedBallY = ballY + static_cast<int>(ball.yVel * predictionFactor);

    // Adjust the prediction based on the ball's direction and speed
    if (ball.yVel > 0) {
        predictedBallY += ball.yVel * predictionFactor;
    }
    else {
        predictedBallY -= ball.yVel * predictionFactor;
    }

    // Introduce a small amount of randomness to the bot's movement
    predictedBallY += rand() % 6 - 3;

    // Move the paddle smoothly towards the predicted position
    // Tính toán vị trí mới của paddle dựa trên tốc độ
    int targetY = paddleY + (predictedBallY - (paddleY + Paddle::PADDLE_HEIGHT / 2)) * 0.1f;
    if (targetY < paddleY) {
        paddle.move(true);
    }
    else if (targetY > paddleY) {
        paddle.move(false);
    }


}


