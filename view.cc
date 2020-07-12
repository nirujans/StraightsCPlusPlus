#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) :
		model_(m), controller_(c), panels(false, 5), butBox(true, 0), playerBox(
				true, 5), start_button("Start Game"), end_button(
				"End Current Game"), clubBox(true, 5), heartBox(true, 5), diamondBox(
				true, 5), spadeBox(true, 5), tableBox(true, 3), yourHand(
				"Your hand:"), handbox(true, 5), validBox(false, 5) {

	// Sets some properties of the window.
	set_title("Straights Card Game");
	set_border_width(10);

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.null(); //image for back of card
	const Glib::RefPtr<Gdk::Pixbuf> validCardPixbuf = deck.valid(); //image for the light if its a valid card
	const Glib::RefPtr<Gdk::Pixbuf> notvalidCardPixbuf = deck.empty(); //empty png

	// Add panels to the window
	add(panels);

	// Add button box and card image to the panels
	panels.add(butBox);

	butBox.add(start_button); //add start button
	seed.set_text("0"); //set the default seed
	butBox.add(seed); //add seed text field
	butBox.add(end_button); //add end button

	frame.set_label("Cards on the table:"); //frame title
	frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT); //add shadow type
	//add the "table" to the view
	panels.add(frame);
	tableBox.add(clubBox);
	tableBox.add(diamondBox);
	tableBox.add(heartBox);
	tableBox.add(spadeBox);
	frame.add(tableBox);

	//initialize the table (
	for (int i = 0; i < 52; i++) {
		cards.push_back(new Gtk::Image(nullCardPixbuf)); //set it to null
		if (i < 13)
			clubBox.add(*cards[i]); //init clubs area
		if ((i >= 13) && (i < 26))
			diamondBox.add(*cards[i]); //diammonds
		if ((i >= 26) && (i < 39))
			heartBox.add(*cards[i]); //hearts
		if ((i >= 39) && (i < 52))
			spadeBox.add(*cards[i]); //spades
	}

	//init player frames that contains ragequit, score and discards
	playerFrame.push_back(new Gtk::Frame("Player 1"));
	playerFrame.push_back(new Gtk::Frame("Player 2"));
	playerFrame.push_back(new Gtk::Frame("Player 3"));
	playerFrame.push_back(new Gtk::Frame("Player 4"));

	for (int i = 0; i < 4; i++) {
		playerBox.add(*playerFrame[i]); //add the frames to the layout box
	}

	panels.add(playerBox);
	for (int i = 0; i < 4; i++) { //initializing all valudes inside the player frame
		playerBut.push_back(new Gtk::Button("Human"));
		points.push_back(new Gtk::Label("0 points"));
		discards.push_back(new Gtk::Label("0 discards"));
		eachPlayer.push_back(new Gtk::VBox());
		(*eachPlayer[i]).add(*playerBut[i]);
		(*eachPlayer[i]).add(*points[i]);
		(*eachPlayer[i]).add(*discards[i]);
		(*playerFrame[i]).add(*eachPlayer[i]);
	}

	yourHand.set_shadow_type(Gtk::SHADOW_ETCHED_OUT); //frame for the hand
	panels.add(yourHand);
	//frame yourHand will have a Hbox which consists of 13 buttons)	
	yourHand.set_label("Your Hand:"); //title
	yourHand.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
	yourHand.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

	yourHand.add(validVBox); //vertical box stacks hand and valid card light
	validVBox.add(handbox);
	validVBox.add(validBox);

	for (int j = 0; j < 13; j++) {
		yourHandBut.push_back(new Gtk::Button());
		hand.push_back(new Gtk::Image(nullCardPixbuf)); //initi hand to null
		yourHandBut[j]->set_image(*hand[j]);
	}

	for (int j = 0; j < 13; j++) { // Add the button to the box.
		handbox.add(*yourHandBut[j]); //add to the layout
	}

	for (int i = 0; i < 13; i++) {
		valid.push_back(new Gtk::Image(notvalidCardPixbuf)); //init valid light to off
		valid[i]->set(notvalidCardPixbuf);
		validBox.add(*valid[i]); //add to layout
	}

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect(
			sigc::mem_fun(*this, &View::startButtonClicked));
	end_button.signal_clicked().connect(
			sigc::mem_fun(*this, &View::endButtonClicked));

	for (int j = 0; j < 13; j++) {
		yourHandBut[j]->set_sensitive(false); //set all hand buttons to false so they dont click it
	}

	end_button.set_sensitive(false); //end cant be clicked if game hasnt been started

	for (int i = 0; i < 4; i++) { //bind the ragequits for easy accessing
		(*playerBut[i]).signal_clicked().connect(
				sigc::bind<int>(
						sigc::mem_fun(*this, &View::playerButtonClicked), i));
	}

	for (int i = 0; i < 13; i++) { //bind the hand for easy accessing
		(*yourHandBut[i]).signal_clicked().connect(
				sigc::bind<int>(sigc::mem_fun(*this, &View::youHandButClicked),
						i));
	}
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {
} //no dynamic memory was allocated

