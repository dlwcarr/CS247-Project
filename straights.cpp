#include "Game.h"
#include <stdlib.h>

using namespace std;

void main(int argc, char *argv[]) {
    srand48(atoi(argv[1]));
	Game g();
	g.play();
}
