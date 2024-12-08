#pragma once
#include "rules.h"

//Game of life implmentation

const State gameOfLifeState[] = {
	{0,0,0,255},
	{255,255,255,255}
};

int countNeighbors(int x, int y, const State*** flash) {
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			if (isValidPoint(x + i, y + j) && flash[x + i][y + j] == &gameOfLifeState[1])
				count++;
		}
	}
	return count;
}

//Rule 1: Any live cell with fewer than two live neighbors dies, as if by underpopulation.
bool r1(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash) < 2;
}

//Rule 2: Any live cell with two or three live neighbors lives on to the next generation.
//auto fullfilled

//Rule 3: Any live cell with more than three live neighbors dies, as if by overpopulation.
bool r2(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash) > 3;
}

//Rule 4: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
bool r3(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash) == 3;
}

const Rule gameOfLifeRules[] = {
	{r1, &gameOfLifeState[1], &gameOfLifeState[0]},
	{r2, &gameOfLifeState[1], &gameOfLifeState[0]},
	{r3, &gameOfLifeState[0], &gameOfLifeState[1]}
};

const Automaton gameOfLife = {
	&gameOfLifeRules,
	3,
	&gameOfLifeState,
	2
};