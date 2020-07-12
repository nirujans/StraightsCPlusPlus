/*
 * Loads a series of pixmaps used for displaying the cards, as well as a card back used as a place marker in the
 * display when we don't have a card yet to display. Use pixel buffers to share images since widgets cannot be
 * shared.
 *
 */

#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>

using std::vector;

#include "model.h"

class DeckGUI {
public:
	DeckGUI();									//constructor
	virtual ~DeckGUI();							//destructor
	Glib::RefPtr<Gdk::Pixbuf> image(int); // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> null(); // Returns the image to use for the placeholder.
	Glib::RefPtr<Gdk::Pixbuf> valid();
	Glib::RefPtr<Gdk::Pixbuf> empty();
private:
	vector<Glib::RefPtr<Gdk::Pixbuf> > deck; // Contains the pixel buffer images.
};
// DeckGUI

#endif
