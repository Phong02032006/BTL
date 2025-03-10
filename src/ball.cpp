#include "ball.h"

Ball::Ball(int x, int y) {
    
    rect.x = x;
    rect.y = y;
    rect.w = BALL_SIZE;
    rect.h = BALL_SIZE;
}

void Ball::render(SDL_Renderer* renderer) const {
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
