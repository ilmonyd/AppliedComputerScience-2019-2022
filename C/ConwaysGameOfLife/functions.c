#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void help() {
	printf("\nThis is a simple program simulating cellular automata called 'Conway's game of life'.\nIt was created by Cambridge mathematician John H. Conway.\nIt consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply.\n\nArguments:\n   -r   *   rows\n   -c   *   columns (if the selected map is too small, the simulation might end quckly)\n   -f   *   fill factor (a number from 0 to 1 exclusive, if the rate you selected is too low or too high, the cells might die out very quickly of overpopulation or underpopulation)\n   -g   *   generations count (0 for infinite steps, stop with Ctrl+C)\n   -s       seed for universe fill\n   -h       display this message\n(* - mandatory argument)\n\nSample usage: ./conway -f 0.5 -r 50 -c 50 -g 0\nA 50x50 map filled with approximately 50%c of cells will be generated and will be simulated infinitely untill stopped via Ctrl+C\n\nThis app was created by Oleg Semenov.\n\n", 37);
}

char* init(int rows, int columns, double fill, int seed, int sflag){
	int i, j;
	fill = 1 - fill;
	
	char* universe = (char*)calloc(rows*columns, sizeof(char));

	if (universe == NULL) return NULL;
	
	srand((double)time(NULL));
	if (sflag == 1) srand(seed);

	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			if (fillRand(0.0, 1.0) <= fill) *(universe + i*columns + j) = '#';
		}
	}
	return universe;
}

void printSimulation(char* universe, int rows, int columns) {
	int i, j;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for (i = 0; i < 2*(columns + 1); i++) {
		printf("#");
	}
	printf("\n");
	for (i = 0; i < rows; i++) {
		printf("#");
		for (j = 0; j < columns; j++) {
			printf ((*(universe + i*columns + j) == '#') ? "\033[07m  \033[m" : "  ");
		}
		printf("#\n");
	}
	for (i = 0; i < 2*(columns + 1); i++) {
		printf("#");
	}
	printf("\n");
}

double fillRand(double min, double max) {
	return (double)rand()/(double)RAND_MAX * (max - min) + min;
}

int countNeighbors(char* universe, int rows, int columns, int x, int y) {
	int i, j;
	int count = 0;
	int coord = y*columns+x;

	for(i = -1; i <= 1; i++) {
		for(j = -1; j <= 1; j++) {
			char c = *(universe + coord + i*columns + j);
			if (c == '#') count++;
		}
	}
	return count;
}

char* nextGen(char* prevUniverse, int rows, int columns) {
	/*
	Any live cell with fewer than two live neighbours dies (referred to as underpopulation or exposure).
	Any live cell with more than three live neighbours dies (referred to as overpopulation or overcrowding).
	Any live cell with two or three live neighbours lives, unchanged, to the next generation.
	Any dead cell with exactly three live neighbours will come to life.
	*/
	char* newUniverse = calloc(rows*columns, sizeof(char));
	if (newUniverse == NULL) return NULL;

	int x, y;
	for (y = 1; y < rows - 1; y++) {
		for (x = 1; x < columns - 1 ; x++) {
			int alive = countNeighbors(prevUniverse, rows, columns, x, y);
			char c = *(prevUniverse+y*columns+x);
			if (c == '#') alive--;

			if (alive < 2) *(newUniverse+y*columns+x) = ' ';
			else if ((alive == 2 || alive == 3) && c == '#') *(newUniverse+y*columns+x) = '#';
			else if (alive > 3 && c == '#') *(newUniverse+y*columns+x) = ' ';
			else if (alive == 3 && c != '#') *(newUniverse+y*columns+x) = '#';
		}
	}
	return newUniverse;
}
