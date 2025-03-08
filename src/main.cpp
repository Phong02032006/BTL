#include <SDL.h>
#include "Paddle.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* window = SDL_CreateWindow("Paddle Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);

    // Tạo paddle ở giữa bên trái màn hình
    Paddle left_paddle(20, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
	Paddle right_paddle(SCREEN_WIDTH - 20 - Paddle::PADDLE_WIDTH, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, SCREEN_HEIGHT);
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Xử lý input
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W]) left_paddle.move(true);
        if (state[SDL_SCANCODE_S]) left_paddle.move(false);
		if (state[SDL_SCANCODE_UP]) right_paddle.move(true);
		if (state[SDL_SCANCODE_DOWN]) right_paddle.move(false);


        // Clear và vẽ
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        left_paddle.render(renderer);
		right_paddle.render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}