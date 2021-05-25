#include "LinkedList.h"
#include "TileCodes.h"
#include "Player.h"
#include "Board.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define EXIT_SUCCESS    0

// Places a tile on the board
bool placeTile(std::string tile, std::string location, Player* player, LinkedList* tileBag, Board* board){
   
   bool correctFormat = false;
   bool emptyPosition = false;
   Shape tileShape;
   Colour tileColour;
   
   int locationY = 0;
   int locationX = 0;

   // Check that tile and location syntax is correct, check that tile is in player's hand, and check that location is empty on board
   if (tile.length() == 2 && (location.length() == 2 || location.length() == 3)){

      if (checkTileFormat(tile) && checkLocationFormat(location)) {
         tileShape = extractShape(tile);
         tileColour = extractColour(tile);
         locationX = extractX(location);
         locationY = extractY(location);

         if (board->getTile(locationY, locationX).getColour() == DEFAULTCOLOUR && board->getTile(locationY, locationX).getShape() == DEFAULTSHAPE) {
            emptyPosition = true;
         }

         if (player->search(tileColour, tileShape) && emptyPosition) {
            
            correctFormat = true;
         }         
      }
      
   }

   if (correctFormat){      
      Tile temp = Tile(tileColour, tileShape);
      Tile temp2;
      bool invalidNeighbour = false;
      bool endOfLine = false;
      bool rowRuleColour = false;
      bool rowRuleShape = false;
      bool colRuleColour = false;
      bool colRuleShape = false;
      Colour columnColour = DEFAULTCOLOUR;
      Colour rowColour = DEFAULTCOLOUR;
      Shape columnShape = DEFAULTSHAPE;
      Shape rowShape = DEFAULTSHAPE;
      int score = 0;
      int countUp = 1;
      int countDown = 1;
      int countRight = 1;
      int countLeft = 1;
      int neighbourCount = 0;
      int blankNeighbourCount = 0;

      bool firstTile = true;
      for (int i=0; i<board->getRows(); i++){
         for (int j=0; j<board->getCols(); j++){
            if (board->getTile(i,j).getColour() != DEFAULTCOLOUR || board->getTile(i,j).getShape() != DEFAULTSHAPE) {
               firstTile = false;
            }
         }
      }
   
      // If first tile has not been placed, place the tile, update the player score and refill the hand
      // If first tile has been placed, confirm that the tile we are placing meets the rules of qwirkle, 
      // then place the tile, then update the player score and refill the hand
      if (!firstTile){

         if (locationY != 0){

            neighbourCount++;
            temp2 = board->getTile(locationY-1,locationX);
            if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
               blankNeighbourCount++;
            }

            endOfLine = false;
            while(!invalidNeighbour && !endOfLine && locationY-countUp >= 0){
               temp2 = board->getTile(locationY-countUp,locationX);
              
              if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
                 endOfLine = true;
               } else if (((temp2.getColour() == temp.getColour() && temp2.getShape() == temp.getShape())) || 
                           (temp2.getColour() != temp.getColour() && temp2.getShape() != temp.getShape()) || 
                           (colRuleColour && temp2.getColour() != columnColour) || 
                           (colRuleShape && temp2.getShape() != columnShape)){
                  invalidNeighbour = true;
               } else if (temp2.getColour() == temp.getColour() && !colRuleColour && !colRuleShape){
                  columnColour = temp2.getColour();
                  colRuleColour = true;
               } else if (temp2.getShape() == temp.getShape() && !colRuleColour && !colRuleShape){
                  columnShape = temp2.getShape();
                  colRuleShape = true;
               } 

               if (!invalidNeighbour && !endOfLine){
                  countUp++;
               }
            }
         } 

         if (locationY != 25){

            neighbourCount++;
            temp2 = board->getTile(locationY+1,locationX);
            if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
               blankNeighbourCount++;
            }
            
            endOfLine = false;
            while(!invalidNeighbour && !endOfLine && locationY+countDown <= 25){
               temp2 = board->getTile(locationY+countDown, locationX);
               
               if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
                 endOfLine = true;
               } else if (((temp2.getColour() == temp.getColour() && temp2.getShape() == temp.getShape())) || 
                           (temp2.getColour() != temp.getColour() && temp2.getShape() != temp.getShape()) || 
                           (colRuleColour && temp2.getColour() != columnColour) || 
                           (colRuleShape && temp2.getShape() != columnShape)){
                  invalidNeighbour = true;
               } else if (temp2.getColour() == temp.getColour() && !colRuleColour && !colRuleShape){
                  columnColour = temp2.getColour();
                  colRuleColour = true;
               } else if (temp2.getShape() == temp.getShape() && !colRuleColour && !colRuleShape){
                  columnShape = temp2.getShape();
                  colRuleShape = true;
               } 

               if (!invalidNeighbour && !endOfLine){
                  countDown++;
               }
            }
         }

         if (locationX != 0){

            neighbourCount++;
            temp2 = board->getTile(locationY, locationX+1);
            if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
               blankNeighbourCount++;
            }

            endOfLine = false;
            while(!invalidNeighbour && !endOfLine && locationX+countRight <= 25){
               temp2 = board->getTile(locationY,locationX+countRight);

               if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
                 endOfLine = true;
               } else if (((temp2.getColour() == temp.getColour() && temp2.getShape() == temp.getShape())) || 
                           (temp2.getColour() != temp.getColour() && temp2.getShape() != temp.getShape()) || 
                           (rowRuleColour && temp2.getColour() != rowColour) || 
                           (rowRuleShape && temp2.getShape() != rowShape)){
                  invalidNeighbour = true;
               } else if (temp2.getColour() == temp.getColour() && !rowRuleColour && !rowRuleShape){
                  rowColour = temp2.getColour();
                  rowRuleColour = true;
               } else if (temp2.getShape() == temp.getShape() && !rowRuleColour && !rowRuleShape){
                  rowShape = temp2.getShape();
                  rowRuleShape = true;
               } 
               
               if (!invalidNeighbour && !endOfLine){
                  countRight++;
               }
            }
         } 

         if (locationX != 25){

            neighbourCount++;
            temp2 = board->getTile(locationY, locationX-1);
            if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
               blankNeighbourCount++;
            }
            
            endOfLine = false;
            while(!invalidNeighbour && !endOfLine && locationX-countLeft >= 0){
               temp2 = board->getTile(locationY, locationX-countLeft);

               if (temp2.getColour() == DEFAULTCOLOUR && temp2.getShape() == DEFAULTSHAPE){
                 endOfLine = true;
               } else if (((temp2.getColour() == temp.getColour() && temp2.getShape() == temp.getShape())) || 
                           (temp2.getColour() != temp.getColour() && temp2.getShape() != temp.getShape()) || 
                           (rowRuleColour && temp2.getColour() != rowColour) || 
                           (rowRuleShape && temp2.getShape() != rowShape)){
                  invalidNeighbour = true;
               } else if (temp2.getColour() == temp.getColour() && !rowRuleColour && !rowRuleShape){
                  rowColour = temp2.getColour();
                  rowRuleColour = true;
               } else if (temp2.getShape() == temp.getShape() && !rowRuleColour && !rowRuleShape){
                  rowShape = temp2.getShape();
                  rowRuleShape = true;
               } 

               if (!invalidNeighbour && !endOfLine){
                  countLeft++;
               }
            }       
         }

         if (neighbourCount == blankNeighbourCount){
            invalidNeighbour = true;
         }

         if (!invalidNeighbour){
            board->placeTile(temp, locationY, locationX);
            
            if (countUp == 6 || countDown == 6 || countUp+countDown-1 == 6){
               score = score + 12;
               std::cout << std::endl << "QWIRKLE!!!" << std::endl << std::endl;
            } else if (countUp == 1 && countDown != 1){
               score = score + countDown;
            } else if (countUp != 1 && countDown == 1){
               score = score + countUp;
            } else if (!(countUp == 1 && countDown == 1)){
               score = score + countUp + countDown - 1;
            }

            if (countRight == 6 || countLeft == 6 || countRight+countLeft-1 == 6){
               score = score + 12;
               std::cout << std::endl << "QWIRKLE!!!" << std::endl << std::endl;
            } else if (countRight == 1 && countLeft != 1){
               score = score + countLeft;
            } else if (countRight != 1 && countLeft == 1){
               score = score + countRight;
            } else if (!(countRight == 1 && countLeft == 1)){
               score = score + countRight + countLeft - 1;
            }

            player->setScore(player->getScore() + score);

            player->getHand()->remove(temp);
            if (tileBag->size() != 0){
               player->getHand()->add_back(tileBag->get(0));
               tileBag->remove(0);
            }

            return true;
         }

      } else {
         board->placeTile(temp, locationY, locationX);
         score++;
         player->setScore(player->getScore() + score);
         player->getHand()->remove(temp);
         player->getHand()->add_back(tileBag->get(0));
         tileBag->remove(0);

         firstTile = false;
         return true;
      }

   
   }

   return false;
}

