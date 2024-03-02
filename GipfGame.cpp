#include "GipfGame.h"
#include <iostream>
#include <string>

GipfGame::GipfGame() 
        : boardSize(0), board(nullptr), piecestoRemove(0), currentPlayer('\0'), gameState(0) {
    playerW = Player{};
    playerB = Player{};
    wrongMove = WrongMove{};
}

void GipfGame::loadBoard() {
    std::cin >> boardSize;
    board = new char* [2 * boardSize - 1];
    for (int i = 0; i < 2 * boardSize - 1; i++) {
        board[i] = new char[2 * boardSize - 1];
        std::fill(board[i], board[i] + 2 * boardSize - 1, '.');
    }
    std::cin >> piecestoRemove;
    playerW.setTotalNP();
    playerB.setTotalNP();
    std::cin.ignore();
    playerW.setResevedP();
    playerB.setResevedP();
    std::cin >> currentPlayer;
    std::cin.ignore();
    gameState = 0;

    if (piecestoRemove < 1 || piecestoRemove > 2 * boardSize - 1) {
        std::cout << "WRONG_PAWNS_REMOVAL_NUMBER" << std::endl;
        return;
    }
    int countW{};
    int countB{};
    int countC{};
    bool correctLength = true;
    int checkLength = boardSize - 1;
    int itr = 0;
    for (int i = 0; i < 2 * boardSize - 1; i++) {
        int k = countC = 0;
        std::string line;
        std::getline(std::cin, line);
        if (i < (2 * boardSize) / 2) {
            checkLength++;
        }
        else {
            checkLength--; itr++;
        }
        for (int j = 0; j < line.length(); j++) {
            if (line[j] != ' ') {
                board[i][itr + k] = line[j];
                k++;
            }
            if (line[j] == 'W') {
                countW++;
            }
            else if (line[j] == 'B') {
                countB++;
            }
            if (line[j] > 64) {
                countC++;
            }
        }
        if (countC != checkLength) {
            correctLength = false;
        }
    }
    if (!correctLength) {
        std::cout << "WRONG_BOARD_ROW_LENGTH" << std::endl;
        return;
    }
    bool testW = playerW.checkPCorrect(countW);
    if (!testW) {
        std::cout << "WRONG_WHITE_PAWNS_NUMBER" << std::endl;
        return;
    }
    bool testB = playerB.checkPCorrect(countB);
    if (!testB) {
        std::cout << "WRONG_BLACK_PAWNS_NUMBER" << std::endl;
        return;
    }
    int numL = checkPawnsStatus('B');
    if (numL == 0) {
        std::cout << "BOARD_STATE_OK" << std::endl;
        gameState = 1;
    }
    else if (numL == 1){
        std::cout << "ERROR_FOUND_" << numL << "_ROW_OF_LENGTH_K" << std::endl;
    }
    else {
        std::cout << "ERROR_FOUND_" << numL << "_ROWS_OF_LENGTH_K" << std::endl;
    }
}

void GipfGame::deletePawns(Line checkL) {
    int deleteW{};
    int deleteB{};
    Point newPt = checkL.lEnd;
    while (true) {
        if (!isOnBoard(newPt)) {
            break;
        }
        if (board[newPt.y][newPt.x] == 'W') {
            deleteW++;
        }
        else if (board[newPt.y][newPt.x] == 'B') {
            deleteB++;
        }
        else {
            break;
        }
        board[newPt.y][newPt.x] = '_';
        newPt = getNextPoint(newPt, checkL.dir);
    }
    Direction inv = invertDir(checkL.dir);
    newPt = getNextPoint(checkL.lEnd, inv);
    while (true) {
        if (!isOnBoard(newPt)) {
            break;
        }
        if (board[newPt.y][newPt.x] == 'W') {
            deleteW++;
        }
        else if (board[newPt.y][newPt.x] == 'B') {
            deleteB++;
        }
        else {
            break;
        }
        board[newPt.y][newPt.x] = '_';
        newPt = getNextPoint(newPt, inv);
    }

    if (currentPlayer == checkL.playerColor) {
        if (currentPlayer == 'W') {
            playerW.increseRP(deleteW);
        }
        else {
            playerB.increseRP(deleteB);
        }
    }
    else {
        if (currentPlayer == 'W') {
            playerB.increseRP(deleteB);
        }
        else {
            playerW.increseRP(deleteW);
        }
    }
}

