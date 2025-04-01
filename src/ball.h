#pragma once
#include <SDL.h>

class Ball {
public:
    static const int BALL_SIZE = 15;
    int xVel;
    int yVel;

    Ball(int x, int y);

    void update(int screenWidth, int screenHeight, const SDL_Rect& paddleRect);
    void render(SDL_Renderer* renderer) const;
    bool checkCollision(const SDL_Rect& rect) const;
    void handleCollision(const SDL_Rect& rect);
    SDL_Rect getRect() const { return rect; }
    void reverseX() { xVel = -xVel; }
    void reverseY() { yVel = -yVel; }
    void reset(int x, int y);
   

private:
    SDL_Rect rect;
    
};
