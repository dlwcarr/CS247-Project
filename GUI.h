#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class StraightsWindow : public Gtk::Window {
public:
	StraightsWindow();
	virtual ~StraightsWindow();

protected:
	virtual void onButtonClicked();
	Gtk::Button testButton;

private:
};

#endif