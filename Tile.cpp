#include "Tile.h"
#include "TileCodes.h"
#include <string>

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
    this->next = nullptr;
}

Tile::Tile() {
    this->colour = DEFAULTCOLOUR;
    this->shape = DEFAULTSHAPE;
    this->next = nullptr;
}

Colour Tile::getColour(){
    return colour;
}

Shape Tile::getShape(){
    return shape;
}

std::string Tile::toString() {
    return std::to_string(colour) + std::to_string(shape);
}

Tile* Tile::getNext(){
    return next;
}

void Tile::setNext(Tile* next){
    this->next = next;
}
