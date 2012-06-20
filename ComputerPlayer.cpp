#include <iostream>
#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player::Player() {}

ComputerPlayer::~ComputerPlayer() {}

Command ComputerPlayer::getCommand(vector<Card>& cards) const {

	Command command;

	if (cards.size()) {
		command.card = Card(cards[0].getSuit(), cards[0].getRank());
		command.type = PLAY;
	} else {
		command.card = getFirstCard();
		command.type = DISCARD;
	}

	return command;

}

// right here, nigga. dis da problem yo
void ComputerPlayer::play(Command cmd) {
	if( cmd.type == PLAY ) {
		removeHand(cmd.card);
	} else {
		discard(cmd.card);
	}
}
