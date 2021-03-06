#include <iostream>

#include "Player.h"

using namespace std;

static string SUITS [] = {"C", "D", "H", "S"};
static string RANKS [] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

string cardToString(Card c) {
	return (RANKS[c.getRank()] + SUITS[c.getSuit()]);
}

Player::Player() : score_(0) {}

Player::~Player() {
	hand_.clear();
	discards_.clear();
}

void Player::discard(Card card) {
	for (vector<Card>::iterator it = hand_.begin(); it != hand_.end(); it++) {
		if (*it == card) {
			discards_.push_back(*it);
			hand_.erase(it);
			return;
		}
	}
}

void Player::insertHand(Card card) {
	hand_.push_back(card);
}

void Player::insertDiscard(Card card) {
	discards_.push_back(card);
}

void Player::updateHand(vector<Card>& cards) {
	// Clear old hand
	hand_.clear();

	// Fill hand_ with cards
	for (int i = 0; i < cards.size(); i++) {
		hand_.push_back(cards[i]);
	}
}

void Player::removeHand(Card card) {
	for (vector<Card>::iterator it = hand_.begin(); it != hand_.end(); it++) {
		if (*it == card) {
			hand_.erase(it);
			return;
		}
	}
}

void Player::tallyScore() {
	int oldScore = score_;
	for (int i = 0; i < discards_.size(); i++) 
		score_ += (discards_[i].getRank() + 1);

	cout << " " << oldScore << " + " << (score_ - oldScore) << " = " << score_ << endl;
	discards_.clear();
}

void Player::setScore(int score) {
	score_ = score;
}

int Player::getScore() const {
	return score_;
}

Card Player::getFirstCard() const {
	return hand_.front();
}

vector<Card> Player::getHand() const {
	return hand_;
}

vector<Card> Player::getDiscards() const {
	vector<Card> c;
	for (int i = 0; i < discards_.size(); i++) {
		c.push_back(discards_[i]);
	}
	return c;
}


void Player::printDeck() const {
	// Print deck_ out in 4 lines of 13 cards
	if (deck->size() == 52) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				cout << (*deck)[j + (13*i)] << " ";
			}
			cout << endl;
		}
	}
}

void Player::printDiscards() const {
	for (int i = 0; i < discards_.size(); i++) {
		cout << discards_[i];
		if (i != (discards_.size() - 1))
			cout << " ";
	}
	cout << endl;

}
