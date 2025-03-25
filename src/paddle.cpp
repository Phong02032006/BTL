#include "paddle.h"
#include <algorithm>
Paddle::Paddle(int x, int y, int sh) :screenHeight(sh) {
    rect.x = x;
    rect.y = y;
    rect.w = PADDLE_WIDTH;
    rect.h = PADDLE_HEIGHT;
}

void Paddle::move(bool up) {
    if (up) {
        rect.y -= PADDLE_SPEED;
    }
    else {
        rect.y += PADDLE_SPEED;
    }
    rect.y = std::max(0, std::min(screenHeight - PADDLE_HEIGHT, rect.y));
}



void Paddle::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}
SDL_Rect& Paddle::getRect() {
    return rect;
}