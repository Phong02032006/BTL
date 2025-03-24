#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "Paddle.h"
#include <iostream>
#include "ball.h"
#include <string>
#include "menu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int LINE_THICKNESS = 5;

extern Mix_Chunk* paddle_hit_sound;


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        return -1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("PONG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/test.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }

    paddle_hit_sound = Mix_LoadWAV("assets/sound2.wav");
    if (!paddle_hit_sound) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
        return -1;
    }

    if (!showMenu(renderer, font)) {
        // User chose to quit from the menu
        TTF_CloseFont(font);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    Paddle left_paddle(20, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
    Paddle right_paddle(SCREEN_WIDTH - 20 - Paddle::PADDLE_WIDTH, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
    Ball ball(SCREEN_WIDTH / 2 - Ball::BALL_SIZE / 2, SCREEN_HEIGHT / 2 - Ball::BALL_SIZE / 2);

    int left_score = 0;
    int right_score = 0;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_ESCAPE]) {
            if (!showPauseMenu(renderer, font)) { 
                running = false;
            }
        }

        if (state[SDL_SCANCODE_W]) left_paddle.move(true);
        if (state[SDL_SCANCODE_S]) left_paddle.move(false);
        if (state[SDL_SCANCODE_UP]) right_paddle.move(true);
        if (state[SDL_SCANCODE_DOWN]) right_paddle.move(false);

        ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, left_paddle.getRect());
        ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, right_paddle.getRect());

        // Update scores
        if (ball.getRect().x <= 5) { 
            right_score++;
            ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        else if (ball.getRect().x + ball.getRect().w >= SCREEN_WIDTH - 5) {
            left_score++;
            ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render paddles and ball
        left_paddle.render(renderer);
        right_paddle.render(renderer);
        ball.render(renderer);

        // Render center line (net)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int y = 0; y < SCREEN_HEIGHT; y += 15) {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, y, SCREEN_WIDTH / 2, y + 10);
        }

        // Render top and bottom horizontal lines with thickness
        for (int i = 0; i < LINE_THICKNESS; ++i) {
            SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i); // Top line
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - 1 - i, SCREEN_WIDTH, SCREEN_HEIGHT - 1 - i); // Bottom line
        }

        // Render scores
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* left_score_surface = TTF_RenderText_Solid(font, std::to_string(left_score).c_str(), white);
        SDL_Texture* left_score_texture = SDL_CreateTextureFromSurface(renderer, left_score_surface);
        SDL_Rect left_score_rect = { SCREEN_WIDTH / 4 - left_score_surface->w / 2, 20, left_score_surface->w, left_score_surface->h };
        SDL_RenderCopy(renderer, left_score_texture, NULL, &left_score_rect);
        SDL_FreeSurface(left_score_surface);
        SDL_DestroyTexture(left_score_texture);

        SDL_Surface* right_score_surface = TTF_RenderText_Solid(font, std::to_string(right_score).c_str(), white);
        SDL_Texture* right_score_texture = SDL_CreateTextureFromSurface(renderer, right_score_surface);
        SDL_Rect right_score_rect = { 3 * SCREEN_WIDTH / 4 - right_score_surface->w / 2, 20, right_score_surface->w, right_score_surface->h };
        SDL_RenderCopy(renderer, right_score_texture, NULL, &right_score_rect);
        SDL_FreeSurface(right_score_surface);
        SDL_DestroyTexture(right_score_texture);

        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    Mix_FreeChunk(paddle_hit_sound);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
