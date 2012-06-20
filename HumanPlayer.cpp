#include <iostream>
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer() {
	
}

HumanPlayer::~HumanPlayer() {

}

Command HumanPlayer::getCommand(vector<Card*>& legalPlays) const {
	cout << "Legal plays:";
	for (int i = 0; i < legalPlays.size(); i++) {
		cout << legalPlays[i];
		if (i != legalPlays.size() - 1)
			cout << " ";
	}
	cout << endl;
}

void HumanPlayer::play(Command c) {

}