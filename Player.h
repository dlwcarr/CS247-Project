#include <vector>
#include <map>
#include "Command.h"
#include "Card.h"

class Player {
public:
	Player();
	~Player();
	virtual Command getCommand(std::vector<Card*>&) const = 0;
	virtual void play(Command) = 0;
	void discard(Card&);
	void insertHand(Card&);
	void insertDiscard(Card&);
	void updateHand(std::vector<Card*>&);
	void removeHand(Card&);
	void tallyScore();
	int getScore() const;
	Card getFirstCard() const;
	std::vector<Card*>& getHand() const;
	std::vector<Card*>& getDiscards() const;
	std::vector<Card*> *deck;
	void printDiscards() const;

private:
	void printDeck();
	std::map<std::string, Card*> *hand_;
	std::vector<Card*> *discards_;
	int score_;	
};