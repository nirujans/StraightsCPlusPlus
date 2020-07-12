/*Straights Game - C++ using gtkmm

 Developers: 	Nirujan Suresh and Anandh Sridharan
 Date:     		July, 13, 2012
 Course: 		CS 247 @ University of Waterloo

 2B Software Engineering
 All Rights Reserved

 */

#include <gtkmm/main.h>
#include "model.h"
#include "controller.h"
#include "view.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	Gtk::Main kit(argc, argv); // Initialize gtkmm with the command line arguments, as appropriate.
	string hardmode = "";
	if (argv[1] != NULL) { //if the user wants hardmode
		hardmode = argv[1];
	}

	Model model;

	// Create model
	Controller controller(&model);  	// Create controller
	View view(&controller, &model); // Create the view -- is passed handle to controller and model

	if (hardmode == "-h") { //if its hardmode, set the flag in model to hard
		model.setHard();
	}
	Gtk::Main::run(view);       // Show the window and return when it is closed.

	return 0;						//end program
} // main
