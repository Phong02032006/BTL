#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

enum GameMode {
    PVP,
    PVE
};

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, GameMode& gameMode, int& difficulty, Mix_Music* backgroundMusic, bool& musicPlaying, SDL_Texture* musicNoteTexture);
int showPauseMenu(SDL_Renderer* renderer, TTF_Font* font);

