#include <iostream>
#include <string>
#include "GipfGame.h"
#include "Solver.h"

void getInput(std::string line, std::pair<char, int>& pos1, std::pair<char, int>& pos2, int& i, char search) {
    std::string posNumb;
    pos1.first = line[i++];
    for (; i < line.size(); i++) {
        if (line[i] == search) {
            i++;
            break;
        }
        posNumb += line[i];
    }
    pos1.second = std::stoi(posNumb);
    pos2.first = line[i++];
    posNumb = "";
    for (; i < line.size(); i++) {
        if (line[i] == '\n' || line[i] == ' ')
            break;
        posNumb += line[i];
    }
    pos2.second = std::stoi(posNumb);
}

int main()
{
    GipfGame myGame;
    std::string opearteMenu;
    while (std::cin >> opearteMenu) {
        if (opearteMenu == "LOAD_GAME_BOARD") {
            myGame.loadBoard();
            std::cout << std::endl;
        }
        else if (opearteMenu == "PRINT_GAME_BOARD") {
            myGame.displayBoard();
        }
        else if (opearteMenu == "DO_MOVE") {
            std::string line;
            std::getline(std::cin, line);
            try {
                int i = 1;
                std::pair<char, int> pos1;
                std::pair<char, int> pos2;
                getInput(line, pos1, pos2, i, '-');

                if (line[i] == '\n' || line[i] == '\0') {
                    myGame.UserMove(pos1.first, pos2.first, pos1.second, pos2.second, -1, '\0', -1, '\n', '\n');
                }
                else if (line[i + 1] == 'w' || line[i + 1] == 'b') {
                    i++;
                    char pColor = line[i];
                    i += 3;
                    std::pair<char, int> delPos1;
                    std::pair<char, int> delPos2;
                    getInput(line, delPos1, delPos2, i, ' ');

                    myGame.UserMove(pos1.first, pos2.first, pos1.second, pos2.second, delPos1.second, delPos1.first, delPos2.second, delPos2.first, pColor);
                }
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Invalid input: " << e.what() << std::endl;
            }
        }
        else if (opearteMenu == "PRINT_GAME_STATE") {
            myGame.printGameState();
        }
        else if (opearteMenu == "EXIT_GAME") {
            return 0;
        }
    }
}