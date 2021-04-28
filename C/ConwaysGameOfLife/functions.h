char* init(int rows, int columns, double fill, int seed, int sflag);
void help();
double fillRand(double min, double max);
void printSimulation(char* universe, int rows, int columns);
int countNeighbors(char* universe, int rows, int columns, int x, int y); 
char* nextGen(char* prevUniverse, int rows, int columns);
