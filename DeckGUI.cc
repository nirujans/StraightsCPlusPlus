#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
#include<iostream>
#include<stdio.h>

using std::string;
using std::transform;
using namespace std;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {
		//cards from A to K of clubs
		"cards_png/0_0.png", "cards_png/0_1.png", "cards_png/0_2.png",
		"cards_png/0_3.png", "cards_png/0_4.png", "cards_png/0_5.png",
		"cards_png/0_6.png", "cards_png/0_7.png", "cards_png/0_8.png",
		"cards_png/0_9.png", "cards_png/0_j.png", "cards_png/0_q.png",
		"cards_png/0_k.png",
		//cards from A to K of diamonds
		"cards_png/1_0.png", "cards_png/1_1.png", "cards_png/1_2.png",
		"cards_png/1_3.png", "cards_png/1_4.png", "cards_png/1_5.png",
		"cards_png/1_6.png", "cards_png/1_7.png", "cards_png/1_8.png",
		"cards_png/1_9.png", "cards_png/1_j.png", "cards_png/1_q.png",
		"cards_png/1_k.png",
		//cards from A to K of hearts
		"cards_png/2_0.png", "cards_png/2_1.png", "cards_png/2_2.png",
		"cards_png/2_3.png", "cards_png/2_4.png", "cards_png/2_5.png",
		"cards_png/2_6.png", "cards_png/2_7.png", "cards_png/2_8.png",
		"cards_png/2_9.png", "cards_png/2_j.png", "cards_png/2_q.png",
		"cards_png/2_k.png",
		//cards from A to K of spades
		"cards_png/3_0.png", "cards_png/3_1.png", "cards_png/3_2.png",
		"cards_png/3_3.png", "cards_png/3_4.png", "cards_png/3_5.png",
		"cards_png/3_6.png", "cards_png/3_7.png", "cards_png/3_8.png",
		"cards_png/3_9.png", "cards_png/3_j.png", "cards_png/3_q.png",
		"cards_png/3_k.png", "cards_png/nothing.png", "cards_png/back_1.png",
		"cards_png/light.png" };

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file(name);
} // createPixbuf

DeckGUI::DeckGUI() {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform(&image_names[0], &image_names[G_N_ELEMENTS(image_names)],
			std::back_inserter(deck), &createPixbuf);
} // DeckGUI::DeckGUI

DeckGUI::~DeckGUI() {
} // DeckGUI::~DeckGUI

//Returns the image for the specified card (ex if index=0, it will return the Aces of clubs)
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::image(int index) {
	return deck[index];
} // DeckGUI::getCardImage

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::null() {
	int size = deck.size();
	return deck[size - 2];
} // DeckGUI::getNullCardImage

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::valid() {
	int size = deck.size();
	return deck[size - 1];
} // DeckGUI::getNullCardImage

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::empty() {
	int size = deck.size();
	return deck[size - 3];
} // DeckGUI::getNullCardImage

