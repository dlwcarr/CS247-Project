#include <iostream>
#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player::Player() {}

ComputerPlayer::~ComputerPlayer() {}

Command ComputerPlayer::getCommand(vector<Card*>& cards) const {

	command = Command();

	if (cards.size()) {
		Command.card = Card(cards[0]->getSuit(), cards[0]->getRank());
		Command.type = PLAY;
	} else {
		Command.card = getFirstCard();
		Command.type = discard;
	}

}

void ComputerPlayer::play(Command) {
	card = getFirstCard();
	if( Command.type == PLAY ) {
		removeHand(card);
	} else {
		discard(card);
	}
}
