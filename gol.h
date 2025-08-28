#pragma once
#include "rules.h"

//Game of life implmentation

const State gameOfLifeState[] = {
	{20,20,20,255},		//Dead
	{255,255,255,255}	//Alive
};

//Rule 1: Any live cell with fewer than two live neighbors dies, as if by underpopulation.
bool r1(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash, &gameOfLifeState[1]) < 2;
}

//Rule 2: Any live cell with two or three live neighbors lives on to the next generation.
//auto fullfilled

//Rule 3: Any live cell with more than three live neighbors dies, as if by overpopulation.
bool r2(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash, &gameOfLifeState[1]) > 3;
}

//Rule 4: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
bool r3(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash, &gameOfLifeState[1]) == 3;
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