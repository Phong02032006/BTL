#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "Paddle.h"
#include "Ball.h"
#include "bot.h"
#include "menu.h"
#include <iostream>
#include <string>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int LINE_THICKNESS = 5;

const int WINNING_SCORE = 5;
bool gameOver = false;
std::string winnerText = "";

extern Mix_Chunk* paddle_hit_sound;
Mix_Chunk* buttonClickSound = nullptr;

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

    buttonClickSound = Mix_LoadWAV("assets/button_click.wav");
    if (!buttonClickSound) {
        std::cerr << "Failed to load button click sound effect: " << Mix_GetError() << std::endl;
        return -1;
    }

    
    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/background_music3.wav");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        return -1;
    }
    bool musicPlaying = true;

    
    SDL_Surface* music_note_surface = IMG_Load("assets/music_note.png");
    if (!music_note_surface) {
        std::cerr << "Failed to load music note icon: " << IMG_GetError() << std::endl;
        return -1;
    }
    SDL_Texture* music_note_texture = SDL_CreateTextureFromSurface(renderer, music_note_surface);
    SDL_FreeSurface(music_note_surface);

    SDL_Surface* music_note_slash_surface = IMG_Load("assets/music_note_slash.png");
    if (!music_note_slash_surface) {
        std::cerr << "Failed to load slashed music note icon: " << IMG_GetError() << std::endl;
        return -1;
    }
    SDL_Texture* music_note_slash_texture = SDL_CreateTextureFromSurface(renderer, music_note_slash_surface);
    SDL_FreeSurface(music_note_slash_surface);

    SDL_SetTextureBlendMode(music_note_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(music_note_slash_texture, SDL_BLENDMODE_BLEND);

    while (true) {
        GameMode gameMode;
        int difficulty = 1;
        if (!showMenu(renderer, font, gameMode, difficulty, backgroundMusic, musicPlaying, music_note_texture, music_note_slash_texture)) {
            break;
        }

        Paddle left_paddle(20, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
        Paddle right_paddle(SCREEN_WIDTH - 20 - Paddle::PADDLE_WIDTH, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
        Ball ball(SCREEN_WIDTH / 2 - Ball::BALL_SIZE / 2, SCREEN_HEIGHT / 2 - Ball::BALL_SIZE / 2);

        if (difficulty == 1) {
            ball.xVel = (rand() % 3 + 2); 
            ball.yVel = (rand() % 3 + 2); 
        }
        else if (difficulty == 2) {
            ball.xVel = (rand() % 4 + 4); 
            ball.yVel = (rand() % 4 + 4); 
        }
        else if (difficulty == 3) {
            ball.xVel = (rand() % 5 + 7); 
            ball.yVel = (rand() % 5 + 7); 
        }

       
        if (rand() % 2 == 0) ball.xVel = -ball.xVel; 
        if (rand() % 2 == 0) ball.yVel = -ball.yVel;


        Bot* bot = nullptr;
        if (gameMode == PVE) {
            bot = new Bot(right_paddle, ball, difficulty);
        }

        int left_score = 0;
        int right_score = 0;

        bool running = true;
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    break;
                }
                else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    if (gameOver) {
                        running = false;
                    }
                    else {
                        int pauseResult = showPauseMenu(renderer, font);
                        if (pauseResult == -1) {
                            running = false;
                        }
                        else if (pauseResult == 1) {
                            running = false;
                            break;
                        }
                    }
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    SDL_Rect music_toggle_rect = { SCREEN_WIDTH - 60, 20, 40, 40 };
                    if (x >= music_toggle_rect.x && x <= music_toggle_rect.x + music_toggle_rect.w &&
                        y >= music_toggle_rect.y && y <= music_toggle_rect.y + music_toggle_rect.h) {
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
            }

            if (!running) break;

            const Uint8* state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_W]) left_paddle.move(true);
            if (state[SDL_SCANCODE_S]) left_paddle.move(false);

            if (gameMode == PVP) {
                if (state[SDL_SCANCODE_UP]) right_paddle.move(true);
                if (state[SDL_SCANCODE_DOWN]) right_paddle.move(false);
            }
            else if (gameMode == PVE) {
                bot->update();
            }

            ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, left_paddle.getRect(), difficulty);
            ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, right_paddle.getRect(), difficulty);

            
            if (ball.getRect().x <= 5) {
                right_score++;
                ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, difficulty);
            }
            else if (ball.getRect().x + ball.getRect().w >= SCREEN_WIDTH - 5) {
                left_score++;
                ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, difficulty);
            }

            if (left_score >= WINNING_SCORE) {
                gameOver = true;
                winnerText = "Left Player Wins!";
            }
            else if (right_score >= WINNING_SCORE) {
                gameOver = true;
                winnerText = "Right Player Wins!";
            }

           
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            left_paddle.render(renderer);
            right_paddle.render(renderer);
            ball.render(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            for (int y = 0; y < SCREEN_HEIGHT; y += 15) {
                SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, y, SCREEN_WIDTH / 2, y + 10);
            }

           
            for (int i = 0; i < LINE_THICKNESS; ++i) {
                SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i); 
                SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - 1 - i, SCREEN_WIDTH, SCREEN_HEIGHT - 1 - i);
            }

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

            SDL_Rect music_toggle_rect = { SCREEN_WIDTH - 60, 20, 40, 40 };
            if (musicPlaying) {
                SDL_RenderCopy(renderer, music_note_texture, NULL, &music_toggle_rect);
            }
            else {
                SDL_RenderCopy(renderer, music_note_slash_texture, NULL, &music_toggle_rect);
            }

            if (gameMode == PVE) {
                if (left_score >= WINNING_SCORE) {
                    gameOver = true;
                    winnerText = "You Win!"; 
                }
                else if (right_score >= WINNING_SCORE) {
                    gameOver = true;
                    winnerText = "You Lose!"; 
                }
            }
            else if (gameMode == PVP) {
                if (left_score >= WINNING_SCORE) {
                    gameOver = true;
                    winnerText = "Left Player Wins!";
                }
                else if (right_score >= WINNING_SCORE) {
                    gameOver = true;
                    winnerText = "Right Player Wins!";
                }
            }

            if (gameOver) {
                
                SDL_Surface* bg_surface = nullptr;
                if (winnerText == "You Win!") {
                    bg_surface = IMG_Load("assets/win_background.png"); 
                }
                else if (winnerText == "Left Player Wins!" || winnerText == "Right Player Wins!") {
                    bg_surface = IMG_Load("assets/win_background.png");
                }
                else if (winnerText == "You Lose!") {
                    bg_surface = IMG_Load("assets/lose_background.png"); 
                }

                if (!bg_surface) {
                    std::cerr << "Failed to load background: " << IMG_GetError() << std::endl;
                }
                else {
                    SDL_Texture* bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
                    SDL_FreeSurface(bg_surface);

                    
                    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
                    SDL_DestroyTexture(bg_texture);
                }

                
                SDL_Color color = { 255, 0, 0, 255 }; 
                SDL_Surface* winner_surface = TTF_RenderText_Solid(font, winnerText.c_str(), color);
                SDL_Texture* winner_texture = SDL_CreateTextureFromSurface(renderer, winner_surface);
                SDL_Rect winner_rect = { SCREEN_WIDTH / 2 - winner_surface->w / 2, SCREEN_HEIGHT / 2, winner_surface->w, winner_surface->h };
                SDL_RenderCopy(renderer, winner_texture, NULL, &winner_rect);

                SDL_RenderPresent(renderer);

                SDL_FreeSurface(winner_surface);
                SDL_DestroyTexture(winner_texture);

                SDL_Delay(3000); 
                bool waitForEsc = true;
                while (waitForEsc) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                            waitForEsc = false;
                        }
                    }
                }
                running = false;
                gameOver = false; 
                winnerText = ""; 
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
            }
            
            SDL_RenderPresent(renderer);
            SDL_Delay(16); 
        }

        if (bot) {
            delete bot;
        }
    }

    SDL_DestroyTexture(music_note_texture);
    SDL_DestroyTexture(music_note_slash_texture);
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(paddle_hit_sound);
    Mix_FreeChunk(buttonClickSound);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
