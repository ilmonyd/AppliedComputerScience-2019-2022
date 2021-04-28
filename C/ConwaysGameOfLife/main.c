#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "functions.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("The program needs arguments to work.\nUse -h for help.\n");
		return -1;
	}
	int option;
	int rows, columns;
	double fill, seed = 1;
	int generations;
	int rflag = 0, cflag = 0, fflag = 0, gflag = 0, sflag = 0, hflag = 0;
	char* rows_pointer;
	char* columns_pointer;
	char* fill_pointer;
	char* gen_pointer;
	while ((option = getopt(argc, argv, "r:c:f:g:s:h")) != -1) {
		switch (option) {
			case 'h':
				help();
				hflag = 1;
				return 0;
			case 'r':
				rows = strtod(optarg, &rows_pointer);
				if ((rows_pointer - optarg) != strlen(optarg)) {
					printf("The number of rows is invalid, must be an integer! Use -h for help.\n");
					return -1;
				}
				rflag = 1;
				break;
			case 'c':
				columns = strtod(optarg, &columns_pointer);
				if ((columns_pointer - optarg) != strlen(optarg)) {
					printf("The number of columns is invalid, must be an integer! Use -h for help.\n");
					return -1;
				}
				cflag = 1;
				break;
			case 'f':
				fill = strtod(optarg, &fill_pointer);
				if ((fill_pointer - optarg) != strlen(optarg)) {
					printf("The fill rate is invalid! Use -h for help.\n");
					return -1;
				}
				fflag = 1;
				break;
			case 'g':
				generations = strtod(optarg, &gen_pointer);
				if ((gen_pointer - optarg) != strlen(optarg)) {
					printf("The number of generations is invalid, must be an integer! Use -h for help.\n");
					return -1;
				}
				gflag = 1;
				break;
			case 's':
				seed = atoi(optarg);
				sflag = 1;
				break;
		}
	}
	
	if (hflag == 0 && (rflag == 0 || cflag == 0 || fflag == 0 || gflag == 0)) {
		printf("You need to define both number of rows and columns as well as fill rate and generations count.\n");
		return -1;
	}
	if (rows <= 0) {
		printf("Number of rows must be greater than 0! You've entered: %d\n", rows);
		return -1;
	}
	if (columns <= 0) {
		printf("Number of columns must be greater than 0! You've entered: %d\n", columns);
		return -1;
	}
	if (fill <= 0 || fill >= 1) {
		printf("Fill factor can't be lower or equal to 0 nor can it be greater than or equal to 1. You've entered: %lf\n", fill);
		return -1;
	}
	printf("The size of map: %dx%d\n", rows, columns);
	if (rows < 15 || columns < 15) {
		printf("*WARNING*  the map size you selected is very small, the simulation might end very quickly!\n");
	}
	if (fill < 0.3 || fill > 0.7) {
		printf("*WARNING*  the fill rate you selected is too low or too high, the cells will die out very quickly of overpopulation or underpopulation!\n");
	}

	char* universe = init(rows, columns, fill, seed, sflag);
	printSimulation(universe, rows, columns);

	int i;
	for (i = 1; i <= generations || generations == 0; i++) {
		char* newUniverse = nextGen(universe, rows, columns);
		if (newUniverse == NULL) return -2;
		free(universe);
		universe = newUniverse;
		printSimulation(universe, rows, columns);
		printf("Generation %d\n", i);
		usleep(100 * 1000);
	}
}

