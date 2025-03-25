#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

enum GameMode {
    PVP,
    PVE
};

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, GameMode& gameMode, int& difficulty);
int showPauseMenu(SDL_Renderer* renderer, TTF_Font* font);
