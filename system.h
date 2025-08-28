#pragma once
#ifndef SYSTEMSETTINGS
#define SYSTEMSETTINGS
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define WIDTH 160.0
#define HEIGHT 160.0
#define PIXELSIZE_X (SCREEN_WIDTH/WIDTH)
#define PIXELSIZE_Y (SCREEN_HEIGHT/HEIGHT)
#define PIXELED (PIXELSIZE_X == 1 && PIXELSIZE_Y == 1)
#define FPS 120
#define BRUSHSIZE 1

//Keycodes
#define PAUSE SDLK_SPACE

#endif