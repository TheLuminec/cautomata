#include "system.h"
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include "rules.h"
#include "display.h"
#include "gol.h"

State*** pixels;
#define ATM gameOfLife
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
            //system("cls");
            printf("\rFPS: %.1lf", 1000/delta);


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

            applyRuleset(&ATM, &pixels);

            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    State* s = pixels[i][j];

                    SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, s->a);

                    if(SANDSIZE == 1)
                        SDL_RenderDrawPoint(renderer, i, j);
                    else {
                        SDL_Rect rect = {i* SANDSIZE, j* SANDSIZE, SANDSIZE, SANDSIZE };
                        SDL_RenderFillRect(renderer, &rect);
                    }
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
    pixels = randomFlash(&ATM);
}

void click(const int x, const int y, int s) {
    int i = x / SANDSIZE;
    int j = y / SANDSIZE;
    if (isValidPoint(i, j)) {
        if(pixels[i][j] == &ATM.stateSet[0])
            pixels[i][j] = &ATM.stateSet[1];
        else
			pixels[i][j] = &ATM.stateSet[0];
    }

    for (int k = 0; k < s - 1; k++) {
        click(x + rand() % s - s / 2, y + rand() % s - s / 2, 0);
    }
}