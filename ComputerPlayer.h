#ifndef _COMP_
#define _COMP_

#include <vector>
#include "Player.h"

class ComputerPlayer : public Player {
public:
	ComputerPlayer();
	~ComputerPlayer();
	void play(Command);								// Handles card manipulation necessary to make a play
	Command getCommand(std::vector<Card>&) const; 	// Takes a vector of valid plays and chooses one to play
};

#endif