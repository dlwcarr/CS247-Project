#include <iostream>
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer() : Player::Player() {}

HumanPlayer::~HumanPlayer() {}

Command HumanPlayer::getCommand(vector<Card>& legalPlays) const {
	// Output player's hand
	vector<Card> hand = getHand();
	cout << "Your hand:";
	for (int i = 0; i < hand.size(); i++)
		cout << " " << hand[i];

	// Output legal plays available to player
	cout << endl << "Legal Plays:";
	for (int i = 0; i < legalPlays.size(); i++)
		cout << " " << legalPlays[i];
	cout << endl;

	// Read in command
	Command cmd;

	while (true) {
		cout << ">";
		cin >> cmd;

		// Ensure play is legal
		if (cmd.type == PLAY) {
			for (int i = 0; i < legalPlays.size(); i++) {
				if (cmd.card == legalPlays[i])
					return cmd;
			}
		}
		else if(cmd.type == DECK) {
			printDeck();
		}
		else if(cmd.type == DISCARD) {
            if(legalPlays.size()) {
                cout << "You have a legal play. You may not discard." << endl;
            }else
                return cmd;
		}else
			return cmd;
 		if(cmd.type != DECK && cmd.type != DISCARD)
 			cout << "This is not a legal play." << endl;
	}
}

void HumanPlayer::play(Command c) {
	if (c.type == PLAY) {
		removeHand(c.card);
	}
	else if (c.type == DISCARD) {
		discard(c.card);
	}
}
