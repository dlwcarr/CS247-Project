#include <iostream>

#include "Player.h"

using namespace std;

Player::Player() : score_(0) {
	hand_ = new map<string, Card*>;
	discards_ = new vector<Card*>;
}

Player::~Player() {
	// Dealloc cards
	hand_->clear();
	delete hand_;

	discards_->clear();
	delete discards_;
}

void Player::discard(Card& card) {
	if (hand_->find(cardToString(card)) != map::end) {					// ensure card is in hand_
		hand_->erase(hand_->find(cardToString(card)));					// Remove card from hand_
		discards_->push_back(new Card(card.getSuit(), card.getRank()));	// Add card to discards_
	}
}

void Player::insertHand(Card& card) {
	hand_->insert(pair<string, Card*>(cardToString(card), new Card(card.getSuit(), card.getRank())));
}

void Player::insertDiscard(Card& card) {
	discards_->insert(pair<string, Card*>(cardToString(card), new Card(card.getSuit(), card.getRank())));
}

void Player::updateHand(vector<Card*>& cards) {
	// Clear old hand
	hand_->clear();

	// Fill hand_ with cards
	for (int i = 0; i < cards->size(); i++) {
		hand_->insert(pair<string, Card*>(cardToString(*cards[i]), new Card(cards[i]->getSuit(), cards[i]->getRank())));
	}
}

void Player::removeHand(Card& card) {
	if (hand_->find(cardToString(card)) != map::end)
		hand_->remove(hand_->find(cardToString(card)));
}

void Player::tallyScore() {
	int oldScore = score_;
	for (int i = 0; i < discards_->size(); i++) 
		score_ += (discards_[i]->getRank() + 1);

	cout << " " << oldScore << " + " << (score_ - oldScore) << " = " << score_ << endl;
	discards_->clear();
}

int Player::getScore() const {
	return score_;
}

Card Player::getFirstCard() const {
	map<string, Card*>::iterator it = hand_->begin();
	return Card(it->getSuit(), it->getRank());
}

vector<Card*>& Player::getHand() const {
	vector<Card*> c;
	for (map<string, Card*>::iterator it = hand_.begin(); it != hand_.end(); it++)
		c.push_back(new Card(it->getSuit(), it->getRank()));
	return c;
}

vector<Card*>& Player::getDiscards() const {
	vector<Card*> c;
	for (map<string, Card*>::iterator it = discards_.begin(); it != discards_.end(); it++)
		c.push_back(new Card(it->getSuit(), it->getRank()));
	return c;
}


void Player::printDeck() {
	// Print deck_ out in 4 lines of 13 cards
	if (deck->size() == 52) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				cout << deck[j + (13*i)];
				if (j != 12) {
					cout << " ";
				}
			}
			cout << endl;
		}
	}


void Player::printDiscards() const {
	for (int i = 0; i < discards_.size(); i++) 
		cout << " " << *discards_[i];
	cout << endl;

}

// Non-member functions

string cardToString(Card c) {
	return (RANKS[c.getRank()] + SUITS[c.getSuit()]);
}

static string SUITS = {"C", "D", "H", "S"};
static string RANKS = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};