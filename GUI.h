#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
using std::vector;


// *********** DECKGUI ************** //

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card c);   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();     // Returns the image to use for the placeholder.

private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
}; // DeckGUI



// ********** WINDOW SHTUFF ************ //

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