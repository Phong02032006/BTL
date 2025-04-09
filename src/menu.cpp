#include "menu.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 70;
const int BUTTON_GAP = 30;
const int EXTEND_WIDTH = 20;

extern Mix_Chunk* buttonClickSound;

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, GameMode& gameMode, int& difficulty, Mix_Music* backgroundMusic, bool& musicPlaying, SDL_Texture* musicNoteTexture, SDL_Texture* musicNoteSlashTexture) {
    bool menuRunning = true;
    bool startGame = false;
    bool selectingDifficulty = false;

    // Load the image
    SDL_Surface* image_surface = IMG_Load("assets/menu_image.png");
    if (!image_surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    // Define button rectangles with gaps
    SDL_Rect pvp_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 - BUTTON_HEIGHT - BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect pve_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect quit_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 + BUTTON_HEIGHT + BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect music_toggle_rect = { SCREEN_WIDTH - 60, 20, 40, 40 }; // Small circular button

    SDL_Rect easy_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 - BUTTON_HEIGHT - BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect medium_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect hard_rect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100 + BUTTON_HEIGHT + BUTTON_GAP, BUTTON_WIDTH, BUTTON_HEIGHT };

    // Define extended rectangles for buttons
    SDL_Rect extended_pvp_rect = { pvp_rect.x - EXTEND_WIDTH, pvp_rect.y, pvp_rect.w + 2 * EXTEND_WIDTH, pvp_rect.h };
    SDL_Rect extended_pve_rect = { pve_rect.x - EXTEND_WIDTH, pve_rect.y, pve_rect.w + 2 * EXTEND_WIDTH, pve_rect.h };
    SDL_Rect extended_quit_rect = { quit_rect.x - EXTEND_WIDTH, quit_rect.y, quit_rect.w + 2 * EXTEND_WIDTH, quit_rect.h };

    SDL_Rect extended_easy_rect = { easy_rect.x - EXTEND_WIDTH, easy_rect.y, easy_rect.w + 2 * EXTEND_WIDTH, easy_rect.h };
    SDL_Rect extended_medium_rect = { medium_rect.x - EXTEND_WIDTH, medium_rect.y, medium_rect.w + 2 * EXTEND_WIDTH, medium_rect.h };
    SDL_Rect extended_hard_rect = { hard_rect.x - EXTEND_WIDTH, hard_rect.y, hard_rect.w + 2 * EXTEND_WIDTH, hard_rect.h };

    // Play background music
    if (musicPlaying) {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    while (menuRunning) {
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
                    if (x >= pvp_rect.x && x <= pvp_rect.x + pvp_rect.w &&
                        y >= pvp_rect.y && y <= pvp_rect.y + pvp_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        gameMode = PVP;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (x >= pve_rect.x && x <= pve_rect.x + pve_rect.w &&
                        y >= pve_rect.y && y <= pve_rect.y + pve_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        selectingDifficulty = true;
                    }
                    else if (x >= quit_rect.x && x <= quit_rect.x + quit_rect.w &&
                        y >= quit_rect.y && y <= quit_rect.y + quit_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        menuRunning = false;
                    }
                    else if (x >= music_toggle_rect.x && x <= music_toggle_rect.x + music_toggle_rect.w &&
                        y >= music_toggle_rect.y && y <= music_toggle_rect.y + music_toggle_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
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
                    if (x >= easy_rect.x && x <= easy_rect.x + easy_rect.w &&
                        y >= easy_rect.y && y <= easy_rect.y + easy_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        difficulty = 1;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (x >= medium_rect.x && x <= medium_rect.x + medium_rect.w &&
                        y >= medium_rect.y && y <= medium_rect.y + medium_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        difficulty = 2;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                    else if (x >= hard_rect.x && x <= hard_rect.x + hard_rect.w &&
                        y >= hard_rect.y && y <= hard_rect.y + hard_rect.h) {
                        Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                        difficulty = 3;
                        gameMode = PVE;
                        startGame = true;
                        menuRunning = false;
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the image to cover the entire screen
        SDL_Rect image_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);

        // Render title text
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* title_surface = TTF_RenderText_Solid(font, "GAME LTNC", white);
        SDL_Texture* title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
        SDL_Rect title_rect = { SCREEN_WIDTH / 2 - title_surface->w / 2, 50, title_surface->w, title_surface->h };
        SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);
        SDL_FreeSurface(title_surface);
        SDL_DestroyTexture(title_texture);

        if (!selectingDifficulty) {
            // Render "PVP" button
            SDL_Surface* pvp_surface = TTF_RenderText_Solid(font, "PVP", white);
            SDL_Texture* pvp_texture = SDL_CreateTextureFromSurface(renderer, pvp_surface);
            SDL_RenderCopy(renderer, pvp_texture, NULL, &pvp_rect);
            SDL_FreeSurface(pvp_surface);
            SDL_DestroyTexture(pvp_texture);

            // Draw extended rectangle around "PVP" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_pvp_rect);

            // Render "PVE" button
            SDL_Surface* pve_surface = TTF_RenderText_Solid(font, "PVE", white);
            SDL_Texture* pve_texture = SDL_CreateTextureFromSurface(renderer, pve_surface);
            SDL_RenderCopy(renderer, pve_texture, NULL, &pve_rect);
            SDL_FreeSurface(pve_surface);
            SDL_DestroyTexture(pve_texture);

            // Draw extended rectangle around "PVE" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_pve_rect);

            // Render "Quit" button
            SDL_Surface* quit_surface = TTF_RenderText_Solid(font, "Quit", white);
            SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
            SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rect);
            SDL_FreeSurface(quit_surface);
            SDL_DestroyTexture(quit_texture);

            // Draw extended rectangle around "Quit" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_quit_rect);

            // Render "Music Toggle" button
            if (musicPlaying) {
                SDL_RenderCopy(renderer, musicNoteTexture, NULL, &music_toggle_rect);
            }
            else {
                SDL_RenderCopy(renderer, musicNoteSlashTexture, NULL, &music_toggle_rect);
            }
        }
        else {
            // Render "Easy" button
            SDL_Surface* easy_surface = TTF_RenderText_Solid(font, "Easy", white);
            SDL_Texture* easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
            SDL_RenderCopy(renderer, easy_texture, NULL, &easy_rect);
            SDL_FreeSurface(easy_surface);
            SDL_DestroyTexture(easy_texture);

            // Draw extended rectangle around "Easy" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_easy_rect);

            // Render "Medium" button
            SDL_Surface* medium_surface = TTF_RenderText_Solid(font, "Medium", white);
            SDL_Texture* medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
            SDL_RenderCopy(renderer, medium_texture, NULL, &medium_rect);
            SDL_FreeSurface(medium_surface);
            SDL_DestroyTexture(medium_texture);

            // Draw extended rectangle around "Medium" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_medium_rect);

            // Render "Hard" button
            SDL_Surface* hard_surface = TTF_RenderText_Solid(font, "Hard", white);
            SDL_Texture* hard_texture = SDL_CreateTextureFromSurface(renderer, hard_surface);
            SDL_RenderCopy(renderer, hard_texture, NULL, &hard_rect);
            SDL_FreeSurface(hard_surface);
            SDL_DestroyTexture(hard_texture);

            // Draw extended rectangle around "Hard" button
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &extended_hard_rect);
        }

        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return startGame;
}

int showPauseMenu(SDL_Renderer* renderer, TTF_Font* font) {
    bool menuRunning = true;
    int returnValue = 0; // 0: Continue, 1: Main Menu, -1: Quit

    // Load the image
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

    // Define extended rectangles for buttons
    SDL_Rect extended_continue_rect = { continue_rect.x - EXTEND_WIDTH, continue_rect.y, continue_rect.w + 2 * EXTEND_WIDTH, continue_rect.h };
    SDL_Rect extended_main_menu_rect = { main_menu_rect.x - EXTEND_WIDTH, main_menu_rect.y, main_menu_rect.w + 2 * EXTEND_WIDTH, main_menu_rect.h };

    while (menuRunning) {
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
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= continue_rect.x && x <= continue_rect.x + continue_rect.w &&
                    y >= continue_rect.y && y <= continue_rect.y + continue_rect.h) {
                    Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                    returnValue = 0;
                    menuRunning = false;
                }
                else if (x >= main_menu_rect.x && x <= main_menu_rect.x + main_menu_rect.w &&
                    y >= main_menu_rect.y && y <= main_menu_rect.y + main_menu_rect.h) {
                    Mix_PlayChannel(-1, buttonClickSound, 0); // Play button click sound
                    returnValue = 1;
                    menuRunning = false;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the image to cover the entire screen
        SDL_Rect image_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);

        // Render "Continue" button
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* continue_surface = TTF_RenderText_Solid(font, "Continue", white);
        SDL_Texture* continue_texture = SDL_CreateTextureFromSurface(renderer, continue_surface);
        SDL_RenderCopy(renderer, continue_texture, NULL, &continue_rect);
        SDL_FreeSurface(continue_surface);
        SDL_DestroyTexture(continue_texture);

        // Draw extended rectangle around "Continue" button
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &extended_continue_rect);

        // Render "Main Menu" button
        SDL_Surface* main_menu_surface = TTF_RenderText_Solid(font, "Main Menu", white);
        SDL_Texture* main_menu_texture = SDL_CreateTextureFromSurface(renderer, main_menu_surface);
        SDL_RenderCopy(renderer, main_menu_texture, NULL, &main_menu_rect);
        SDL_FreeSurface(main_menu_surface);
        SDL_DestroyTexture(main_menu_texture);

        // Draw extended rectangle around "Main Menu" button
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &extended_main_menu_rect);

        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return returnValue;
}
