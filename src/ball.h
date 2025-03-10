#pragma once
#pragma once
#include <SDL.h>

class Ball {
public:
    static const int BALL_SIZE = 15;

    
    Ball(int x, int y);

    
    void render(SDL_Renderer* renderer) const;

private:
    SDL_Rect rect;
};

