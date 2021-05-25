#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include "Tile.h"
#include <string>

class Player {
    public:
        Player();
        ~Player();

        // initiate 
        Player(LinkedList* tileBag, std::string name);

        // set player score
        void setScore(int score);

        // set player name
        void setName(std::string);

        // set player hand
        void setHand(std::string newHand);

        // return player score
        int getScore();

        // return player name
        std::string getName();

        // return player hand
        LinkedList* getHand();

        // check if a tile is in the player hand
        bool search(Colour colour, Shape shape);

    private:
        LinkedList* hand;
        std::string name;
        int score;
};
#endif // ASSIGN2_TILE_H