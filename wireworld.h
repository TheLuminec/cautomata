#pragma once
#include "rules.h"

//Wireworld implementation

const State wireworldState[] = {
	{20,20,20,255},		//Empty
	{20,20,255,255},	//Electron head
	{255,20,20,255},	//Electron tail
	{255,255,20,255}	//Conductor
};

//0 to 0 done, empty

//Rule 1: Any electron head becomes an electron tail.
bool r1(int x, int y, const State*** flash) {
	return true;
}

//Rule 2: Any electron tail becomes a conductor.
bool r2(int x, int y, const State*** flash) {
	return true;
}

//Rule 3: Any conductor with one or two neighboring electron heads becomes an electron head.
bool r3(int x, int y, const State*** flash) {
	int n = countNeighbors(x, y, flash, &wireworldState[1]);
	return n == 1 || n == 2;
}

const Rule wireworldRules[] = {
	{r1, &wireworldState[1], &wireworldState[2]},
	{r2, &wireworldState[2], &wireworldState[3]},
	{r3, &wireworldState[3], &wireworldState[1]}
};

const Automaton wireworld = {
	&wireworldRules,
	3,
	&wireworldState,
	4
};