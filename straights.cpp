#include "Game.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc > 1) {
		srand48(atoi(argv[1]));
	}
	Game g;
	g.start();
}
