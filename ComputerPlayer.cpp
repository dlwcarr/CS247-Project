#include <iostream>
#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player::Player() {}

ComputerPlayer::~ComputerPlayer() {}

Command ComputerPlayer::getCommand(vector<Card*>& cards) {
	
	command = Command();

	if (cards.size()) {
		Command.card = getFirstCard();
		Command.type = "play";
	} else {
		card = getFirstCard();
		Command.card = card;
		Command.type = discard;
	}

}

void ComputerPlayer::play(Command) {
	card = getFirstCard();
	if( Command.type = "play" ) {
		removeHand(card);
	} else {
		discard(card);
	}
}