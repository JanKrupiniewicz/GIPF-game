#include "Player.h"
#include <iostream>

Player::Player(int totalNumbPieces, int piecesInReserve)
	: totalNumbPieces(totalNumbPieces), piecesInReserve(piecesInReserve) {}

bool Player::makeMove() {
	piecesInReserve--;
	if (piecesInReserve < 0) {
		return true;
	}
	return false;
}

bool Player::checkPCorrect(int countP) const
{
	if (totalNumbPieces < piecesInReserve + countP) {
		return false;
	}
	return true;
}

int Player::getTotalNP() const {
	return totalNumbPieces;
}

void Player::setTotalNP() {
	std::cin >> totalNumbPieces;
}

int Player::getResevedP() const {
	return piecesInReserve;
}

void Player::increseRP(int numb) {
	piecesInReserve += numb;
}

void Player::decreseRP(int numb) {
	piecesInReserve -= numb;
}

void Player::setResevedP() {
	std::cin >> piecesInReserve;
}
