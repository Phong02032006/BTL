#include "ball.h"

Ball::Ball(int x, int y) {
    rect.x = x;
    rect.y = y;
    rect.w = BALL_SIZE;
    rect.h = BALL_SIZE;
    xVel = 5;
    yVel = 5;
}

void Ball::update(int screenWidth, int screenHeight, const SDL_Rect& paddleRect) {
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
        xVel = -xVel;

        // Ensure the ball doesn't get "stuck" in the edge
        if (rect.x <= 0) {
            rect.x = 0;
        }
        else {
            rect.x = screenWidth - rect.w;
        }
    }
}

void Ball::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(const SDL_Rect& rect) const {
    // Check if the ball's rectangle intersects with the given rectangle
    return SDL_HasIntersection(&this->rect, &rect);
}

void Ball::handleCollision(const SDL_Rect& rect) {
    // Reverse the ball's X velocity to bounce off the paddle
    reverseX();
}

void Ball::reset(int x, int y) {
    rect.x = x;
    rect.y = y;
    xVel = 5;
    yVel = 5;
}
