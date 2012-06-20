#include <vector>
#include <deque>
#include "Card.h"
#include "Player.h"

struct Table {
	std::deque<Card*> *hearts;
	std::deque<Card*> *diamonds;
	std::deque<Card*> *spades;
	std::deque<Card*> *clubs;
};

class Game {
public:
	Game();							// Constructor
	~Game();						// Destructor
	void start();					// Starts the game

private:
	void shuffleDeck();				// Shuffles the deck
	void buildDeck();
	std::vector<Card*>& validPlays(const std::vector<Card*>&) const;

	// Data members
	std::vector<Player*> *players_;	// Players
	std::vector<Card*> *deck_;		// Deck of cards
	Table *table_;					// Cards that have been played
}