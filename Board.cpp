#include "Board.h"
#include <vector>

Board::Board() {
    cols = BOARD_DIMENSION;    
    rows = 0;
    for (int i = 0; i<BOARD_DIMENSION; i++) {
        addRow(i);
    }
}

Board::~Board() {
    board.clear();
}

void Board::addRow(int row){
    std::vector<Tile> tempVec;
    for (int i=0; i<cols; i++) {
        tempVec.push_back(Tile());
    }
    board.insert(board.begin() + row, tempVec);
    rows += 1;
}
void Board::addCol(int col){
    for (int i=0; i<rows; i++) {
        board.at(i).insert(board.at(i).begin() + col, Tile());
    }
    cols += 1;
}

void Board::placeTile(Tile tile, int row, int col){
    board.at(row).at(col).colour = tile.colour;
    board.at(row).at(col).shape = tile.shape;
}

Tile Board::getTile(int row, int col){
    return board.at(row).at(col);
}

int Board::getRows(){
    return rows;
}

int Board::getCols(){
    return cols;
}