void View::update(string msg) { //if the player order has been determined, make a pop up saying so

	GtkWidget *dialog;
	GtkWidget *window;

	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
			msg.c_str(), "Player Order Determined");
	gtk_window_set_title(GTK_WINDOW(dialog), "Player Order Determined");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

}

void View::endGame(string msg) { //if it is the end of game, popup the winner

	GtkWidget *dialog;
	GtkWidget *window;

	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
			msg.c_str(), "Winner");
	gtk_window_set_title(GTK_WINDOW(dialog), "Winner");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	endButtonClicked(); //should act like if the endButton is clicked
}

void View::endRound(string msg, vector<int> d, vector<int> s) { //if end of round

	stringstream ss_dis;
	string discard_msg;

	for (int i = 0; i < d.size(); i++) { //update the discards
		ss_dis << d[i];
		discard_msg = ss_dis.str() + " discards";
		discards[i]->set_label(discard_msg);
		ss_dis.str("");
	}

	for (int i = 0; i < 13; i++) { //turn of all valid lights
		valid[i]->set(deck.empty());
	}

	stringstream ss_score;
	string score_msg;

	for (int i = 0; i < s.size(); i++) { //update the score
		ss_score << s[i];
		score_msg = ss_score.str() + " points";
		points[i]->set_label(score_msg);
		ss_score.str("");
	}

	GtkWidget *dialog;
	GtkWidget *window;
	//popup saying end of round scores
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
			msg.c_str(), "End of Round Score");
	gtk_window_set_title(GTK_WINDOW(dialog), "End of Round Score");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	for (int i = 0; i < 4; i++) { //discards are back to zero
		discards[i]->set_label("0 discards");
	}

}

void View::startButtonClicked() { //if start button is scored
	string player_types[4] = { playerBut[0]->get_label(),
			playerBut[1]->get_label(), playerBut[2]->get_label(),
			playerBut[3]->get_label() }; //get their types
	int s = atoi(seed.get_text().c_str()); //get the seed
	vector<bool> rage = controller_->startButtonClicked(player_types, s); //call the controller passing seed and player types

	//ragequit button enable to human and disabled to computer
	for (int i = 0; i < 4; i++) {
		playerBut[i]->set_sensitive(rage[i]);
		playerBut[i]->set_label("Rage Quit");
	}
	//hand is set to true for clicking now
	for (int j = 0; j < 13; j++) {
		yourHandBut[j]->set_sensitive(true);
	}

	start_button.set_sensitive(false); //cant start the game again
	end_button.set_sensitive(true); //can end the game
	controller_->reSeedDeck(); //creates a brand new deck
	controller_->setPlayerHand(); //call the controller to set the hand
	controller_->gamePlay();	//start the game

}
void View::playerButtonClicked(int playerNum) { //if a ragequit
	string change = controller_->playerButtonClicked(
			(*playerBut[playerNum]).get_label());
	if (((*playerBut[playerNum]).get_label() == "Rage Quit")) { //if they ragequit, tell the controller
		(*playerBut[playerNum]).set_sensitive(false);
		controller_->rageQuit();
		controller_->gamePlay();
	} else if ((change == "Computer") || (change == "Human")) { //in the beginning before the game
		(*playerBut[playerNum]).set_label(change);
	}

}

