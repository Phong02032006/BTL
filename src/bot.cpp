#include "bot.h"
#include "ball.h"
#include <cmath>
#include <cstdlib> /
const int SCREEN_HEIGHT = 600;

Bot::Bot(Paddle& paddle, const Ball& ball, int difficulty)
    : paddle(paddle), ball(ball), difficulty(difficulty) {
}

void Bot::update() {
    int ballY = ball.getRect().y;
    int paddleY = paddle.getRect().y;

    // Điều chỉnh tốc độ và độ khó
    float speed = Paddle::PADDLE_SPEED;
    float predictionFactor = 1.0f;
    float randomnessFactor = 0.0f; // Yếu tố ngẫu nhiên

    if (difficulty == 1) {
        speed *= 0.4f; // Dễ: tốc độ chậm hơn
        predictionFactor = 0.6f; // Dự đoán ít chính xác hơn
        randomnessFactor = 15.0f; // Ngẫu nhiên lớn hơn
    }
    else if (difficulty == 2) {
        speed *= 0.8f; // Trung bình: tốc độ bình thường
        predictionFactor = 0.85f; // Dự đoán tương đối chính xác
        randomnessFactor = 8.0f; // Ngẫu nhiên vừa phải
    }
    else if (difficulty == 3) {
        speed *= 1.2f; // Khó: tốc độ nhanh hơn
        predictionFactor = 1.0f; // Dự đoán chính xác
        randomnessFactor = 3.0f; // Ít ngẫu nhiên hơn
    }

    // Dự đoán vị trí bóng trong tương lai
    int predictedBallY = ballY + static_cast<int>(ball.yVel * predictionFactor);

    // Thêm yếu tố ngẫu nhiên để bot không quá hoàn hảo
    predictedBallY += rand() % static_cast<int>(randomnessFactor) - static_cast<int>(randomnessFactor / 2);

    // Tính toán vị trí đích của paddle
    int targetY = predictedBallY - Paddle::PADDLE_HEIGHT / 2;

    // Làm mượt chuyển động bằng easing
    float deltaY = targetY - paddleY;
    float easingFactor = 0.1f; // Hệ số easing để làm mượt chuyển động
    paddle.rect.y += static_cast<int>(deltaY * easingFactor * speed);

    // Đảm bảo paddle không di chuyển ra khỏi màn hình
    if (paddle.rect.y < 0) {
        paddle.rect.y = 0;
    }
    else if (paddle.rect.y > SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) {
        paddle.rect.y = SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT;
    }
}
