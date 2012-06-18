#include <string>
#include <iostream>
#include <assert.h>
#include "Game.h"
#include "Command.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using namespace std;

const int CARD_COUNT = 52;

// Public methods

Game::Game() {

	// Initialize players
	for (int i = 1; i < 5; i++) {
		string input;
		cout << "Is player " << i << " a human(h) or computer(c)?" << endl << ">";
		cin >> input;
		cout << endl;
		assert(input.c_str() == 'h' || input.c_str() == 'H' || input.c_str() == 'c' || input.c_str() == 'C');
		
		if (input.c_str() == 'h' || input.c_str() == 'H')
			players_[i] = new HumanPlayer();
		else
			players_[i] = new ComputerPlayer();
	}
	
}

Game::~Game() {

}

void Game::start() {
	// Main game loop
	while (true) {
		this->buildDeck();
		this->shuffleDeck();


	}
}

// Private methods

void Game::shuffleDeck() {

	/* To ensure that the your cards are ordered the same way as
	the given program, use this shuffling algorithm.

	CARD_COUNT is the constant 52
	cards_ is an array of pointers to cards
	*/

	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = deck_[n];
		deck_[n] = deck_[k];
		deck_[k] = c;
	}
}

void Game::printDeck() {
	// Print deck_ out in 4 lines of 13 cards
	if (deck_->size() == 52) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				cout << deck_[j + (13*i)];
				if (j != 12) {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
}

void Game::buildDeck() {
	deck_->clear();
	Card *temp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			temp = new Card(i, j);
			deck_->push_back(temp);
		}
	}
}

// Non-member functions