// Replaces a tile in the current player's hand
bool replaceTile(std::string tile, Player* player, LinkedList* tileBag){

   if (tileBag->size() != 0){

      bool correctFormat = false;
      Shape tileShape;
      Colour tileColour;

      // Check that the tile syntax is correct and exists in the hand
      if (tile.length() == 2 && checkTileFormat(tile)){

         tileShape = extractShape(tile);
         tileColour = extractColour(tile);  

         if (player->getHand()->search(tileColour, tileShape)) {
            correctFormat = true;
         }
      }
      
      // If correct, swap the tile in hand for a tile in the bag
      if (correctFormat){

         Tile* temp = new Tile(tileColour, tileShape);
         player->getHand()->remove(*temp);
         tileBag->add_back(temp);
         player->getHand()->add_back(tileBag->get(0));
         tileBag->remove(0);
         
         return true;
      }
   }

   return false;
}

// Defines the player names 
std::string enterPlayerNames(int playernumber, std::vector<Player*> players){

   std::cout << "-------------------------" << std::endl;
   std::cout << "Enter a name for player " << playernumber + 1 << std::endl;

   std::string player;
   bool legalName = false;
   std::cout << "> ";
   while (!legalName && std::getline(std::cin, player)){
      std::cout<< player << std::endl;
      for(char& c : player) {
         c = toupper(c);
      }

      if (!checkPlayerNames(player, players)){
         std::cout << "Invalid name, try again" << std::endl << "> ";
      } else {
         legalName = true;
      }
   }

   return player;
}

