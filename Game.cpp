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
	for (int i = 1; i < 5; i++) {
		string input;
		cout << "Is player " << i << " a human(h) or computer(c)?" << endl << ">";
		cin >> input;
		cout << endl;
		assert(input == "h" || input == "H" || input == "c" || input == "C");
		
		if (input == "h" || input == "H") {
			players_.push_back(new HumanPlayer());
			human[i-1] = true;
		}
		else {
			players_.push_back(new ComputerPlayer());
			human[i-1] = false;
		}
	}
}

Game::~Game() {

}

void Game::start() {
	// Main game loop
	while (true) {
		this->buildDeck();
		this->shuffleDeck();
		// Give each player a pointer to the deck for DECK command
		for (int i = 0; i < 4; i++) {
			players_[i]->deck = &deck_; 
		}

		// Distribute cards
		int startingPlayer = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				if (deck_[j + (13*i)].getSuit() == SPADE && deck_[j + (13*i)].getRank() == SEVEN)
					startingPlayer = i;
				players_[i]->insertHand(deck_[j + (13*i)]);
			}
		}

		cout << "A new round begins. It's player " << (startingPlayer + 1) << "\'s turn to play." << endl;

		// Take turns
		// First player first turn
		bool firstTurn = true;
		while(true) {
			vector<Card> plays;
			plays.push_back(Card(SPADE, SEVEN));
			Command cmd = players_[startingPlayer]->getCommand(plays);
			if (cmd.type == QUIT ) {
				return;
			}
			else if (cmd.type == RAGEQUIT) {
				vector<Card> curHand = players_[startingPlayer]->getHand();
				delete players_[startingPlayer];
				players_[startingPlayer] = new ComputerPlayer();
				for( int c = 0; c < curHand.size(); c++) {
					players_[startingPlayer]->insertHand(curHand[c]);
				}
			}
			else {
				cout << "Player " << (startingPlayer + 1) << " plays 7S." << endl;
				players_[startingPlayer]->play(cmd);
				putOnTable(cmd.card);
				break;
			}
			
		}
		
		//Rest of the turns
		int j = 1;
		while(j < 52) {
			for( int i = 0; i < 4; i++, j++) {
				if (firstTurn) {
					i++;
					firstTurn = false;
				}
				int index = (startingPlayer + i) % 4;
				Player* curPlayer = players_[index];
				if(human[index])
					printTable();
				vector<Card> plays = validPlays(curPlayer->getHand());
				Command cmd = curPlayer->getCommand(plays);
				if (cmd.type == QUIT ) {
					return;
				}
				else if (cmd.type == RAGEQUIT) {
					vector<Card> curHand = curPlayer->getHand();
					vector<Card> curDiscards = curPlayer->getDiscards();
					delete players_[index];
					players_[index] = new ComputerPlayer();
					for( int c = 0; c < curHand.size(); c++) {
						players_[index]->insertHand(curHand[c]);
					}
					for( int c = 0; c < curDiscards.size(); c++) {
						players_[index]->insertDiscard(curHand[c]);
					}
					i--;
					j--;
				}
				else {
					if (cmd.type == PLAY) {
						cout << "Player " << (index + 1) << " plays " << cmd.card << endl;
						putOnTable(cmd.card);
					}
					else if (cmd.type == DISCARD) {
						cout << "Player " << (index + 1) << " discards " << cmd.card << endl;	
					}
					curPlayer->play(cmd);
				}
				
			}

		}
		for( int i = 0; i < 4; i++) {
				cout << "Player" << i << "\'s discards:";
				players_[i]->printDiscards();
				cout << "Player" << i << "\'s score:";
				players_[i]->tallyScore();
			}
		if(players_[0]->getScore() >= 80 || players_[1]->getScore() >= 80 || players_[2]->getScore() >= 80 || players_[3]->getScore() >= 80) {
			int winner = 0;
			for( int i = 1; i < 4; i++) {
				if( players_[i]->getScore() < players_[winner]->getScore() ) {
					winner = i;
				}
			}
			cout << "Player " << winner << " wins!";
			return;
		}

		
	}
}

// Private methods

void Game::shuffleDeck() {

	/* To ensure that the your cards are ordered the same way as
	the given program, use this shuffling algorithm.

	CARD_COUNT is the constant 52
	cards_ is an array of cards
	*/

	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = deck_[n];
		deck_[n] = deck_[k];
		deck_[k] = c;
	}
}


void Game::buildDeck() {
	deck_.clear();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			deck_.push_back(Card(Suit(i), Rank(j)));
		}
	}
}

