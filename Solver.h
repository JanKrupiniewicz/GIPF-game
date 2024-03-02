#pragma once

class GipfGame;

enum Direction {
	RIGHT, LEFT, UPRIGHT, UPLEFT, DOWNLEFT, DOWNRIGHT, UNKNOWN
};

struct Point {
	int x, y;

	Point() = default;

	Point(int x, int y)
		: x(x), y(y) {}

	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}
};

struct WrongMove {
	char currentPlayer;
	char pos1CH;
	char pos2CH;
	int pos1IN;
	int pos2IN;

	WrongMove() = default;

	WrongMove(char currentPlayer, char pos1CH, char pos2CH, int pos1IN, int pos2IN)
		: currentPlayer(currentPlayer), pos1CH(pos1CH), pos2CH(pos2CH), pos1IN(pos1IN), pos2IN(pos2IN) {}
};

struct Line {
	char playerColor;
	Direction dir;
	Point lEnd;

	Line() = default;

	Line(char playerColor, Direction dir, int x, int y)
		: playerColor(playerColor), dir(dir) {
		lEnd.x = x;
		lEnd.y = y;
	}
};
