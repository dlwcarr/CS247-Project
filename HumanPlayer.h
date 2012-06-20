#ifndef _HUMAN_
#define _HUMAN_

#include <vector>
#include "Player.h"
#include "Command.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	~HumanPlayer();
	Command getCommand(std::vector<Card*>&) const;
	void play(Command);
private:

}

#endif
