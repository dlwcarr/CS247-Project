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
	if (hand_.find(cardToString(card)) != hand_.end()) {					// ensure card is in hand_
		hand_.erase(hand_.find(cardToString(card)));					// Remove card from hand_
		discards_.push_back(Card(card.getSuit(), card.getRank()));	// Add card to discards_
	}
}

void Player::insertHand(Card card) {
	hand_.insert(pair<string, Card>(cardToString(card), Card(card.getSuit(), card.getRank())));
}

void Player::insertDiscard(Card card) {
	discards_.push_back(Card(card.getSuit(), card.getRank()));
}

void Player::updateHand(vector<Card>& cards) {
	// Clear old hand
	hand_.clear();

	// Fill hand_ with cards
	for (int i = 0; i < cards.size(); i++) {
		hand_.insert(pair<string, Card>(cardToString(cards[i]), Card(cards[i].getSuit(), cards[i].getRank())));
	}
}

void Player::removeHand(Card card) {
	if (hand_.find(cardToString(card)) != hand_.end())
		hand_.erase(hand_.find(cardToString(card)));
}

void Player::tallyScore() {
	int oldScore = score_;
	for (int i = 0; i < discards_.size(); i++) 
		score_ += (discards_[i].getRank() + 1);

	cout << " " << oldScore << " + " << (score_ - oldScore) << " = " << score_ << endl;
	discards_.clear();
}

int Player::getScore() const {
	return score_;
}

Card Player::getFirstCard() const {
	map<string, Card>::const_iterator it = hand_.begin();
	return Card(it->second.getSuit(), it->second.getRank());
}

vector<Card> Player::getHand() const {
	vector<Card> c;
	for (map<string, Card>::const_iterator it = hand_.begin(); it != hand_.end(); it++)
		c.push_back(Card(it->second.getSuit(), it->second.getRank()));
	return c;
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
				cout << (*deck)[j + (13*i)];
				if (j != 12) {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
}

void Player::printDiscards() const {
	for (int i = 0; i < discards_.size(); i++) 
		cout << " " << discards_[i];
	cout << endl;

}