#include "Game.h"
#include "GUI.h"
#include <stdlib.h>
#include <gtkmm/main.h>

using namespace std;

int main(int argc, char *argv[]) {

	Gtk::Main kit (argc, argv);
	StraightsWindow window;
	Gtk::Main::run(window);

	return 0;
}