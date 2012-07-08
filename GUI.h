#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/image.h>
#include <gtkmm/entry.h>
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
	Gtk::VBox mainVBox;

	Gtk::HBox topBarHBox;
	Gtk::Button newGameButton;
	Gtk::Entry seedEntry;
	Gtk::Button endGameButton;


	Gtk::Frame tableFrame;
	Gtk::VBox tableVBox;
	Gtk::HBox tableClubHBox;
	Gtk::HBox tableDiamondHBox;
	Gtk::HBox tableHeartHBox;
	Gtk::HBox tableSpadeHBox;
	Gtk::Image* tableCards[52]; // Images for the Table

private:
	DeckGUI deck;
};







#endif