// Begins main gameplay logic for taking turns between players and other player commands
bool beginGame(std::vector<Player*> players, LinkedList* tileBag, Board* board, int firstPlayer) {
   
   bool gameOver = false;
   int currentPlayer = firstPlayer - 1;
   while(!gameOver) {

      std::cout << std::endl << players.at(currentPlayer)->getName() << ", it's your turn" << std::endl;

      std::cout<<printScoreBoard(players);
      std::cout<<printBoard(board);
      std::cout<<printPlayerHand(players.at(currentPlayer));      

      std::cout << "To place tile - 'place G3 at B1'" << std::endl;
      std::cout << "To replace tile - 'replace G3'" << std::endl;
      std::cout << "To save game - 'save filename'" << std::endl;
      std::cout << "To quit game - 'quit'" << std::endl;

      bool placeTileSuccessful = false;
      bool replaceTileSuccessful = false;

      std::string playerInput;
      std::cout << "> ";
      // Waits for player input to place a tile, replace a tile, save the game, or quit
      while (!placeTileSuccessful && !replaceTileSuccessful && std::getline(std::cin, playerInput)){
         std::cout << playerInput << std::endl;         
         if ((playerInput.length() == 14 || playerInput.length() == 15) && playerInput.substr(0, 6) == "place " && playerInput.substr(8, 4) == " at "){
            
            std::string location;
            if (playerInput.length() == 14){
               location = playerInput.substr(12, 2);
            } else if (playerInput.length() == 15){
               location = playerInput.substr(12, 3);
            }
            placeTileSuccessful = placeTile(playerInput.substr(6, 2), location, players.at(currentPlayer), tileBag, board);

            if (!placeTileSuccessful){
               std::cout << "Invalid input, try again" << std::endl << "> ";
            }

         } else if (playerInput.length() == 10 && playerInput.substr(0, 8) == "replace "){

            replaceTileSuccessful = replaceTile(playerInput.substr(8, playerInput.size()-8), players.at(currentPlayer), tileBag);

            if (!replaceTileSuccessful){
               std::cout << "Invalid input, try again" << std::endl << "> ";
            }

         } else if (playerInput.substr(0, 5) == "save "){

            std::string fileName = playerInput.substr(5, playerInput.size()-5);
            std::string fileNameTXT = fileName + ".txt";
            std::ofstream myFile;
            myFile.open(fileNameTXT, std::ios::trunc);

            myFile << saveGameString(tileBag, players, board);

            myFile.close();

            std::cout << std::endl << "Game successfully saved" << std::endl << std::endl << "> ";

         } else if (playerInput == "quit"){
            gameOver = true;
            placeTileSuccessful = true;
         } else {
            std::cout << "Invalid input, try again" << std::endl << "> ";
         }
      }

      for (Player* player:players) {
         
         if (player->getHand()->size() == 0) {
            player->setScore(player->getScore() + 6);
            std::cout << printGameOver(players);
            gameOver = true;
         }
            
      }

      if (std::cin.eof()){
         gameOver = true;
      } 
      else {
         // Changes the current player at the end of each turn and checks if the game should end       
         currentPlayer = (currentPlayer + 1) % NUMBER_PLAYER;         
      }
   }
   return true;

}

