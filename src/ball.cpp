#include "ball.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <random>
Mix_Chunk* paddle_hit_sound = nullptr;

Ball::Ball(int x, int y) {
    rect.x = x;
    rect.y = y;
    rect.w = BALL_SIZE;
    rect.h = BALL_SIZE;
    xVel = 3;
    yVel = 3;
}

void Ball::update(int screenWidth, int screenHeight, const SDL_Rect& paddleRect,int difficulty) {
    // Update position based on velocity
    rect.x += xVel;
    rect.y += yVel;

    // Handle collision with top and bottom screen edges
    if (rect.y <= 0 || rect.y + rect.h >= screenHeight) {
        yVel = -yVel;

        // Ensure the ball doesn't get "stuck" in the edge
        if (rect.y <= 0) {
            rect.y = 0;
        }
        else {
            rect.y = screenHeight - rect.h;
        }
    }

    // Handle collision with the paddle
    if (checkCollision(paddleRect)) {
        handleCollision(paddleRect);
    }

    // Handle collision with left and right screen edges
    if (rect.x <= 0 || rect.x + rect.w >= screenWidth) {

        reset(screenWidth, screenHeight,difficulty);
    }
}

void Ball::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(const SDL_Rect& rect) const {

    return SDL_HasIntersection(&this->rect, &rect);
}

void Ball::handleCollision(const SDL_Rect& rect) {
    if (paddle_hit_sound) {
        Mix_PlayChannel(-1, paddle_hit_sound, 0);

    }
    reverseX();
}

void Ball::reset(int screenWidth, int screenHeight, int difficulty) {
    // Đặt vị trí của quả bóng ở giữa màn hình
    rect.x = screenWidth / 2 - BALL_SIZE / 2;
    rect.y = screenHeight / 2 - BALL_SIZE / 2;

    // Thiết lập bộ sinh số ngẫu nhiên
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> directionX(-1, 1);
    std::uniform_int_distribution<> directionY(-1, 1);

    // Điều chỉnh tốc độ bóng dựa trên độ khó
    int speedMultiplier = 0;
    if (difficulty == 1) {
        speedMultiplier = 3; // Dễ
    }
    else if (difficulty == 2) {
        speedMultiplier = 5; // Trung bình
    }
    else if (difficulty == 3) {
        speedMultiplier = 7; // Khó
    }

    // Đảm bảo vận tốc không bằng 0
    do {
        xVel = speedMultiplier * directionX(gen);
    } while (xVel == 0);

    do {
        yVel = speedMultiplier * directionY(gen);
    } while (yVel == 0);
}


