#include <vector>

#include "Card.h"

class Player {
public:
	Player();
	~Player();
	virtual void play() = 0;
	void discard(Card);
	void updateHand(std::vector<Card*>&);
	void tallyScore();
	int getScore() const;
private:

protected:
	std::vector<Card*> *hand_;
	std::vector<Card*> *discards_;
	int score_;
}