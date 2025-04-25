#include "menu.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 70;
const int BUTTON_GAP = 30;
const int EXTEND_WIDTH = 20;

extern Mix_Chunk* buttonClickSound;

void renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect& rect, SDL_Rect& extended_rect, bool isHovered) {
    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, text_texture, NULL, &rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    if (isHovered) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    SDL_RenderDrawRect(renderer, &extended_rect);
}

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, GameMode& gameMode, int& difficulty, Mix_Music* backgroundMusic, bool& musicPlaying, SDL_Texture* musicNoteTexture, SDL_Texture* musicNoteSlashTexture) {
    bool menuRunning = true;
    bool startGame = false;
    bool selectingDifficulty = false;

    SDL_Surface* image_surface = IMG_Load("assets/menu_image.png");
    if (!image_surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    SDL_Rect pvp_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 - BUTTON_HEIGHT - BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect pve_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect quit_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 + BUTTON_HEIGHT + BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect music_toggle_rect = { SCREEN_WIDTH - 60, 20, 40, 40 };

    SDL_Rect easy_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 - BUTTON_HEIGHT - BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect medium_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect hard_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 + BUTTON_HEIGHT + BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };

    SDL_Rect extended_pvp_rect = { pvp_rect.x - EXTEND_WIDTH, pvp_rect.y, pvp_rect.w + 2 * EXTEND_WIDTH, pvp_rect.h };
    SDL_Rect extended_pve_rect = { pve_rect.x - EXTEND_WIDTH, pve_rect.y, pve_rect.w + 2 * EXTEND_WIDTH, pve_rect.h };
    SDL_Rect extended_quit_rect = { quit_rect.x - EXTEND_WIDTH, quit_rect.y, quit_rect.w + 2 * EXTEND_WIDTH, quit_rect.h };

    SDL_Rect extended_easy_rect = { easy_rect.x - EXTEND_WIDTH, easy_rect.y, easy_rect.w + 2 * EXTEND_WIDTH, easy_rect.h };
    SDL_Rect extended_medium_rect = { medium_rect.x - EXTEND_WIDTH, medium_rect.y, medium_rect.w + 2 * EXTEND_WIDTH, medium_rect.h };
    SDL_Rect extended_hard_rect = { hard_rect.x - EXTEND_WIDTH, hard_rect.y, hard_rect.w + 2 * EXTEND_WIDTH, hard_rect.h };

    if (musicPlaying) {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    while (menuRunning) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool hoverPvp = false;
        bool hoverPve = false;
        bool hoverQuit = false;
        bool hoverMusic = false;
        bool hoverEasy = false;
        bool hoverMedium = false;
        bool hoverHard = false;

        if (!selectingDifficulty) {
            hoverPvp = mouseX >= pvp_rect.x && mouseX <= pvp_rect.x + pvp_rect.w &&
                mouseY >= pvp_rect.y && mouseY <= pvp_rect.y + pvp_rect.h;
            hoverPve = mouseX >= pve_rect.x && mouseX <= pve_rect.x + pve_rect.w &&
                mouseY >= pve_rect.y && mouseY <= pve_rect.y + pve_rect.h;
            hoverQuit = mouseX >= quit_rect.x && mouseX <= quit_rect.x + quit_rect.w &&
                mouseY >= quit_rect.y && mouseY <= quit_rect.y + quit_rect.h;
            hoverMusic = mouseX >= music_toggle_rect.x && mouseX <= music_toggle_rect.x + music_toggle_rect.w &&
                mouseY >= music_toggle_rect.y && mouseY <= music_toggle_rect.y + music_toggle_rect.h;
        }
        else {
            hoverEasy = mouseX >= easy_rect.x && mouseX <= easy_rect.x + easy_rect.w &&
                mouseY >= easy_rect.y && mouseY <= easy_rect.y + easy_rect.h;
            hoverMedium = mouseX >= medium_rect.x && mouseX <= medium_rect.x + medium_rect.w &&
                mouseY >= medium_rect.y && mouseY <= medium_rect.y + medium_rect.h;
            hoverHard = mouseX >= hard_rect.x && mouseX <= hard_rect.x + hard_rect.w &&
                mouseY >= hard_rect.y && mouseY <= hard_rect.y + hard_rect.h;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menuRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    if (selectingDifficulty) {
                        selectingDifficulty = false;
                    }
                    else {
                        menuRunning = false;
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (!selectingDifficulty) {
                    if (hoverPvp) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        gameMode = PVP;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (hoverPve) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        selectingDifficulty = true;
                    }
                    else if (hoverQuit) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        menuRunning = false;
                    }
                    else if (hoverMusic) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        if (musicPlaying) {
                            Mix_PauseMusic();
                        }
                        else {
                            Mix_ResumeMusic();
                        }
                        musicPlaying = !musicPlaying;
                    }
                }
                else {
                    if (hoverEasy) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        difficulty = 1;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (hoverMedium) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        difficulty = 2;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (hoverHard) {
                        Mix_PlayChannel(-1, buttonClickSound, 0);
                        difficulty = 3;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect image_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);

        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* title_surface = TTF_RenderText_Solid(font, "GAME LTNC", white);
        SDL_Texture* title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
        SDL_Rect title_rect = { SCREEN_WIDTH / 2 - title_surface->w / 2, 50, title_surface->w, title_surface->h };
        SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);
        SDL_FreeSurface(title_surface);
        SDL_DestroyTexture(title_texture);

        if (!selectingDifficulty) {
            renderButton(renderer, font, "PVP", pvp_rect, extended_pvp_rect, hoverPvp);
            renderButton(renderer, font, "PVE", pve_rect, extended_pve_rect, hoverPve);
            renderButton(renderer, font, "Quit", quit_rect, extended_quit_rect, hoverQuit);

            if (hoverMusic) {
                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
                SDL_Rect music_border = { music_toggle_rect.x - 2, music_toggle_rect.y - 2,
                                         music_toggle_rect.w + 4, music_toggle_rect.h + 4 };
                SDL_RenderDrawRect(renderer, &music_border);
            }

            if (musicPlaying) {
                SDL_RenderCopy(renderer, musicNoteTexture, NULL, &music_toggle_rect);
            }
            else {
                SDL_RenderCopy(renderer, musicNoteSlashTexture, NULL, &music_toggle_rect);
            }
        }
        else {
            renderButton(renderer, font, "Easy", easy_rect, extended_easy_rect, hoverEasy);
            renderButton(renderer, font, "Medium", medium_rect, extended_medium_rect, hoverMedium);
            renderButton(renderer, font, "Hard", hard_rect, extended_hard_rect, hoverHard);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return startGame;
}

int showPauseMenu(SDL_Renderer* renderer, TTF_Font* font) {
    bool menuRunning = true;
    int returnValue = 0;

    SDL_Surface* image_surface = IMG_Load("assets/pause_menu.png");
    if (!image_surface) {
        std::cerr << "Failed to load pause menu image: " << IMG_GetError() << std::endl;
        return -1;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    int totalHeight = 2 * BUTTON_HEIGHT + BUTTON_GAP;
    int startY = (SCREEN_HEIGHT - totalHeight) / 2;

    SDL_Rect continue_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, startY, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect main_menu_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, startY + BUTTON_HEIGHT + BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };

    SDL_Rect extended_continue_rect = { continue_rect.x - EXTEND_WIDTH, continue_rect.y, continue_rect.w + 2 * EXTEND_WIDTH, continue_rect.h };
    SDL_Rect extended_main_menu_rect = { main_menu_rect.x - EXTEND_WIDTH, main_menu_rect.y, main_menu_rect.w + 2 * EXTEND_WIDTH, main_menu_rect.h };

    while (menuRunning) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool hoverContinue = mouseX >= continue_rect.x && mouseX <= continue_rect.x + continue_rect.w &&
            mouseY >= continue_rect.y && mouseY <= continue_rect.y + continue_rect.h;
        bool hoverMainMenu = mouseX >= main_menu_rect.x && mouseX <= main_menu_rect.x + main_menu_rect.w &&
            mouseY >= main_menu_rect.y && mouseY <= main_menu_rect.y + main_menu_rect.h;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                returnValue = -1;
                menuRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    returnValue = 0;
                    menuRunning = false;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (hoverContinue) {
                    Mix_PlayChannel(-1, buttonClickSound, 0);
                    returnValue = 0;
                    menuRunning = false;
                }
                else if (hoverMainMenu) {
                    Mix_PlayChannel(-1, buttonClickSound, 0);
                    returnValue = 1;
                    menuRunning = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect image_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);

        renderButton(renderer, font, "Continue", continue_rect, extended_continue_rect, hoverContinue);
        renderButton(renderer, font, "Main Menu", main_menu_rect, extended_main_menu_rect, hoverMainMenu);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return returnValue;
}
