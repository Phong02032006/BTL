#include "bot.h"
#include "ball.h"
#include <cmath>
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

    if (difficulty == 1) {
        speed *= 1.5; // Dễ: tốc độ chậm hơn
        predictionFactor = 0.2f; // Dự đoán ít chính xác hơn
		
    }
    else if (difficulty == 2) {
        speed *= 3.6; // Trung bình: tốc độ bình thường
        predictionFactor = 0.85f; // Dự đoán tương đối chính xác
    }
    else if (difficulty == 3) {
        speed *= 5.0; // Khó: tốc độ nhanh hơn
        predictionFactor = 1.0f; // Dự đoán chính xác
    }

    // Dự đoán vị trí bóng trong tương lai
    int predictedBallY = ballY + static_cast<int>(ball.yVel * predictionFactor);

    // Thêm yếu tố ngẫu nhiên nhỏ để bot không quá hoàn hảo
    predictedBallY += rand() % 6 - 3;

    // Tính toán vị trí đích của paddle
    int targetY = predictedBallY - Paddle::PADDLE_HEIGHT / 2;

    // Sử dụng interpolation để di chuyển mượt mà
    float deltaY = targetY - paddleY;
    float dampingFactor = 0.2f; // Yếu tố giảm xóc để làm mượt chuyển động
    paddle.rect.y += static_cast<int>(deltaY * dampingFactor);

    // Đảm bảo paddle không di chuyển ra khỏi màn hình
    if (paddle.rect.y < 0) {
        paddle.rect.y = 0;
    }
    else if (paddle.rect.y > SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) {
        paddle.rect.y = SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT;
    }
}
