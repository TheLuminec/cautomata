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

typedef struct automaton {
	Rule* ruleSet;
	uint16_t ruleCount;

	State* stateSet;
	uint16_t stateSize;
} Automaton;

bool isValidPoint(const int x, const int y) {

	return (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0);
}

const State* useRules(const int x, const int y, const Automaton* rs, const State*** data) {
	for (int i = 0; i < rs->ruleCount; i++) {
		if(data[x][y] == rs->ruleSet[i].from)
			if(rs->ruleSet[i].rule(x, y, data))
				return rs->ruleSet[i].to;
	}
	
	return data[x][y];
}

void applyRuleset(const Automaton* rs, State**** dataPtr) {
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


State*** randomFlash(const Automaton* rs) {
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
