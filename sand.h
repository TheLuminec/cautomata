#pragma once
#include "rules.h"

/*
* Sand currently justs falls since I haven't implemented left/right
*/

//Sand States
const State sandState[] = {
	{0,0,0,255},		//No sand
	{255,255,255,255}	//Sand
};

//0 to 0 done, no sand
// 1 to 1 done, sand on bottom
//normal falling, sandy
bool sr1(int x, int y, const State*** flash) {
	return isValidPoint(x, y + 1) && flash[x][y + 1] == &sandState[0];
}
//normal falling, empty
bool sr2(int x, int y, const State*** flash) {
	return isValidPoint(x, y - 1) && flash[x][y - 1] == &sandState[1];
}
//sand fall left, sandy
bool sr3(int x, int y, const State*** flash) {
	return isValidPoint(x - 1, y + 1) && flash[x - 1][y + 1] == &sandState[0];
}
//sand fall left, empty
bool sr4(int x, int y, const State*** flash) {
	return isValidPoint(x + 1, y - 1) && flash[x + 1][y - 1] == &sandState[1];
}
//sand fall right, sandy
bool sr5(int x, int y, const State*** flash) {
	return isValidPoint(x + 1, y + 1) && flash[x + 1][y + 1] == &sandState[0];
}
//sand fall right, empty
bool sr6(int x, int y, const State*** flash) {
	return isValidPoint(x - 1, y - 1) && flash[x - 1][y - 1] == &sandState[1];
}

const Rule sandRules[] = {
	{sr1, &sandState[1], &sandState[0]},
	{sr2, &sandState[0], &sandState[1]},

	{sr3, &sandState[1], &sandState[0]},
	{sr4, &sandState[0], &sandState[1]},
	{sr5, &sandState[1], &sandState[0]},
	{sr6, &sandState[0], &sandState[1]}
};

// Sand Automaton
const Automaton sand = {
	&sandRules,
	2,
	&sandState,
	2
};
