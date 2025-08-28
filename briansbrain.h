#pragma once
#include "rules.h"

const State briansBrainState[] = {
	{20,20,20,255},		//Off
	{255,255,255,255},	//On
	{20,20,255,255}		//Dying
};

//Rule 1: Any cell that is "off" and has exactly two neighbors that are "on" becomes "on".
bool r1(int x, int y, const State*** flash) {
	return countNeighbors(x, y, flash, &briansBrainState[1]) == 2;
}

//Rule 2: Any cell that is "on" becomes "dying".
bool r2(int x, int y, const State*** flash) {
	return true;
}

//Rule 3: Any cell that is "dying" becomes "off".
bool r3(int x, int y, const State*** flash) {
	return true;
}

const Rule briansBrainRules[] = {
	{r1, &briansBrainState[0], &briansBrainState[1]},
	{r2, &briansBrainState[1], &briansBrainState[2]},
	{r3, &briansBrainState[2], &briansBrainState[0]}
};

const Automaton briansBrain = {
	&briansBrainRules,
	3,
	&briansBrainState,
	3
};