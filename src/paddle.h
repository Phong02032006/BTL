#pragma once
#include "SDl.h"
class Paddle {
public:
    static const int PADDLE_WIDTH = 15;
    static const int PADDLE_HEIGHT = 90;
    static const int PADDLE_SPEED = 10;
    Paddle(int x, int y, int screenHeight);
    void move(bool up);
    void render(SDL_Renderer* renderer) const;
    SDL_Rect& getRect();
private:
    SDL_Rect rect;
    int screenHeight;
};