int main(void) {
   
   std::vector<Player *> players;

   //init board
   Board* board = new Board();

   bool exit = false;
   std::cout << "-------------------" << std::endl;
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << "Menu" << std::endl;
   std::cout << "---" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits" << std::endl;
   std::cout << "4. Quit" << std::endl;

   std::cout << "> ";
   std::string menuint;
   // Wait for user input at main menu
   while (!exit && std::getline(std::cin, menuint)){
      std::cout << menuint << std::endl;
      // Start a new game; initialise board, tilebag, players, and begin the game 
      if (menuint == "1") {

         //init tile bag
         LinkedList* tileBag = new LinkedList();
         for (int k=0; k<2; k++){
            for (int i=0; i<6; i++) {
               for (int j=0; j<TILESHAPE_MAX; j++) {
                  Tile* temp = new Tile(colour[i], j+1);
                  tileBag->add_back(temp);
                  delete temp;
               }
            }  
         }
         tileBag->shuffle();

         std::cout << "-------------------" << std::endl;
         std::cout << "Starting a New Game" << std::endl;

         //get player name and init player hand
         for (int i = 0; i<NUMBER_PLAYER; i++) {
            players.push_back(new Player(tileBag, enterPlayerNames(i, players)));
         }         

         //play the game
         if (!(std::cin.eof())){
            std::cout << "-----------" << std::endl;
            std::cout << "Let's Play!" << std::endl;
            std::cout << "-----------" << std::endl;
            
            exit = beginGame(players, tileBag, board, FIRST_PLAYER);
         }
         delete tileBag;

      // Load the file the player specifies and then resume the game
      } else if (menuint == "2"){
         std::cout << "---------------------------------------------" << std::endl;
         std::cout << "Enter the name of the file you want to load" << std::endl;

         std::cout << "> ";
         std::string fileName;
         std::getline(std::cin, fileName);         
         std::cout << fileName << std::endl;         

         int firstPlayer = 0;

         Player* player1 = new Player();
         Player* player2 = new Player();         
         LinkedList* tileBag = new LinkedList();
         
         bool load = false;

         std::string fileNameTXT = fileName + ".txt";
         std::ifstream myFile(fileNameTXT);
         std::string line;

         // Initialise board, tilebag and players based on contents of file
         if (myFile.is_open()) {
            
            int lineCount = 0;
            while (std::getline(myFile, line)) {

               if (lineCount == 0){
                  player1->setName(line);
                  lineCount++;
               } else if (lineCount == 1){
                  player1->setScore(stoi(line));
                  lineCount++;
               } else if (lineCount == 2){
                  player1->setHand(line);
                  lineCount++;
               } else if (lineCount == 3){
                  player2->setName(line);
                  lineCount++;
               } else if (lineCount == 4){
                  player2->setScore(stoi(line));
                  lineCount++;
               } else if (lineCount == 5){
                  player2->setHand(line);
                  lineCount++;
               } else if (lineCount == 6){
                  //int boardSizeX = std::stoi(line.substr(0, 2));
                  //int boardSizeY = std::stoi(line.substr(3, 2));                                    
                  lineCount++;

               } else if (lineCount == 7){
                  if (line.length() != 0){
                     unsigned int letterCount = 0;
                     bool endReached = false;
                     while (!endReached){
                        Shape tileShape = stoi(line.substr(letterCount+1, 1));
                        Colour tileColour = *line.substr(letterCount, 1).c_str(); 

                        char charLocationY = *line.substr(letterCount+3, 1).c_str();
                        int locationY = 0;
                        if (charLocationY >= 'A' && charLocationY <='Z'){
                           locationY = int(charLocationY) - 65;
                        }
                        

                        int locationX = 0; 
                        if (letterCount+4 == line.length()-1 || line.substr(letterCount+5, 1) == ","){
                           locationX = stoi(line.substr(letterCount+4, 1));
                           letterCount = letterCount + 7;
                        } else if (letterCount+5 == line.length()-1 || line.substr(letterCount+6, 1) == ","){
                           locationX = stoi(line.substr(letterCount+4, 2));
                           letterCount = letterCount + 8;
                        }                     

                        board->placeTile(*(new Tile(tileColour, tileShape)), locationY, locationX);
                        if (letterCount >= line.length()-1){
                           endReached = true;
                        }
                     }
                  }
                  lineCount++;
               } else if (lineCount == 8){
                  unsigned int letterCount = 0;
                  bool endReached = false;
                  while (!endReached){
                     Shape tileShape = stoi(line.substr(letterCount+1, 1));
                     Colour tileColour = *line.substr(letterCount, 1).c_str();
                     Tile* temp = new Tile(tileColour, tileShape);
                     tileBag->add_back(temp);
                     delete temp;
                     letterCount = letterCount + 3;
                     if (letterCount >= line.length()){
                        endReached = true;
                     }
                  } 
                  lineCount++;
               } else if (lineCount == 9){
                  if (player1->getName() == line){
                     firstPlayer = 1;
                  } else if (player2->getName() == line){
                     firstPlayer = 2;
                  }
               }
            }

            load = true;

         } 
         else {
            std::cout << "Unable to open file" << std::endl; 
         } 

         if (load){
            std::cout << std::endl << "Game successfully loaded" << std::endl;
            players.clear();
            players.push_back(player1);
            players.push_back(player2);            
            exit = beginGame(players, tileBag, board, firstPlayer);
         }
         delete tileBag;

      // Print credits
      } else if (menuint == "3"){
         std::cout << "-----------------------------------" << std::endl;
         std::cout << "Name: Nguyen Duc Phu" << std::endl;
         std::cout << "Student ID: s3516565" << std::endl;
         std::cout << "Email: s3516565@rmit.edu.vn" << std::endl << std::endl;
         std::cout << "Name: Amandeep Kaur Hothi" << std::endl;
         std::cout << "Student ID: s3838913" << std::endl;
         std::cout << "Email: s3838913@student.rmit.edu.au" << std::endl << std::endl;
         std::cout << "Name: Karan Pradhan" << std::endl;
         std::cout << "Student ID: s3814520" << std::endl;
         std::cout << "Email: s3814520@student.rmit.edu.au"<< std::endl << std::endl;
         std::cout << "Name: Rhys Puclin" << std::endl;
         std::cout << "Student ID: s3840068" << std::endl;
         std::cout << "Email: s3840068@student.rmit.edu.au" << std::endl;
         std::cout << "-----------------------------------" << std::endl;
         std::cout << "> ";
      
      // Leave main menu
      } else if (menuint == "4"){
         exit = true;
      } else {
         std::cout << "Invalid input, try again" << std::endl << "> ";
      }
   }

   std::cout << std::endl << "-------" << std::endl;
   std::cout << "GoodBye" << std::endl;
   std::cout << "-------" << std::endl;

   for (Player* p : players)
   {
      if (p!=nullptr) {
         delete p;
      }      
   } 
   players.clear();
   delete board;
}