#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
#include <deque>
#include "Game.h"
#include "Command.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using namespace std;

const int CARD_COUNT = 52;

// Public methods

Game::Game() {

	// Initialize players
	players_ = new vector<Player*>(4);

	for (int i = 1; i < 5; i++) {
		string input;
		cout << "Is player " << i << " a human(h) or computer(c)?" << endl << ">";
		cin >> input;
		cout << endl;
		assert(input.c_str() == 'h' || input.c_str() == 'H' || input.c_str() == 'c' || input.c_str() == 'C');
		
		if (input.c_str() == 'h' || input.c_str() == 'H')
			players_[i-1] = new HumanPlayer();
		else
			players_[i-1] = new ComputerPlayer();
	}

	// Initialize Table
	table_ = new Table;
	table_->diamonds = new deque<Card*>;
	table_->clubs = new deque<Card*>;
	table_->hearts = new deque<Card*>;
	table_->spades = new deque<Card*>;

	deck_ = new vector<Card*>;
	
}

Game::~Game() {

}

void Game::start() {
	// Main game loop
	while (true) {
		this->buildDeck();
		this->shuffleDeck();

		// Distribute cards
		int startingPlayer = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				if (deck_[j + (13*i)]->getSuit() == SPADE && deck_[j + (13*i)]->getRank() == SEVEN)
					startingPlayer = j;
				players_[i]->insertHand(deck_[j + (13*i)]);
			}
		}

		// Take turns
		// First player first turn
		bool firstTurn = true;
		while(true) {
			plays = new vector<Card*>;
			plays.push_back(Card(3, 6));
			Command cmd = players[startingPlayer]->getCommand(plays);
			if (cmd.type == QUIT ) {
				return;
			}
			else if (cmd.type == RAGEQUIT) {
				//do shit nigguh
			}
			else if (cmd.type == DECK) {
				//do shit nigguh
			}
			players[startingPlayer]->play(cmd);
		}
		
		//Rest of the turns
		while(true) {
			for( int i = 0; i < 4; i++) {
				if firstTurn {
					i++;
					firstTurn = false;
				}
				Player* curPlayer = players_[startingPlayer + i % 4];
				vector<Card*> plays = validPlays(curPlayer->getHand());
				Command cmd = curPlayer->getCommand(plays);
				if (cmd.type == QUIT ) {
				return;
				}
				else if (cmd.type == RAGEQUIT) {
					//do shit nigguh
				}
				else if (cmd.type == DECK) {
					//do shit nigguh
				}
				curPlayer->play(cmd);
			}
		}
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

vector<Card*>& Game::validPlays(const vector<Card*>& hand) const {
	vector<Card*> validPlays;
	
	if (!table_->hearts->empty()) {
		if (table_->hearts->size() > 1)
			validPlays.push_back(new Card(table_->hearts->back()->getSuit(), table_->hearts->back()->getRank()));
		validPlays.push_back(new Card(table_->hearts->front()->getSuit(), table_->hearts->front()->getRank()));
	}
	else 
		validPlays.push_back(new Card(HEART, SEVEN));

	if (!table_->diamonds->empty()) {
		if (table_->diamonds->size() > 1)
			validPlays.push_back(new Card(table_->diamonds->back()->getSuit(), table_->diamonds->back()->getRank()));
		validPlays.push_back(new Card(table_->diamonds->front()->getSuit(), table_->diamonds->front()->getRank()));
	}
	else 
		validPlays.push_back(new Card(DIAMOND, SEVEN));

	if (!table_->spades->empty()) {
		if (table_->spades->size() > 1)
			validPlays.push_back(new Card(table_->spades->back()->getSuit(), table_->spades->back()->getRank()));
		validPlays.push_back(new Card(table_->spades->front()->getSuit(), table_->spades->front()->getRank()));
	}

	if (!table_->clubs->empty()) {
		if (table_->clubs->size() > 1)
			validPlays.push_back(new Card(table_->clubs->back()->getSuit(), table_->clubs->back()->getRank()));
		validPlays.push_back(new Card(table_->clubs->front()->getSuit(), table_->clubs->front()->getRank()));
	}
	else
		validPlays.push_back(new Card(CLUB, SEVEN));

	vector<Card*> validHand;

	for (int i = 0; i < validPlays.size(); i++) {
		for (int j = 0; j < hand.size(); j++) {
			if (*validPlays[i] == *hand[j])
				validHand.push_back(new Card(validPlays[i]->getSuit(), validPlays[i]->getRank()));
		}
	}

	return validHand;
}

// Non-member functions