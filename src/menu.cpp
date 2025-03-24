#include "Menu.h"
#include <iostream>

const int SCREEN_WIDTH = 800;  
const int SCREEN_HEIGHT = 600;

bool showMenu(SDL_Renderer* renderer, TTF_Font* font) {
    
    bool menuRunning = true;
    bool startGame = false;

    // Load the image
    SDL_Surface* image_surface = IMG_Load("assets/menu_image.png");
    if (!image_surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    // Define button rectangles
    SDL_Rect play_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 50 };
    SDL_Rect quit_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 50, 100, 50 };

    while (menuRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menuRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    startGame = true;
                    menuRunning = false;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    menuRunning = false;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= play_rect.x && x <= play_rect.x + play_rect.w &&
                    y >= play_rect.y && y <= play_rect.y + play_rect.h) {
                    startGame = true;
                    menuRunning = false;
                }
                else if (x >= quit_rect.x && x <= quit_rect.x + quit_rect.w &&
                    y >= quit_rect.y && y <= quit_rect.y + quit_rect.h) {
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

        // Render title text
        SDL_Color blue = { 0, 0, 255, 255 };
        SDL_Surface* title_surface = TTF_RenderText_Solid(font, "GAME LTNC", blue);
        SDL_Texture* title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
        SDL_Rect title_rect = { SCREEN_WIDTH / 2 - title_surface->w / 2, 50, title_surface->w, title_surface->h };
        SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);
        SDL_FreeSurface(title_surface);
        SDL_DestroyTexture(title_texture);

        // Render "Play" button
        SDL_Surface* play_surface = TTF_RenderText_Solid(font, "Play", blue);
        SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
        SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);
        SDL_FreeSurface(play_surface);
        SDL_DestroyTexture(play_texture);

        // Render "Quit" button
        SDL_Surface* quit_surface = TTF_RenderText_Solid(font, "Quit", blue);
        SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
        SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rect);
        SDL_FreeSurface(quit_surface);
        SDL_DestroyTexture(quit_texture);

        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return startGame;

}
bool showPauseMenu(SDL_Renderer* renderer, TTF_Font* font) {
    bool menuRunning = true;
    bool continueGame = false;

    // T?i ?nh n?n c?a menu t?m d?ng
    SDL_Surface* image_surface = IMG_Load("assets/pause_menu.png");
    if (!image_surface) {
        std::cerr << "Failed to load pause menu image: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    // ??nh v? nút "Continue" và "Quit"
    SDL_Rect continue_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 50 };
    SDL_Rect quit_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 50, 100, 50 };

    while (menuRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menuRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    continueGame = true;
                    menuRunning = false;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    menuRunning = false;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= continue_rect.x && x <= continue_rect.x + continue_rect.w &&
                    y >= continue_rect.y && y <= continue_rect.y + continue_rect.h) {
                    continueGame = true;
                    menuRunning = false;
                }
                else if (x >= quit_rect.x && x <= quit_rect.x + quit_rect.w &&
                    y >= quit_rect.y && y <= quit_rect.y + quit_rect.h) {
                    menuRunning = false;
                }
            }
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Hi?n th? ?nh n?n
        SDL_Rect image_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);

        // Hi?n th? ch? "Continue"
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* continue_surface = TTF_RenderText_Solid(font, "Continue", white);
        SDL_Texture* continue_texture = SDL_CreateTextureFromSurface(renderer, continue_surface);
        SDL_RenderCopy(renderer, continue_texture, NULL, &continue_rect);
        SDL_FreeSurface(continue_surface);
        SDL_DestroyTexture(continue_texture);

        // Hi?n th? ch? "Quit"
        SDL_Surface* quit_surface = TTF_RenderText_Solid(font, "Quit", white);
        SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
        SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rect);
        SDL_FreeSurface(quit_surface);
        SDL_DestroyTexture(quit_texture);

        // C?p nh?t màn hình
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(image_texture);
    return continueGame;
}