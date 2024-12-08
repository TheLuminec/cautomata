#pragma once
#include "system.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
int running = 0;
bool clicked = false;


void initSDL() {
    running = 1;
	clicked = false;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        "Cautomata",                   // Title of the window
        SDL_WINDOWPOS_CENTERED,        // Initial x position
        SDL_WINDOWPOS_CENTERED,        // Initial y position
        SCREEN_WIDTH,                  // Width of the window
        SCREEN_HEIGHT,                 // Height of the window
        SDL_WINDOW_SHOWN               // Flags for window creation
    );

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}