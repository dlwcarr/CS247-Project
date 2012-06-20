#include <iostream>
#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player::Player() {}

ComputerPlayer::~ComputerPlayer() {}

Command ComputerPlayer::getCommand(vector<Card>& cards) const {

	Command command;

	// If a valid play is available, pick the first one
	if (cards.size() != 0) {
		command.card = cards[0];
		command.type = PLAY;
	}
	// Otherwise discard first card in hand 
	else {
		command.card = getFirstCard();
		command.type = DISCARD;
	}

	return command;
}

void ComputerPlayer::play(Command cmd) {
	// Remove card from hand
	if (cmd.type == PLAY)
		removeHand(cmd.card);

	// Move card from hand to discards
	else
		discard(cmd.card);
}
