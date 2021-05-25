#include "Tile.h"
#include "Player.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


LinkedList::LinkedList(){
    head = nullptr;
}

LinkedList::LinkedList(LinkedList& other){
    head = nullptr;
    for(int i = 0; i < other.size(); i++){
        add_back(new Tile(other.get(i)->getColour(), other.get(i)->getShape()));
    }
}

LinkedList::~LinkedList(){
    clear();
}

int LinkedList::size(){
    
    int counter = 0;

    Tile* current = head;
    while(current != nullptr){
        counter++;
        current = current->getNext();
    }
    return counter;
}

Tile* LinkedList::get(int index){
    Tile* returnTile = nullptr;

    if(index >= 0 && index < size()){

        int counter = 0;
        Tile* current = head;

        while(counter < index){
            counter++;
            current = current->getNext();
        }

        returnTile = current;

    }
    return returnTile;
}

void LinkedList::add_back(Tile* tile){

    if(head == nullptr) {
        head = new Tile(tile->getColour(), tile->getShape());
    } else {
        Tile* current = head;
        while(current->getNext() != nullptr){
            current = current->getNext();
        }
    
        current->setNext(new Tile(tile->getColour(), tile->getShape()));
    }

}

void LinkedList::remove(int index){
    
    int counter = 0;
    Tile* current = head;
    Tile* prev = nullptr;

    while (counter != index){
        counter++;
        prev = current;
        current = current->getNext();
    }

    if (prev == nullptr){
        head = current->getNext();
    } else {
        prev->setNext(current->getNext());
    }
    
    delete current;

}

void LinkedList::remove(Tile tile){
    
    Tile* current = head;
    Tile* prev = nullptr;

    while (!(tile.getColour() == current->getColour() && tile.getShape() == current->getShape())){
        prev = current;
        current = current->getNext();
    }

    if (prev == nullptr){
        head = current->getNext();
    } else {
        prev->setNext(current->getNext());
    }

    delete current;
}

void LinkedList::clear(){
    while(head != nullptr){
        remove(0);
    }
}

void LinkedList::shuffle() {
    LinkedList* tempList = new LinkedList();
    int bagSize = size();
    
    for (int i=0; i<bagSize; i++) {
        
        srand(time(NULL));
        int randomTile = rand() % size();
        Tile* tempTile = get(randomTile);
        tempList->add_back(tempTile);
        remove(randomTile);
        
    }

    this->clear();
    
    for (int i=0; i<bagSize; i++) {
        this->add_back(tempList->get(i));
    }

    tempList->clear();
    delete tempList;
}

bool LinkedList::search(Colour colour, Shape shape) {

    bool found = false;

    Tile* current = head;
    while(current != nullptr && !found) {        
        if (current->getColour() == colour && current->getShape() == shape) {            
            found = true;            
        }
        current = current->getNext();
    }

    return found;
}