int GipfGame::checkPawnsStatus(char funcType, Point strPt, Point endP, Direction extDir) {
    int ctr{};
    if (extDir == UNKNOWN || extDir == RIGHT)
        for (int i = 0; i < 2 * boardSize - 1; i++) {
            int countW{};
            int countB{};
            for (int j = 0; j < 2 * boardSize - 1; j++) {
                if (board[i][j] == 'W') {
                    countW++;
                    countB = 0;
                }
                else if (board[i][j] == 'B') {
                    countB++;
                    countW = 0;
                }
                else {
                    countW = 0;
                    countB = 0;
                }

                if (countW >= piecestoRemove && (j + 1 == 2 * boardSize - 1 || board[i][j + 1] != 'W')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'W', RIGHT, j, i });
                    ctr++;
                }
                else if (countB >= piecestoRemove && (j + 1 == 2 * boardSize - 1 || board[i][j + 1] != 'B')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'B', RIGHT, j, i });
                    ctr++;
                }
            }
        }

    if (extDir == UNKNOWN || extDir == DOWNLEFT)
        for (int j = 0; j < 2 * boardSize - 1; j++) {
            int countW{};
            int countB{};
            for (int i = 0; i < 2 * boardSize - 1; i++) {
                if (board[i][j] == 'W') {
                    countW++;
                    countB = 0;
                }
                else if (board[i][j] == 'B') {
                    countB++;
                    countW = 0;
                }
                else {
                    countW = 0;
                    countB = 0;
                }

                if (countW >= piecestoRemove && (i + 1 == 2 * boardSize - 1 || board[i + 1][j] != 'W')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'W', DOWNLEFT, j, i });
                    ctr++;
                }
                else if (countB >= piecestoRemove && (i + 1 == 2 * boardSize - 1 || board[i + 1][j] != 'B')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'B', DOWNLEFT, j, i });
                    ctr++;
                }
            }
        }

    if (extDir == UNKNOWN || extDir == UPLEFT) {
        for (int i = 0; i < 2 * boardSize - 1; i++) {
            int countW{};
            int countB{};

            for (int j = 0; j < 2 * boardSize - 1 - i; j++) {
                if (board[i + j][j] == 'W') {
                    countW++;
                    countB = 0;
                }
                else if (board[i + j][j] == 'B') {
                    countB++;
                    countW = 0;
                }
                else {
                    countW = 0;
                    countB = 0;
                }

                if (countW >= piecestoRemove && (i + j + 1 == 2 * boardSize - 1 || board[i + j + 1][j + 1] != 'W')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'W', UPLEFT, j, i + j });
                    ctr++;
                }
                else if (countB >= piecestoRemove && (i + j + 1 == 2 * boardSize - 1 || board[i + j + 1][j + 1] != 'B')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'B', UPLEFT, j, i + j });
                    ctr++;
                }
            }
        }
        for (int i = 1; i < 2 * boardSize - 1; i++) {
            int countW{};
            int countB{};

            for (int j = 0; j < 2 * boardSize - 1 - i; j++) {
                if (board[j][i + j] == 'W') {
                    countW++;
                    countB = 0;
                }
                else if (board[j][i + j] == 'B') {
                    countB++;
                    countW = 0;
                }
                else {
                    countW = 0;
                    countB = 0;
                }

                if (countW >= piecestoRemove && (i + j + 1 == 2 * boardSize - 1 || board[i + j + 1][j + 1] != 'W')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'W', UPLEFT, i + j, j });
                    ctr++;
                }
                else if (countB >= piecestoRemove && (i + j + 1 == 2 * boardSize - 1 || board[i + j + 1][j + 1] != 'W')) {
                    if (funcType == 'Q' || funcType == 'X') deletePawns({ 'B', UPLEFT, i + j, j });
                    ctr++;
                }
            }
        }
    }
    return ctr;
}

