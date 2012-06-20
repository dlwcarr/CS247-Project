#include <string>
#include <stdlib.h>
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
		cout << "Is player " << i << " a human(h) or a computer(c)?" << endl << ">";
		cin >> input;
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

	// Set up deck
	buildDeck();
}

Game::~Game() {
	for (int i = 0; i < players_.size(); i++)
		delete players_[i];
}

void Game::start() {
	// Main game loop
	while (true) {
		// Clear table between rounds
		clearTable();

		// Shuffle deck between rounds
		shuffleDeck();

		// Give each player a reference to the deck for DECK command
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
			// On the first turn, 7S is the only valid play
			vector<Card> validPlays;
			validPlays.push_back(Card(SPADE, SEVEN));

			// Get command from first player
			Command cmd = players_[startingPlayer]->getCommand(validPlays);

			if (cmd.type == QUIT ) // Quit if necessary
				return;

			else if (cmd.type == RAGEQUIT) {
				// If player RAGEQUITs on first turn they have no discards and score = 0
				// Get player's hand
				vector<Card> curHand = players_[startingPlayer]->getHand();

				// Delete old player
				delete players_[startingPlayer];

				// Create a new computer player to take their place
				players_[startingPlayer] = new ComputerPlayer();

				// Update new computer player with old player's hand
				for( int c = 0; c < curHand.size(); c++)
					players_[startingPlayer]->insertHand(curHand[c]);

			}
			else {
				// First move can't be a DISCARD, so it must be a PLAY
				cout << "Player " << (startingPlayer + 1) << " plays " << cmd.card << "." << endl;

				// Tell player to execute its move
				players_[startingPlayer]->play(cmd);

				// Add card to the table
				putOnTable(cmd.card);

				// Continue to the next turn
				break;
			}
		}

		//Rest of the turns
		int j = 1;
		while(j < 52) { // Every turn is either a PLAY or DISCARD, so max 52 turns in a round

			for( int i = 0; i < 4; i++, j++) { // Loop through players

				if (firstTurn) {
					i++;
					firstTurn = false;
				}

				// Determine which turn it is
				int index = (startingPlayer + i) % 4;

				Player* curPlayer = players_[index];

				// Print table for human players
				if(human[index])
					printTable();

				// Get command from current player
				vector<Card> vPlays = validPlays(curPlayer->getHand());
				Command cmd = curPlayer->getCommand(vPlays);

				// End game on QUIT command
				if (cmd.type == QUIT )
					return;

				else if (cmd.type == RAGEQUIT) { // Replace player with a computer player
					// Get player's state
					vector<Card> curHand = curPlayer->getHand();
					vector<Card> curDiscards = curPlayer->getDiscards();
					int score = curPlayer->getScore();

					// Delete old player
					delete players_[index];

					// Create new computer player
					players_[index] = new ComputerPlayer();

					// Transfer old player's state to new player
					for (int c = 0; c < curHand.size(); c++)
						players_[index]->insertHand(curHand[c]);

					for (int c = 0; c < curDiscards.size(); c++)
						players_[index]->insertDiscard(curHand[c]);

					players_[index]->setScore(score);

					// Redo current turn
					i--;
					j--;
				}
				else {
					if (cmd.type == PLAY) {
						cout << "Player " << (index + 1) << " plays " << cmd.card << "." << endl;
						// Put card on table
						putOnTable(cmd.card);
					}
					else if (cmd.type == DISCARD)
						cout << "Player " << (index + 1) << " discards " << cmd.card << "." << endl;

					// Execute Command cmd
					curPlayer->play(cmd);
				}
			}
		}

		// Output end of round info
		for (int i = 0; i < 4; i++) {
			cout << "Player " << (i + 1) << "\'s discards: ";
			players_[i]->printDiscards();
			cout << "Player " << (i + 1) << "\'s score:";
			players_[i]->tallyScore();
		}

		// Check if game is over
		if (players_[0]->getScore() >= 80 || players_[1]->getScore() >= 80 || players_[2]->getScore() >= 80 || players_[3]->getScore() >= 80) {

			int winner = 0;
			for( int i = 1; i < 4; i++) {
				// Find player with the lowest score
				if (players_[i]->getScore() < players_[winner]->getScore())
					winner = i;
			}

			// Output win message and end game
			cout << "Player " << (winner + 1) << " wins!" << endl;
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

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = deck_[n];
		deck_[n] = deck_[k];
		deck_[k] = c;
	}
}


void Game::buildDeck() { // Create a new ordered deck from scratch
	deck_.clear();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++)
			deck_.push_back(Card(Suit(i), Rank(j)));
	}
}

