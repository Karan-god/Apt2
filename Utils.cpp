#include "Utils.h"
#include "TileCodes.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"

#include <string>
#include <vector>
#include <iostream>

Shape extractShape(std::string tile) {
    return stoi(tile.substr(1, 1));
}

Colour extractColour(std::string tile) {
    return *tile.substr(0, 1).c_str();
}

int extractX(std::string location) {
    int locationX = 0;
    if (location.length() == 2){
         locationX = stoi(location.substr(1, 1));
      } else if (location.length() == 3){
         locationX = stoi(location.substr(1, 2));
      }
    return locationX;
}

int extractY(std::string location) {
    int locationY = NOT_VALID_VALUE;
    char charLocationY = *location.substr(0, 1).c_str();
    if (charLocationY>= 'A' && charLocationY<='Z') {
        locationY = int(charLocationY) - 65;
    }
    return locationY;
}

bool checkTileFormat(std::string tile) {

    bool correctFormat = false;
    if (tile.length() == 2) {
        Shape tileShape = extractShape(tile);
        Colour tileColour = extractColour(tile);  

        

        bool shapeFormat = false;
        if (tileShape >=TILESHAPE_MIN and tileShape<=TILESHAPE_MAX) {
            shapeFormat = true;
        }

        bool colourFormat = false;
        for (int i = 0; i< NUMBER_OF_COLOUR; i++) {
            if (tileColour == colour[i]) {
                colourFormat = true;
            }
        }

        if (shapeFormat && colourFormat) {            
            correctFormat = true;
        };
    }
    
    return correctFormat;
}

bool checkLocationFormat(std::string location) {
    bool correctFormat = false;    
    int locationX = extractX(location);
    if (location.length() == 2){
         locationX = stoi(location.substr(1, 1));
      } else if (location.length() == 3){
         locationX = stoi(location.substr(1, 2));
      }

    char charLocationY = *location.substr(0, 1).c_str();

    if (charLocationY>='A' && charLocationY<='Z' && locationX >= 0 && locationX <= 25) {
        correctFormat = true;        
    }

    return correctFormat;
}

std::string printScoreBoard(std::vector<Player*> players) {
    std::string result = "";
    for (Player* player:players) {
        result = result + "Score for " + player->getName() + ": " + std::to_string(player->getScore()) + "\n";
    }
    result = result + "\n";
    return result;
}

std::string printBoard(Board* board) {
    std::string result = "";
    result = result + "   ";
    for (int i=0; i<board->getRows(); i++){
        if (i < 10){
            result = result + std::to_string(i) + "  ";
        } else {
        result = result + std::to_string(i) + " ";
        }      
   }
   result = result + "\n";
   result = result + "  -";
   for (int i=0; i<board->getRows(); i++){
      result = result + "---";
   }
   result = result + "\n";
         
   for (int i=0; i<board->getRows(); i++){
        char row = 'A' + i;
        result = result + row;
        result +=  + " |";

        for (int j=0; j<board->getCols(); j++){
            Tile tempTile = board->getTile(i,j);
            Colour tempColour = tempTile.getColour();
            Shape tempShape = tempTile.getShape();

            if (tempColour == DEFAULTCOLOUR && tempShape == DEFAULTSHAPE){
                result = result + "  ";
            } else {
                result = result + tempColour + std::to_string(tempShape);
            }

            result = result + "|";
        }
        result = result + "\n";
   }
   result = result + "\n";
   return result;
}

std::string printPlayerHand(Player* player) {
    std::string result = "";
    result = result + "Your hand is\n";
    for (int i=0; i<player->getHand()->size(); i++){
        result = result + player->getHand()->get(i)->getColour() + std::to_string(player->getHand()->get(i)->getShape());        
        if (i != player->getHand()->size()-1){
            result = result + ",";
        }
      }
    result = result + "\n\n";
    return result;
}

std::string saveGameString(LinkedList* tileBag, std::vector<Player*> players, Board* board) {
    std::string result = "";
    for (Player* player:players) {
        result= result + player->getName() + "\n"; 
        result = result + std::to_string(player->getScore()) + "\n";
        for (int i=0; i<player->getHand()->size(); i++){
               result = result + player->getHand()->get(i)->getColour();
               result += std::to_string(player->getHand()->get(i)->getShape());
               if (i != player->getHand()->size()-1){
                  result = result + ",";
               }
            }
        result = result + "\n";
    }
            
    result = result + std::to_string(board->getRows()) + "," + std::to_string(board->getCols()) + "\n";
    result = result + "\n";

    bool firstTile = true;
            
    
           
    for (int i=0; i<board->getRows(); i++){
        for (int j=0; j<board->getCols(); j++){
            Tile tempTile = board->getTile(i,j);
            Colour tempColour = tempTile.getColour();
            Shape tempShape = tempTile.getShape();                        
            char locationY = char('A' + i);
            
            if (!(tempColour == DEFAULTCOLOUR && tempShape == DEFAULTSHAPE)){    
                if (firstTile){
                    firstTile = false;
                }
                else {                    
                    result = result + ", ";
                }

                result = result + tempColour + std::to_string(tempShape) + "@" + std::string(1, locationY) + std::to_string(j);

                
            }
        }
    }

    result = result + "\n";

    for (int i=0; i<tileBag->size(); i++){
        result = result + tileBag->get(i)->getColour() + std::to_string(tileBag->get(i)->getShape());
        if (i != tileBag->size()-1){
            result = result + ",";
        }
    }
    result = result + "\n";

    result = result + players.at(FIRST_PLAYER-1)->getName();
    return result;
}

std::string printGameOver(std::vector<Player*> players) {
    std::string result = "";
    result = result + "\n" + "Game Over" + "\n";

    for (Player* player:players) {
        result = result + "Score for " + player->getName() + ": " + std::to_string(player->getScore()) + "\n";
    }
    
    int draw = 0;
    int highestScore = -1;
    std::string winPlayer = "";

    for (Player* player:players) {
        if (player->getScore() > highestScore) {
            highestScore = player->getScore();
            winPlayer = player->getName();
            draw = 1;
        }
        else if (player->getScore() == highestScore) {            
            draw += 1;
        }
    }

    if (draw>1) {
        result = result + "Draw!" + "\n";
        
    } 
    else {
        result = result + "Player " + winPlayer + " won!" + "\n";
    }
    
    return result;
}

bool checkPlayerNames(std::string playername, std::vector<Player*> players){

   if (playername.length() == 0){
      return false;
   }

   for (int i = 0; (unsigned)i < playername.length(); i++) {
      if (!(playername[i] >= 'A' && playername[i] <= 'Z')){
         return false;
      }
   }

   for (Player* p:players) {
      if (p->getName() == playername) {
         return false;
      }
   }

   return true;
}