void GipfGame::displayBoard() {
    if (gameState == 0) {
        std::cout<< "EMPTY_BOARD" << std::endl;
        return;
    }
    int spacing = boardSize - 1;
    int countJMax = boardSize;
    int itr = 0;
    std::cout << std::endl;
    std::cout << boardSize << " " << piecestoRemove << " " << playerW.getTotalNP() << " " << playerB.getTotalNP();
    std::cout << std::endl << playerW.getResevedP() << " " << playerB.getResevedP() << " " << currentPlayer << std::endl;
    for (int i = 0; i < 2 * boardSize - 1; i++) {
        for (int j = 0; j < spacing; j++)
            std::cout << " ";

        for (int j = 0; j < countJMax; j++) {
            std::cout << board[i][itr + j] << " ";
        }
        std::cout << std::endl;

        if (i < (2 * boardSize - 1) / 2) {
            spacing--; countJMax++;
        }
        else {
            spacing++; countJMax--; itr++;
        }
    }
    std::cout << std::endl;
}

bool GipfGame::checkValidMove(char pos1CH, int pos1IN) const {
    int maxN{};
    if (pos1CH > boardSize + 97) {
        maxN = 3 * boardSize + 1 + 97 - pos1CH;
    }
    else {
        maxN = boardSize + 1 - 97 + pos1CH;
    }
    if (97 > pos1CH || pos1CH > 97 + 2 * boardSize || pos1IN > maxN || pos1IN == 0) {
        return true;
    }
    return false;
}

bool GipfGame::checkStartFiled(char pos1CH, int pos1IN) const {
    if (pos1CH != 97 && pos1CH != 97 + 2 * boardSize) {
        int maxN{};
        if (pos1CH > boardSize + 97) {
            maxN = 3 * boardSize + 1 + 97 - pos1CH;
        }
        else {
            maxN = boardSize + 1 - 97 + pos1CH;
        }
        if (pos1IN != 1 && pos1IN != maxN) {
            return true;
        }
    }
    return false;
}

Direction GipfGame::invertDir(Direction dir) {
    switch(dir) {
    case RIGHT:
        return LEFT;
        break;
    case LEFT:
        return RIGHT;
        break;
    case UPRIGHT:
        return DOWNLEFT;
        break;
    case UPLEFT:
        return DOWNRIGHT;
        break;
    case DOWNRIGHT:
        return UPLEFT;
        break;
    case DOWNLEFT:
        return UPRIGHT;
        break;
    default:
        return UNKNOWN;
        break;
    }
}

Point GipfGame::getNextPoint(Point point, Direction dir)
{
    switch (dir) {
    case RIGHT:
        return { point.x + 1, point.y };
        break;
    case LEFT:
        return { point.x - 1, point.y };
        break;
    case UPRIGHT:
        return { point.x, point.y - 1 };
        break;
    case UPLEFT:
        return { point.x - 1, point.y - 1 };
        break;
    case DOWNRIGHT:
        return { point.x + 1, point.y + 1 };
        break;
    case DOWNLEFT:
        return { point.x, point.y + 1 };
        break;
    default:
        return {-1, -1};
        break;
    }
}

bool GipfGame::isOnBoard(Point pt) const {
    if (pt.x >= 0 && pt.x < 2 * boardSize - 1 && pt.y >= 0 && pt.y < 2 * boardSize - 1 && board[pt.y][pt.x] != '.') {
        return true;
    }
    return false;
}

Point GipfGame::lineFull(Direction moveDir, Point strPt) {
    Point newPt = strPt;
    while (true) {
        if (!isOnBoard(newPt)) {
            return {-1, -1};
        }
        if (board[newPt.y][newPt.x] != 'W' && board[newPt.y][newPt.x] != 'B') {
            return {newPt.x, newPt.y};
        }
        newPt = getNextPoint(newPt, moveDir);
    }
}

