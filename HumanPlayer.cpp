#include <iostream>
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer() {
	
}

HumanPlayer::~HumanPlayer() {

}

Command HumanPlayer::getCommand(vector<Card*>& legalPlays) const {
	vector<Card*> hand = getHand();
	cout << "Your hand:";
	for (int i = 0; i < hand.size(); i++)
		cout << " " << hand[i];
	cout << endl << "Legal plays:";
	for (int i = 0; i < legalPlays.size(); i++)
		cout << " " << legalPlays[i];
	cout << endl;

	Command cmd;
	bool flag = true;

	while (flag) {
		cout << ">";
		cin >> cmd;
		if (cmd.type == PLAY) {
			for (int i = 0; i < legalPlays->size(); i++) {
				if (cmd.card == *legalPlays[i])
					flag = false;
			}
		}
		else 
			flag = false;
	}

	return cmd;
}

void HumanPlayer::play(Command c) {
	if (c.type == PLAY) {
		removeHand(c.card);
	}
	else if (c.type == DISCARD) {
		discard(c.card);
	}
}