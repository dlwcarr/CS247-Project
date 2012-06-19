#include <vector>
#include "Command.h"
#include "Card.h"

class Player {
public:
	Player();
	~Player();
	virtual void play(Command) = 0;
	virtual Command getCommand() const = 0;
	void discard(Card&);
	void insertHand(Card&);
	void updateHand(std::vector<Card*>&);
	void tallyScore();
	int getScore() const;
private:
	std::vector<Card*> *hand_;
	std::vector<Card*> *discards_;
	int score_;
protected:
	
}