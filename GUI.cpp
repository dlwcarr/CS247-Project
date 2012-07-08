#include <iostream>
#include "GUI.h"

using namespace std;

StraightsWindow::StraightsWindow() : testButton("Test") {
	set_border_width(10);

	testButton.signal_clicked().connect(sigc::mem_fun(*this, &StraightsWindow::onButtonClicked));

	add(testButton);

	testButton.show();
}

StraightsWindow::~StraightsWindow() {}

void StraightsWindow::onButtonClicked() {
	cout << "Button clicked" << endl;
}