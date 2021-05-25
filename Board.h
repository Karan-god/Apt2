
#ifndef ASSIGN2_BOARD_H

#define ASSIGN2_BOARD_H

#include <vector>
#include <string>

#include "Tile.h"

class Board {
public:
    Board();
    ~Board();

    // add new Row to the board
    void addRow(int row);

    // add new column to the board
    void addCol(int col);

    // place a tile at row, col
    void placeTile(Tile tile, int row, int col);

    // return the tile at row, col
    Tile getTile(int row, int col);

    // return the row count of the board
    int getRows();

    // return hte col count of the board
    int getCols();

private:

    // the board itself
    std::vector<std::vector<Tile>> board;

    // number of rows
    int rows;

    // number of cols
    int cols;

    // current fixed board dimension
    #define BOARD_DIMENSION 26

};

#endif // ASSIGN2_NODE_H
