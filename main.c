#include "system.h"
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include "rules.h"
#include "display.h"

State*** pixels;
void init();
void click(const int, const int, int);

int main() {
	init();
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;

    while (running) {
        a = SDL_GetTicks();
        delta = a - b;

        if (delta > 1000 / FPS) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = 0;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    clicked = true;
                }
                else if (event.type == SDL_MOUSEBUTTONUP) {
                    clicked = false;
                }
                if (clicked) {
                    click(event.button.x, event.button.y, 10);
                }
            }

            b = a;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            applyRuleset(&sand, &pixels);

            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    State* s = pixels[i][j];
                    SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, s->a);

					//SDL_RenderDrawPoint(renderer, i, j);
                    SDL_Rect rect = {i*2, j*2, 2, 2};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }


            SDL_RenderPresent(renderer);
        }
    }

    cleanupSDL();
    for (int i = 0; i < WIDTH; i++) {
        free(pixels[i]);
    }
    free(pixels);

	return 0;
}

void init() {
    srand(time(NULL));

	initSDL();
    pixels = randomFlash(&sand);

    printf("Enter to start...");
	getchar();
}

void click(const int x, const int y, int s) {
    int i = x / SANDSIZE;
    int j = y / SANDSIZE;
    if (isValidPoint(i, j)) {
        if(pixels[i][j] == &sand.stateSet[0])
            pixels[i][j] = &sand.stateSet[1];
        else
			pixels[i][j] = &sand.stateSet[0];
    }

    for (int k = 0; k < s - 1; k++) {
        click(x + rand() % s - s / 2, y + rand() % s - s / 2, 0);
    }
}