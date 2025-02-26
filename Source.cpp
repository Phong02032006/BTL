#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture = IMG_LoadTexture(renderer, "image.png");
    Mix_Music* music = Mix_LoadMUS("test.wav");
    TTF_Font* font = TTF_OpenFont("test.ttf", 24);
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, SDL2!", color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    Mix_PlayMusic(music, -1);
    SDL_RenderCopy(renderer, text_texture, NULL, &(SDL_Rect){100, 100, 200, 50});

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_DestroyTexture(texture);
    Mix_FreeMusic(music);
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text_texture);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
