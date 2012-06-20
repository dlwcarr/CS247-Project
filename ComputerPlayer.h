#ifndef _COMP_
#define _COMP_

#include <vector>
#include "Player.h"

class ComputerPlayer : public Player {
public:
	ComputerPlayer();
	~ComputerPlayer();
	void play(Command);
	Command getCommand(std::vector<Card*>&) const;	
};

#endif