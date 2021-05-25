#ifndef ASSIGN1_UTILS_H
#define ASSIGN1_UTILS_H

#include <string>
#include <vector>
#include "Player.h"
#include "Board.h"

#define NUMBER_OF_COLOUR 6
#define TILESHAPE_MIN 1
#define TILESHAPE_MAX 6

const char colour[6] = {'R', 'O', 'Y', 'G', 'B', 'P'};

// check if tile format is correct
bool checkTileFormat(std::string tile);

// check if location format is correct
bool checkLocationFormat(std::string location);

// get shape from tile string
Shape extractShape(std::string tile);

// get colour from tile string
Colour extractColour(std::string tile);

// get X from position
int extractX(std::string position);

// get Y from position
int extractY(std::string position);

// check player name is correct format and no duplicate
bool checkPlayerNames(std::string playername, std::vector<Player*> players);

// print score board after game over
std::string printScoreBoard(std::vector<Player*> players);

// Prints the current state of the board
std::string printBoard(Board* board);

// Print player hands
std::string printPlayerHand(Player* player);

std::string saveGameString(LinkedList* tileBag, std::vector<Player*> players, Board* board);

// Prints player scores and winner of the game
std::string printGameOver(std::vector<Player*> players);
#endif // ASSIGN1_UTILS_H
