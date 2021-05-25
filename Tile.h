
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:

   Colour colour;
   Shape  shape;
   Tile* next;
   
   // initiate tile with colour and shape
   Tile(Colour colour, Shape shape);

   // initiate tile with default colour and shape
   Tile();

   // get colour of tile
   Colour getColour();

   // get shape of tile
   Shape getShape();

   // tile to string to print
   std::string toString();

   // return pointer to next tile in linked list
   Tile* getNext();

   // set next tile
   void setNext(Tile* next);

   
};

#endif // ASSIGN2_TILE_H
