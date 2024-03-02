#pragma once

class Player
{
private:
	int totalNumbPieces;
	int piecesInReserve;
public:
	Player() = default;
	Player(int totalNumbPieces, int piecesInReserve);
	bool makeMove();
	bool checkPCorrect(int countP) const;
	int getTotalNP() const;
	void setTotalNP();
	int getResevedP() const;
	void increseRP(int numb);
	void decreseRP(int numb);
	void setResevedP();
};