#pragma once
#include "system.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "rules.h"

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

void schedulePixelDraw(int i, int j, const State* s) {
    SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, s->a);

    if (PIXELED) {
        SDL_RenderDrawPoint(renderer, i, j);
    }
    else {
        SDL_FRect rect = { i * PIXELSIZE_X, j * PIXELSIZE_Y, PIXELSIZE_X, PIXELSIZE_Y };
        SDL_RenderFillRectF(renderer, &rect);
    }
}

void draw(const Automaton ATM) {
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, ATM.stateSet[0].r, ATM.stateSet[0].g, ATM.stateSet[0].b, ATM.stateSet[0].a);
    SDL_RenderClear(renderer);
}