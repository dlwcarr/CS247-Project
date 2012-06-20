#include <vector>
#include "Player.h"
#include "Command.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	~HumanPlayer();
	void play(Command);
	Command getCommand() const;
private:
	
}