vector<Card> Game::validPlays(const vector<Card>& hand) const {

	vector<Card> allValidPlays;
	
	if (!table_.hearts.empty()) {
		if (table_.hearts.back().getRank() > 0)
			allValidPlays.push_back(Card(table_.hearts.back().getSuit(), Rank(table_.hearts.back().getRank() + 1)));
		if (table_.hearts.front().getRank() < 12)
			allValidPlays.push_back(Card(table_.hearts.front().getSuit(), Rank(table_.hearts.front().getRank() + 1)));
	}
	else 
		allValidPlays.push_back(Card(HEART, SEVEN));

	if (!table_.diamonds.empty()) {
		allValidPlays.push_back(Card(table_.diamonds.back().getSuit(), table_.diamonds.back().getRank()));
		allValidPlays.push_back(Card(table_.diamonds.front().getSuit(), table_.diamonds.front().getRank()));
	}
	else 
		allValidPlays.push_back(Card(DIAMOND, SEVEN));

	if (!table_.spades.empty()) {
		allValidPlays.push_back(Card(table_.spades.back().getSuit(), table_.spades.back().getRank()));
		allValidPlays.push_back(Card(table_.spades.front().getSuit(), table_.spades.front().getRank()));
	}

	if (!table_.clubs.empty()) {
		allValidPlays.push_back(Card(table_.clubs.back().getSuit(), table_.clubs.back().getRank()));
		allValidPlays.push_back(Card(table_.clubs.front().getSuit(), table_.clubs.front().getRank()));
	}
	else
		allValidPlays.push_back(Card(CLUB, SEVEN));

	vector<Card> validHand;

	for (int i = 0; i < allValidPlays.size(); i++) {
		for (int j = 0; j < hand.size(); j++) {
			if (allValidPlays[i] == hand[j])
				validHand.push_back(Card(allValidPlays[i].getSuit(), allValidPlays[i].getRank()));
		}
	}

	return validHand;
}

void Game::printTable() const {
	cout << "Cards on the table:" << endl;
	
	cout << "Clubs:";
	for (deque<Card>::const_iterator it = table_.clubs.begin(); it != table_.clubs.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;
	
	cout << "Diamonds:";
	for (deque<Card>::const_iterator it = table_.diamonds.begin(); it != table_.diamonds.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;
	
	cout << "Hearts:";
	for (deque<Card>::const_iterator it = table_.hearts.begin(); it != table_.hearts.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;

	cout << "Spades:";
	for (deque<Card>::const_iterator it = table_.spades.begin(); it != table_.spades.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;
}

void Game::putOnTable(Card card) {
	if(card.getSuit() == CLUB) {
		if (table_.clubs.size() == 0) {
			table_.clubs.push_front(card);
		}
		else if (table_.clubs.size() == 1) {
			if (card.getRank() > 6) 
				table_.clubs.push_back(card);
			else
				table_.clubs.push_front(card);
		}
		else {
			if (card.getRank() > table_.clubs.back().getRank())
				table_.clubs.push_back(card);
			else
				table_.clubs.push_front(card);
		}
	}
	else if (card.getSuit() == DIAMOND) {
		if (table_.diamonds.size() == 0) {
			table_.diamonds.push_front(card);
		}
		else if (table_.diamonds.size() == 1) {
			if (card.getRank() > 6) 
				table_.diamonds.push_back(card);
			else
				table_.diamonds.push_front(card);
		}
		else {
			if (card.getRank() > table_.diamonds.back().getRank())
				table_.diamonds.push_back(card);
			else
				table_.diamonds.push_front(card);
		}
	}
	else if (card.getSuit() == HEART) {
		if (table_.hearts.size() == 0) {
			table_.hearts.push_front(card);
		}
		else if (table_.hearts.size() == 1) {
			if (card.getRank() > 6) 
				table_.hearts.push_back(card);
			else
				table_.hearts.push_front(card);
		}
		else {
			if (card.getRank() > table_.hearts.back().getRank())
				table_.hearts.push_back(card);
			else
				table_.hearts.push_front(card);
		}
	}
	else if (card.getSuit() == SPADE) {
		if (table_.spades.size() == 0) {
			table_.spades.push_front(card);
		}
		else if (table_.spades.size() == 1) {
			if (card.getRank() > 6) 
				table_.spades.push_back(card);
			else
				table_.spades.push_front(card);
		}
		else {
			if (card.getRank() > table_.spades.back().getRank())
				table_.spades.push_back(card);
			else
				table_.spades.push_front(card);
		}
	}
}

// Non-member functions