#include <stdio.h>


#include "support.h"
#include <SDL.h>


int is_running = 0;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *screen;

void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Strike",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Couldn't set window mode %d x %d: %s\n", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
}

void init_game() {
    is_running = 1;
}

void free_game() {
}

void update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = 0;
                break;
            case SDL_KEYDOWN: // key press
                if (event.key.keysym.sym == 'q')
                    is_running = 0;
                break;
            case SDL_MOUSEMOTION:
                // mouse_x = event.motion.x;
                // mouse_y = event.motion.y;
                // mouse_xvel = event.motion.xrel;
                // mouse_yvel = event.motion.yrel;
                break;
        }
    }

    // update rest of game.
}

void draw() {
    // clears renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw the game.



    // renders renderer
    SDL_RenderPresent(renderer);
}

int main(UNUSED int argc, UNUSED char *argv[]) {
    printf("type q or click the red x button to quit.\n");

    // init sdl
    init_sdl();

    // init game
    init_game();

    // game loop
    while(is_running) {
        update();

        // TODO: make draw() run on its own thread.
        draw();
    }

    // frees game materials
    free_game();

    return 0;
}
