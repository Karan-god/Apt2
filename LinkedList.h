#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Tile.h"

class LinkedList{
   public:
      LinkedList();
      LinkedList(LinkedList& other);
      ~LinkedList();

      // return size of the Linked List
      int size();

      // return the tile at index
      Tile* get(int index);
      
      // add tile to the back of the linked list
      void add_back(Tile* tile);

      // remove tile at index
      void remove(int index);

      // find and remove the specific tile in linkedlist
      void remove(Tile tile);

      // clear all tiles in linked list
      void clear();

      // shuffle tiles in the linked list
      void shuffle();

      // check if a tile is in the linked list
      bool search(Colour colour, Shape shape);

   private:

      // head of the linked list
      Tile* head;
      
};


#endif //LINKEDLIST