#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

bool showMenu(SDL_Renderer* renderer, TTF_Font* font);
bool showPauseMenu(SDL_Renderer* renderer, TTF_Font* font);