#ifndef _GAME_
#define _GAME_

#include <vector>
#include <deque>
#include "Card.h"
#include "Player.h"

struct Table {
	std::deque<Card> hearts;
	std::deque<Card> diamonds;
	std::deque<Card> spades;
	std::deque<Card> clubs;
};

class Game {
public:
	Game();							// Constructor
	~Game();						// Destructor
	void start();					// Starts the game
	void printTable() const;

private:
	void shuffleDeck();				// Shuffles the deck
	void buildDeck();				// Creates a deck in order
	std::vector<Card> validPlays(const std::vector<Card>&) const; // Finds valid plays in parameter vector based on whats on the table
	void putOnTable(Card);			// Add a card to the table
	void clearTable();				// Clear cards from table

	// Data members
	bool human[4];					// Check if a player is human or not
	std::vector<Player*> players_;	// Players
	std::vector<Card> deck_;		// Deck of cards
	Table table_;					// Cards that have been played
};

#endif