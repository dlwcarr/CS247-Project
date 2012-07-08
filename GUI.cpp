#include <iostream>
#include "GUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

using namespace std;

// ************* GUICARD ************** //
const char * image_names[] = {   
	// Set up CARDS
	"img/0_0.png", "img/1_0.png", "img/2_0.png", "img/3_0.png",
	"img/0_1.png", "img/1_1.png", "img/2_1.png", "img/3_1.png",
	"img/0_2.png", "img/1_2.png", "img/2_2.png", "img/3_2.png",
	"img/0_3.png", "img/1_3.png", "img/2_3.png", "img/3_3.png",
	"img/0_4.png", "img/1_4.png", "img/2_4.png", "img/3_4.png",
	"img/0_5.png", "img/1_5.png", "img/2_5.png", "img/3_5.png",
	"img/0_6.png", "img/1_6.png", "img/2_6.png", "img/3_6.png",
	"img/0_7.png", "img/1_7.png", "img/2_7.png", "img/3_7.png",
	"img/0_8.png", "img/1_8.png", "img/2_8.png", "img/3_8.png",
	"img/0_9.png", "img/1_9.png", "img/2_9.png", "img/3_9.png",
	"img/0_j.png", "img/1_j.png", "img/2_j.png", "img/3_j.png",
	"img/0_k.png", "img/1_k.png", "img/2_k.png", "img/3_k.png",
	"img/0_q.png", "img/1_q.png", "img/2_q.png", "img/3_q.png",
	"img/nothing.png",
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf


DeckGUI::DeckGUI()  {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck), &createPixbuf );
} // DeckGUI::DeckGUI

DeckGUI::~DeckGUI() {
} // DeckGUI::~DeckGUI

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage( Card c ) {
	int index = ((int) c.getRank())*4 + ((int) c.getSuit() );
	return deck[ index ];
} // DeckGUI::getCardImage 

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	int size = deck.size();
	return deck[ size-1 ];
} // DeckGUI::getNullCardImage





// ************** WINDOW SHTUFF **************** //


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

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.
StraightsWindow::StraightsWindow(){
		
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();	
	// Sets the border width of the window.
	set_border_width( 10 );
		
	// Set the look of the frame.
	tableFrame.set_label( "Cards on the table:" );
	tableFrame.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
	tableFrame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
	// Add the frame to the window. Windows can only hold one widget, same for frames.
	add( tableFrame );
	
	// Add the horizontal box for laying out the images to the frame.
	tableFrame.add(tableVbox);
	
	// Initialize 4 empty cards and place them in the box.
	for (int i = 0; i < 4; i++ ) {
		card[i] = new Gtk::Image( nullCardPixbuf );
		hbox.add( *card[i] );
	} // for
	
	// Initialize the 5th card and place the image into the button.
	card[4] = new Gtk::Image( cardPixbuf );	
	button.set_image( *card[4] );	
			
	// Add the button to the box.
	hbox.add( button );
	
	// The final step is to display this newly created widget.
	show_all();
} // OtherWorld::OtherWorld

OtherWorld::~OtherWorld() {
	for (int i = 0; i < 5; i++ ) delete card[i];
} // OtherWorld::~OtherWorld()