Direction GipfGame::getDir(char pos1CH, char pos2CH, int pos1IN, int pos2IN)
{
    if (pos1CH + 1 < pos2CH) {
        return UNKNOWN;
    }

    if (pos1CH == pos2CH) {
        if (pos1IN < pos2IN) {
            return UPRIGHT;
        }
        else if (pos1IN > pos2IN) {
            return DOWNLEFT;
        }
    }
    else if (pos1IN == pos2IN) {
        if (pos1CH < pos2CH) {
            return DOWNRIGHT;
        }
        else if (pos1CH > pos2CH) {
            return LEFT;
        }
    }
    else {
        if (pos1CH < pos2CH) {
            if (pos1IN < pos2IN) {
                return RIGHT;
            }
            else {
                return DOWNRIGHT;
            }
        }
        else {
            if (pos1IN < pos2IN) {
                return UPLEFT;
            }
            else {
                return DOWNRIGHT;
            }
        }
    }
    return UNKNOWN;
}

Point GipfGame::getStartPoint(char pos2CH, int pos2IN) const {
    Point point{}; 
    point.x = pos2CH - 98;
    int itr = boardSize;
    for (int i = 0; i < 2 * boardSize - 1; i++) {
        if (i < boardSize) {
            itr--;
        }
        else {
            itr++;
        }
        if (i == point.x) {
            break;
        }
    }
    if (point.x < boardSize) {
        int numFields = 2 * boardSize - itr;
        point.y = numFields - pos2IN;
    }
    else {
        int numFields = 2 * boardSize;
        point.y = numFields - pos2IN;
    }
    return point;
}

void GipfGame::makeMove(Point strPt)
{
    if (currentPlayer == 'W') {
        bool pW = playerW.makeMove();
        if (pW) {
            std::cout << "WHITE_PLAYER_LOOSES" << std::endl;
            gameState = 3;
            return;
        }
        board[strPt.y][strPt.x] = currentPlayer;
        currentPlayer = 'B';
    }
    else {
        bool pB = playerB.makeMove();
        if (pB) {
            std::cout << "BLACK_PLAYER_LOOSES" << std::endl;
            gameState = 2;
            return;
        }
        board[strPt.y][strPt.x] = currentPlayer;
        currentPlayer = 'W';
    }

}

void GipfGame::pushPawns(Direction moveDir, Point strPt, Point& checkPt)
{
    Direction invDir = invertDir(moveDir);
    Point currentPt = checkPt;

    while (currentPt != strPt)
    {
        Point prevPt = getNextPoint(currentPt, invDir);
        board[currentPt.y][currentPt.x] = board[prevPt.y][prevPt.x];
        currentPt = prevPt;
    }
    checkPt = getNextPoint(checkPt, moveDir);
}

Direction GipfGame::checkValidExtPos(Point& startP, Point& endP) const {
    if (abs(startP.x - endP.x) == 3 && abs(startP.y - endP.y) == 0) {
        return RIGHT;
    }
    if ((startP.x - endP.x == 3 && startP.y - endP.y == 3) || (startP.x - endP.x == -3 && startP.y - endP.y == -3)) {
        return UPLEFT;
    }
    if ((startP.x - endP.x == -3 && startP.y - endP.y == 3) || (startP.x - endP.x == 3 && startP.y - endP.y == -3)) {
        return DOWNLEFT;
    }
    if (abs(startP.x - endP.x) == 0 && abs(startP.y - endP.y) == 3) {
        return DOWNLEFT;
    }
    return UNKNOWN;
}

bool GipfGame::checkValidExtColor(Point& startP, char extColor) const {
    if (board[startP.y][startP.x] + 32 != extColor) {
        return true;
    }
    return false;
}

