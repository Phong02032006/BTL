#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
enum GameMode {
    PVP,
    PVE
};

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, GameMode& gameMode, int& difficulty, Mix_Music* backgroundMusic, bool& musicPlaying, SDL_Texture* musicNoteTexture, SDL_Texture* musicNoteSlashTexture);

int showPauseMenu(SDL_Renderer* renderer, TTF_Font* font);

#endif // MENU_H
