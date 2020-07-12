#ifndef __VIEW_H
#define __VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "observer.h"

//GLOBAL VARIABLES FOR CONTROLLER AND MODEL
class Controller;
class Model;

class View: public Gtk::Window, public Observer {
public:
	View(Controller*, Model*); //Constructor
	virtual ~View(); //Destructor for View
	//METHODS CALLED BY THE OBSERVER
	virtual void update(std::string msg);// Observer Pattern: concrete update() method
	virtual void endRound(std::string msg, std::vector<int>, std::vector<int>);	// Observer Pattern: concrete endRound() method
	virtual void updateInterface(std::vector<int>, std::vector<int>,
			std::vector<int>, std::vector<int>); // Observer Pattern: concrete updateInterface() method
	virtual void notifyTableClear(); // Observer Pattern: concrete notifyTable() method
	virtual void endGame(std::string); // Observer Pattern: concrete endGame() method
private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;

	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	// Member widgets:
	Gtk::VBox panels;      // Main window divided into two horizontal panels
	Gtk::HBox butBox;      // Horizontal boxes for stacking buttons vertically

	Gtk::Button start_button; //button to start game
	Gtk::Button end_button; //button to end game
	Gtk::Entry seed; //text box to enter seed value
	Gtk::Frame frame; //frame that contains the top part of the view

	std::vector<Gtk::Frame*> playerFrame; //Frame that contains the Player number, score and discards
	std::vector<Gtk::Button*> playerBut; //ragequit buttons
	std::vector<Gtk::VBox*> eachPlayer; //vertical box for stacking
	std::vector<Gtk::Label*> points; //labels that update when points update
	std::vector<Gtk::Label*> discards; //labels that update when discards update
	Gtk::HBox playerBox; //horizontal box for lay  out purposes

	Gtk::VBox tableBox; //lay out purposes
	std::vector<Gtk::Image*> cards;          // Images to display.
	std::vector<Gtk::Image*> valid;	//"like a light", shines if a card is valid
	Gtk::HBox clubBox; //box containing clubs for table
	Gtk::HBox heartBox; //hearts
	Gtk::HBox diamondBox; //diamonds
	Gtk::HBox spadeBox; //spade
	Gtk::HBox validBox; //box for hand layout
	Gtk::VBox validVBox; //stacks hand and valid light

	Gtk::Frame yourHand; //frame for hand
	std::vector<Gtk::Button*> yourHandBut; //individual buttons for hands
	std::vector<Gtk::Image*> hand; //card images for hands
	Gtk::HBox handbox; //lay out purposes

	// Signal handlers:
	void startButtonClicked(); //if start button is clicked
	void endButtonClicked(); //if end button is clicked
	void playerButtonClicked(int); //if ragequit is clicked
	void youHandButClicked(int); //if  a card is selected

};
// View

#endif
