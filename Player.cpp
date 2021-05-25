#include "Player.h"
#include <iostream>
#include <string>


Player::Player(LinkedList* tileBag, std::string name) {
    hand = new LinkedList();
    this->name = name;
    score = 0;

    for (int i = 0; i < 6; i++) {
        hand->add_back(tileBag->get(0));
        tileBag->remove(0);       
    }
}

Player::~Player() {
    delete hand;
}

Player::Player(){
    hand = new LinkedList();
    name = "";
    score = 0;
}

int Player::getScore(){
    return score;
}

void Player::setScore(int score){
    this->score = score;
}

std::string Player::getName(){
    return name;
}

void Player::setName(std::string name){
    this->name = name;
}

LinkedList* Player::getHand(){
    return hand;
}

void Player::setHand(std::string newHand){
    unsigned int letterCount = 0;
    bool endReached = false;
    while (!endReached){
        Shape tileShape = stoi(newHand.substr(letterCount+1, 1));
        Colour tileColour = *newHand.substr(letterCount, 1).c_str();  
        Tile* temp = new Tile(tileColour, tileShape);
        hand->add_back(temp);
        delete temp;
        letterCount = letterCount + 3;
        if (letterCount >= newHand.length()){
            endReached = true;
        }
    }
}

bool Player::search(Colour colour, Shape shape) {
    return hand->search(colour, shape);
}