#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/image.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
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

	// Top Bar
	Gtk::HBox topBarHBox;
	Gtk::Button newGameButton;
	Gtk::Entry seedEntry;
	Gtk::Button endGameButton;

	// Table
	Gtk::Frame tableFrame;
	Gtk::VBox tableVBox;
	Gtk::HBox tableClubHBox;
	Gtk::HBox tableDiamondHBox;
	Gtk::HBox tableHeartHBox;
	Gtk::HBox tableSpadeHBox;
	Gtk::Image* tableCards[52]; // Images for the Table

	// Players
	Gtk::HBox playersHBox;
	Gtk::Frame p1Frame;
	Gtk::Frame p2Frame;
	Gtk::Frame p3Frame;
	Gtk::Frame p4Frame;
	Gtk::VBox p1VBox;
	Gtk::VBox p2VBox;
	Gtk::VBox p3VBox;
	Gtk::VBox p4VBox;
	Gtk::Button p1ActionButton;
	Gtk::Button p2ActionButton;
	Gtk::Button p3ActionButton;
	Gtk::Button p4ActionButton;
	Gtk::Label p1PointsLbl;
	Gtk::Label p2PointsLbl;
	Gtk::Label p3PointsLbl;
	Gtk::Label p4PointsLbl;
	Gtk::Label p1DiscardsLbl;
	Gtk::Label p2DiscardsLbl;
	Gtk::Label p3DiscardsLbl;
	Gtk::Label p4DiscardsLbl;

	// Hand
	Gtk::Frame handFrame;
	Gtk::HBox handHBox;
	Gtk::Button* handCards[13]; // Buttons for the hand





private:
	DeckGUI deck;
};







#endif