vector<Card> Game::validPlays(const vector<Card>& hand) const { // Find valid plays in hand

	vector<Card> allValidPlays;

	if (!table_.hearts.empty()) {
		// Check both ends of the table
		if (table_.hearts.back().getRank() < 12)
			allValidPlays.push_back(Card(HEART, Rank(table_.hearts.back().getRank() + 1)));
		if (table_.hearts.front().getRank() > 0)
			allValidPlays.push_back(Card(HEART, Rank(table_.hearts.front().getRank() - 1)));
	}
	// Sevens are always valid
	else
		allValidPlays.push_back(Card(HEART, SEVEN));

	if (!table_.diamonds.empty()) {
		// Check both ends of the table
		if (table_.diamonds.back().getRank() < 12)
			allValidPlays.push_back(Card(DIAMOND, Rank(table_.diamonds.back().getRank() + 1)));
		if (table_.diamonds.front().getRank() > 0)
			allValidPlays.push_back(Card(DIAMOND, Rank(table_.diamonds.front().getRank() - 1)));
	}
	// Sevens are always valid
	else
		allValidPlays.push_back(Card(DIAMOND, SEVEN));

	if (!table_.spades.empty()) {
		// Check both ends of the table
		if (table_.spades.back().getRank() < 12)
			allValidPlays.push_back(Card(SPADE, Rank(table_.spades.back().getRank() + 1)));
		if (table_.spades.front().getRank() > 0)
			allValidPlays.push_back(Card(SPADE, Rank(table_.spades.front().getRank() - 1)));
	}
	// 7S is always on the table => not valid

	if (!table_.clubs.empty()) {
		// Check both ends of the table
		if (table_.clubs.back().getRank() < 12)
			allValidPlays.push_back(Card(CLUB, Rank(table_.clubs.back().getRank() + 1)));
		if (table_.clubs.front().getRank() > 0)
			allValidPlays.push_back(Card(CLUB, Rank(table_.clubs.front().getRank() - 1)));
	}
	// Sevens are always valid
	else
		allValidPlays.push_back(Card(CLUB, SEVEN));

	vector<Card> validHand;

	// Look for matches between hand and allValidPlays
	for (int i = 0; i < hand.size(); i++) {
		for (int j = 0; j < allValidPlays.size(); j++) {
			if (allValidPlays[j] == hand[i])
				validHand.push_back(hand[i]);
		}
	}

	return validHand;
}

void Game::printTable() const {
	cout << "Cards on the table:" << endl;

	cout << "Clubs:";
	for (deque<Card>::const_iterator it = table_.clubs.begin(); it != table_.clubs.end(); it++) {
        int rank = it->getRank() + 1;
        if ( rank == 11) {
            cout << " " << "J";
        } else if ( rank == 12) {
            cout << " " << "Q";
        }
        else if ( rank == 13) {
            cout << " " << "K";
        }
        else {
            cout << " " << (it->getRank() + 1);
        }
	}

	cout << endl;

	cout << "Diamonds:";
	for (deque<Card>::const_iterator it = table_.diamonds.begin(); it != table_.diamonds.end(); it++) {
		int rank = it->getRank() + 1;
        if ( rank == 11) {
            cout << " " << "J";
        } else if ( rank == 12) {
            cout << " " << "Q";
        }
        else if ( rank == 13) {
            cout << " " << "K";
        }
        else {
            cout << " " << (it->getRank() + 1);
        }
	}
	cout << endl;

	cout << "Hearts:";
	for (deque<Card>::const_iterator it = table_.hearts.begin(); it != table_.hearts.end(); it++) {
		int rank = it->getRank() + 1;
        if ( rank == 11) {
            cout << " " << "J";
        } else if ( rank == 12) {
            cout << " " << "Q";
        }
        else if ( rank == 13) {
            cout << " " << "K";
        }
        else {
            cout << " " << (it->getRank() + 1);
        }
	}
	cout << endl;

	cout << "Spades:";
	for (deque<Card>::const_iterator it = table_.spades.begin(); it != table_.spades.end(); it++) {
		int rank = it->getRank() + 1;
        if ( rank == 11) {
            cout << " " << "J";
        } else if ( rank == 12) {
            cout << " " << "Q";
        }
        else if ( rank == 13) {
            cout << " " << "K";
        }
        else {
            cout << " " << (it->getRank() + 1);
        }
	}
	cout << endl;
}

void Game::putOnTable(Card card) {
	// Find correct deque to place card in
	if(card.getSuit() == CLUB) {

		// If empty, doesn't matter where it goes
		if (table_.clubs.size() == 0)
			table_.clubs.push_front(card);

		// Find which side to push card on
		else {
			if (card.getRank() > table_.clubs.back().getRank())
				table_.clubs.push_back(card);
			else
				table_.clubs.push_front(card);
		}
	}
	else if (card.getSuit() == DIAMOND) {
		if (table_.diamonds.size() == 0)
			table_.diamonds.push_front(card);

		else {
			if (card.getRank() > table_.diamonds.back().getRank())
				table_.diamonds.push_back(card);
			else
				table_.diamonds.push_front(card);
		}
	}
	else if (card.getSuit() == HEART) {
		if (table_.hearts.size() == 0)
			table_.hearts.push_front(card);

		else {
			if (card.getRank() > table_.hearts.back().getRank())
				table_.hearts.push_back(card);
			else
				table_.hearts.push_front(card);
		}
	}
	else if (card.getSuit() == SPADE) {
		if (table_.spades.size() == 0)
			table_.spades.push_front(card);

		else {
			if (card.getRank() > table_.spades.back().getRank())
				table_.spades.push_back(card);
			else
				table_.spades.push_front(card);
		}
	}
}

void Game::clearTable() {
	table_.clubs.clear();
	table_.diamonds.clear();
	table_.hearts.clear();
	table_.spades.clear();
}

// Non-member functions