void GipfGame::UserMove(char pos1CH, char pos2CH, int pos1IN, int pos2IN, int extPos1INT, char extPos1CH, int extPos2INT, char extPos2CH, char extColor) {
    if (checkValidMove(pos1CH, pos1IN)) {
        std::cout << "BAD_MOVE_" << pos1CH << pos1IN << "_IS_WRONG_INDEX" << std::endl;
        wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
        gameState = 5;
        return;
    }
    if (checkValidMove(pos2CH, pos2IN)) {
        std::cout << "BAD_MOVE_" << pos2CH << pos2IN << "_IS_WRONG_INDEX" << std::endl;
        wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
        gameState = 5;
        return;
    }
    Direction moveDir = getDir(pos1CH, pos2CH, pos1IN, pos2IN);
    if (moveDir == UNKNOWN) {
        std::cout << "UNKNOWN_MOVE_DIRECTION" << std::endl;
        wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
        gameState = 5;
        return;
    }
    if (checkStartFiled(pos1CH, pos1IN)) {
        std::cout << "BAD_MOVE_" << pos1CH << pos1IN << "_IS_WRONG_STARTING_FIELD" << std::endl;
        wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
        gameState = 5;
        return;
    }
    if (!checkStartFiled(pos2CH, pos2IN)) {
        std::cout << "BAD_MOVE_" << pos2CH << pos2IN << "_IS_WRONG_DESTINATION_FIELD" << std::endl;
        wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
        gameState = 5;
        return;
    }

    Point strPt = getStartPoint(pos2CH, pos2IN);
    Point newPt = getNextPoint(strPt, moveDir);
    if (board[strPt.y][strPt.x] != 'W' && board[strPt.y][strPt.x] != 'B') {
        makeMove(strPt);
    }
    else {
        Point checkPt = lineFull(moveDir, strPt);
        if (checkPt.x == -1 || checkPt.y == -1) {
            std::cout << "BAD_MOVE_ROW_IS_FULL " << std::endl;
            wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
            gameState = 5;
            return;
        }
        pushPawns(moveDir, strPt, checkPt);
        makeMove(strPt);
    }

    if (extPos1INT != -1 && extPos2INT != -1) {
        Point startP = getStartPoint(extPos1CH, extPos1INT);
        Point endP = getStartPoint(extPos2CH, extPos2INT);
        Direction extDir = checkValidExtPos(startP, endP);

        if (extDir == UNKNOWN) {
            std::cout << "WRONG_INDEX_OF_CHOSEN_ROW" << std::endl;
            wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
            gameState = 5;
            return;
        }
        if (checkValidExtColor(startP, extColor)) {
            std::cout << "WRONG_COLOR_OF_CHOSEN_ROW" << std::endl;
            wrongMove = WrongMove{ currentPlayer, pos1CH, pos2CH, pos1IN, pos2IN };
            gameState = 5;
            return;
        }
        checkPawnsStatus('X', startP, endP, extDir);
    }
    else {
        checkPawnsStatus('Q');
    }

    std::cout << "MOVE_COMMITTED" << std::endl;
}

void GipfGame::printGameState() const
{
    switch (gameState) {
    case 0:
        std::cout << "wrong_board_loaded" << std::endl;
        break;
    case 1:
        std::cout << "in_progress" << std::endl;
        break;
    case 2:
        std::cout << "white_win" << std::endl;
        break;
    case 3:
        std::cout << "black_win" << std::endl;
        break;
    case 4:
        std::cout << "dead_lock <kolor>" << std::endl;
        break;
    case 5:
        std::cout << "bad_move <";
        if (wrongMove.currentPlayer == 'W') {
            std::cout << "white> <";
        }
        else {
            std::cout << "black> <";
        }
        std::cout << wrongMove.pos1CH << wrongMove.pos1IN << " - " << wrongMove.pos2CH << wrongMove.pos2IN << ">" << std::endl;
        break;
    }
}

GipfGame::~GipfGame() {
    if (board) {
        for (int i = 0; i < 2 * boardSize - 1; i++) {
            delete[] board[i];
        }
        delete[] board;
    }
}