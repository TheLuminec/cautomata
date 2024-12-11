#include "system.h"
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include "rules.h"
#include "display.h"
#include "sand.h"
#include "gol.h"

//selected automata
#define ATM gameOfLife

//pixels that hold automata data
State*** pixels;
bool simulate;

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

        if (delta >= 1000.0 / FPS) {
            printf("\rFPS: %.1lf", 1000/delta);
            b = a;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = 0;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    clicked = true;
                }
                else if (event.type == SDL_MOUSEBUTTONUP) {
                    clicked = false;
                }
                else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case PAUSE:
                            simulate = !simulate;
                            break;
                        default:
                            break;
                    }
                }

                if (clicked) {
                    click(event.button.x, event.button.y, BRUSHSIZE);
                }
            }

            if(simulate)
                applyRuleset(&ATM, &pixels);

            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
					State* s = pixels[i][j];
                    if (s != &ATM.stateSet[0])
                        schedulePixelDraw(i, j, s);
                }
            }

            draw(ATM);
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
    simulate = true;
}

void click(const int x, const int y, int s) {
    int i = x / PIXELSIZE_X;
    int j = y / PIXELSIZE_Y;

    if (isValidPoint(i, j)) {
        if(pixels[i][j] == &ATM.stateSet[0])
            pixels[i][j] = &ATM.stateSet[1];
        else
			pixels[i][j] = &ATM.stateSet[0];
    }

    for (int k = 0; k < s - 1; k++) {
        click(x + ((rand() % s) - (s / 2)) * PIXELSIZE_X, y + ((rand() % s) - (s / 2)) * PIXELSIZE_Y, 0);
    }
}