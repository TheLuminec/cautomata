#pragma once
#include "system.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct state {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

} State;

typedef struct rule {
	bool (*rule)(int, int, const State***);
	State* from;
	State* to;

} Rule;

typedef struct ruleset {
	Rule* ruleSet;
	uint16_t ruleCount;

	State* stateSet;
	uint16_t stateSize;
} Ruleset;

bool isValidPoint(const int x, const int y) {

	return (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0);
}

const State* useRules(const int x, const int y, const Ruleset* rs, const State*** data) {
	for (int i = 0; i < rs->ruleCount; i++) {
		if(data[x][y] == rs->ruleSet[i].from)
			if(rs->ruleSet[i].rule(x, y, data))
				return rs->ruleSet[i].to;
	}
	
	return data[x][y];
}

void applyRuleset(const Ruleset* rs, State**** dataPtr) {
	// Allocate flash
	State*** flash = malloc(WIDTH * sizeof(State**));
	for (int i = 0; i < WIDTH; i++) {
		flash[i] = malloc(HEIGHT * sizeof(State*));
	}

	// Apply rules
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			flash[i][j] = useRules(i, j, rs, *dataPtr);
		}
	}

	// Free old data
	for (int i = 0; i < WIDTH; i++) {
		free((*dataPtr)[i]);
	}
	free(*dataPtr);

	// Update the caller's pointer
	*dataPtr = flash;
}


State*** randomFlash(const Ruleset* rs) {
	State*** flash = malloc(WIDTH * sizeof(State**));
	for (int i = 0; i < WIDTH; i++) {
		flash[i] = malloc(HEIGHT * sizeof(State*));
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			int r = rand() % 10;
			if (r < 2)
				flash[i][j] = &(rs->stateSet[1]);
			else
				flash[i][j] = &(rs->stateSet[0]);
		}
	}

	return flash;
}


//Sand Implementation
const State sandState[] = {
	{0,0,0,255},
	{255,255,255,255}
};

//0 to 0 done, no sand
// 1 to 1 done, sand on bottom
//normal falling, sandy
bool sr1(int x, int y, const State*** flash) {
	return isValidPoint(x, y + 1) && flash[x][y + 1] == &sandState[0];
}
//normal falling, empty
bool sr2(int x, int y, const State*** flash) {
	return isValidPoint(x, y - 1) && flash[x][y-1] == &sandState[1];
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

const Ruleset sand = { 
	&sandRules,
	2,
	&sandState,
	3
};