void View::youHandButClicked(int cardButton) { //if a card is selected in the hand
	int num = atoi(yourHandBut[cardButton]->get_name().c_str()); //finds the index

	if (controller_->validCardPlay(num, cardButton)) { //checks if its a valid card
		controller_->addNextPlayer();
		controller_->gamePlay();
	}

}

void View::endButtonClicked() { //if the game is over
	//clear table, clear hand, clear players, clear any vectors used in game.cc (in model.cc setPlayerTypes, playerButton)
	controller_->clearGame(); //clear up
	for (int i = 0; i < 4; i++) { //reinit everyone back to humans
		playerBut[i]->set_label("Human");
		playerBut[i]->set_sensitive(true);
	}
	start_button.set_sensitive(true); //can start a game
	end_button.set_sensitive(false); //cant end twice

	for (int i = 0; i < 13; i++) { //init hand to null
		hand[i]->set(deck.null());
		yourHandBut[i]->set_image(*hand[i]); //null hand imgs
		yourHandBut[i]->set_sensitive(false); //hand cant be clicked
		valid[i]->set(deck.empty()); //all lights off
	}

	for (int i = 0; i < 52; i++) { //init cards on table to null
		cards[i]->set(deck.null());
	}

	for (int i = 0; i < 4; i++) {
		points[i]->set_label("0 points"); //points to zero
		discards[i]->set_label("0 discards"); //discards to zero
	}

}

void View::updateInterface(vector<int> d, vector<int> h, vector<int> t,
		vector<int> validIndex) {
	stringstream ss_dis;
	string discard_msg;

	for (int i = 0; i < 13; i++) { //all lights off
		valid[i]->set(deck.empty());
	}

	for (int i = 0; i < validIndex.size(); i++) { //if a card is valid, shine a light underneath it
		valid[validIndex[i]]->set(deck.valid());
	}

	for (int i = 0; i < d.size(); i++) { //update the discards if the previous players discarded a card
		ss_dis << d[i];
		discard_msg = ss_dis.str() + " discards";
		discards[i]->set_label(discard_msg);
		ss_dis.str("");
	}

	for (int i = 0; i < h.size(); i++) { //update the hand
		hand[i]->set(deck.image(h[i]));
		yourHandBut[i]->set_image(*hand[i]);
		stringstream ss; //create a stringstream
		ss << h[i]; //add number to the stream
		yourHandBut[i]->set_name(ss.str());
		hand[i]->set(deck.image(h[i]));
		yourHandBut[i]->set_image(*hand[i]);
		yourHandBut[i]->set_sensitive(true);
	}

	for (int i = 0; i < t.size(); i++) { //update the table
		cards[t[i]]->set(deck.image(t[i]));
	}

	for (int i = 12; (i + 1) > h.size(); i--) { //if empty cards null them and make them unselectable
		hand[i]->set(deck.null());
		yourHandBut[i]->set_image(*hand[i]);
		yourHandBut[i]->set_sensitive(false);
	}

	for (int i = 0; i < 4; i++) { //set all ragequits to false
		(*playerBut[i]).set_sensitive(false);
	}

	(*playerBut[controller_->getCurrentPlayerNum()]).set_sensitive(true); //enable the current players ragequit to true

}

void View::notifyTableClear() { //clear the table
	for (int i = 0; i < 52; i++) {
		cards[i]->set(deck.null());
	}
}
