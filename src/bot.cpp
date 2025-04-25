#include "bot.h"
#include "ball.h"
#include <cmath>
#include <cstdlib> 
const int SCREEN_HEIGHT = 600;

Bot::Bot(Paddle& paddle, const Ball& ball, int difficulty)
    : paddle(paddle), ball(ball), difficulty(difficulty) {
}

void Bot::update() {

    int ballY = ball.getRect().y;
    int paddleY = paddle.getRect().y;

    float speed = Paddle::PADDLE_SPEED;
    float predictionFactor = 1.0f;
    float randomnessFactor = 0.0f;

    if (difficulty == 1) {
        speed *= 0.4f;
        predictionFactor = 0.6f;
        randomnessFactor = 15.0f;
    }
    else if (difficulty == 2) {
        speed *= 0.8f;
        predictionFactor = 0.85f;
        randomnessFactor = 8.0f;
    }
    else if (difficulty == 3) {
        speed *= 1.2f;
        predictionFactor = 1.0f;
        randomnessFactor = 3.0f;

    }
        int predictedBallY = ballY + static_cast<int>(ball.yVel * predictionFactor);

        predictedBallY += rand() % static_cast<int>(randomnessFactor) - static_cast<int>(randomnessFactor / 2);

        int targetY = predictedBallY - Paddle::PADDLE_HEIGHT / 2;

        float deltaY = targetY - paddleY;
        float easingFactor = 0.1f;
        paddle.rect.y += static_cast<int>(deltaY * easingFactor * speed);

        if (paddle.rect.y < 0) {
            paddle.rect.y = 0;
        }
        else if (paddle.rect.y > SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) {
            paddle.rect.y = SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT;
        }
    }

