#pragma once
#include "Player.h"
#include "Solver.h"
#include <vector>

class GipfGame
{
private:
	int gameState;
	
	int boardSize;
	int piecestoRemove;
	char currentPlayer;
	char** board;

	WrongMove wrongMove;
	Player playerW;
	Player playerB;
	
	int checkPawnsStatus(char funcType, Point strPt = Point(), Point endP = Point(), Direction extDir = UNKNOWN);
	void deletePawns(Line checkL);
	bool isOnBoard(Point pt) const;
	bool checkValidMove(char pos1CH, int pos1IN) const;
	Direction checkValidExtPos(Point& startP, Point& endP) const;
	bool checkValidExtColor(Point& startP, char extColor) const;
	bool checkStartFiled(char pos1CH, int pos1IN) const;
	static Direction getDir(char pos1CH, char pos2CH, int pos1IN, int pos2IN);
	static Direction invertDir(Direction dir);
	Point lineFull(Direction moveDir, Point strPt);
	static Point getNextPoint(Point pt, Direction dir);
	void pushPawns(Direction moveDir, Point strPt, Point& checkPt);
	Point getStartPoint(char pos2CH, int pos2IN) const;
	void makeMove(Point strPt);

public:
	GipfGame();
	~GipfGame();
	void loadBoard();
	void displayBoard();
	void UserMove(char pos1CH, char pos2CH, int pos1IN, int pos2IN, int extPos1INT, char extPos1CH, int extPos2INT, char extPos2CH, char extColor);
	void printGameState() const;


	friend class Solver;
};