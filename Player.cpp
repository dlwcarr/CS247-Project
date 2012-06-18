#include <iostream>

#include "Player.h"

using namespace std;

Player::Player() : score_(0) {
	hand_ = new vector<Card*>();
	discards_ = new vector<Card*>();
}

Player::~Player() {
	// Dealloc cards
	hand_->clear();
	delete hand_;

	discards_->clear();
	delete discards_;
}

void Player::discard(Card& card) {
	for (int i = 0; i < hand_->size(); i++) {
		
		// Look for card in hand_
		if ((*hand_[i]) ==  card) {
			
			// Remove card from hand_
			Card* temp = hand_[i];
			hand_[i] = hand_->back();
			hand_->back() = temp;
			hand_->pop_back();

			// Insert card into discards_
			discards_->push_back(temp);
			return;
		}
	}
}

void Player::insertHand(Card& card) {
	hand_->push_back(new Card(card.getSuit(), card.getRank()));
}

void Player::updateHand(vector<Card*>& cards) {
	// Clear old hand
	hand_->clear();

	// Fill hand_ with cards
	for (int i = 0; i < cards->size(); i++) {
		hand_->push_back(new Card(cards[i]->getSuit(), cards[i]->getRank()));
	}
}

void Player::tallyScore() {
	for (int i = 0; i < discards_->size(); i++) 
		score_ += (discards_[i]->getRank() + 1);
	discards_->clear();
}

int Player::getScore() const {
	return score_;
}