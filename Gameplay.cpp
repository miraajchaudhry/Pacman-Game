#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include <random>
#include <vector>
#include <chrono>

#include "Pacman.h"

Stats::Stats() {
    points = 0;
    lives = 3;
}

Stats::Stats(int newPts, int numGhosts, int lvs) {
    points = newPts;
    lives = lvs;
}

int Stats::getPoints() const {
    return points;
}

int Stats::getLives() const {
    return lives;
}

void Stats::increasePoints() {
    points += 10;
}

void Stats::decreaseLives() {
    lives -= 1;
}

std::ostream& operator<<(std::ostream& out, const Stats& rtObj) {
    out << "Points: " << rtObj.points << "\tLives: " << rtObj.lives << std::endl;

    return out;
}

Character::Character() {
    row = 0;
    column = 0;
}

Character::Character(int startingRow, int startingColumn) {
    row = startingRow;
    column = startingColumn;
}

int Character::getRow() const {
    return row;
}

int Character::getColumn() const {
    return column;
}

Gameplay::Gameplay() {
    gameStats = Stats();
    
    for (int r = 0; r < 11; r++) {
        for (int c = 0; c < 20; c++) {
            if ((c == 0 || c == 19) && r != 5)
                          maze[r][c] = '|';
            
            else if (r == 0 || r == 10)
                maze[r][c] = '-';
            
            else if ((r > 3 && r < 7) && (c == 5 || c == 7 || c == 12 || c == 14))
                maze[r][c] = '|';
            
            else if ((r == 2 || r == 8) && ((c > 1 && c < 6) || (c > 6 && c < 13) || (c > 13 && c < 18)))
                maze[r][c] = '-';
            
            else if (r == 6 && (c > 7 && c < 12))
                maze[r][c] = '-';
            
            else if (r == 5 && ((c > 1 && c < 5) || (c > 14 && c < 18)))
                maze[r][c] = '-';
            
            else if ((r == 3 || r == 7) && (c == 2 || c == 17))
                maze[r][c] = '|';
            
            else
                maze[r][c] = '*';
                
        }
    }
}

char Gameplay::getChar(int row, int column) {
    return maze[row][column];
}

void Gameplay::modifyMaze(int row, int column, char newChar) {
    maze[row][column] = newChar;
}

void Gameplay::loss() {
    std::string again;
    
    std::cout << "Game over: You're out of lives. Here are your stats: " << std::endl << gameStats << std::endl;
    
    std::cout << "Would you like to play again? ";
    //std::cin >> again;
    
        
}

void Gameplay::win() {
    std::cout << "Congratulations: You finished before running out of lives! Here are you stats:" << std::endl << gameStats << std::endl;
}

void Gameplay::increasePoints() {
    gameStats.increasePoints();
}

bool Gameplay::livesLeft() {
    if (gameStats.getLives() != 0)
        return true;
    
    return false;
}

void Gameplay::collisionOccurs(Pacman& pac, Ghost& g1, Ghost& g2, Ghost& g3, Ghost& g4) {
    pac.resetPacman(*this);
    g1.resetGhost(*this);
    g2.resetGhost(*this);
    g3.resetGhost(*this);
    g4.resetGhost(*this);
    
    gameStats.decreaseLives();
}

Stats Gameplay::getGameStats() const {
    return gameStats;
}

bool Gameplay::tokensLeft() {
    /*if (gameStats.getTokensLeft() > 0)
        return true;
    
    return false;*/
    
    for (int row = 0; row < 11; row++) {
        for (int column = 0; column < 20; column++) {
            if (maze[row][column] == '*')
                return true;
        }
    }
    
    return false;
}

Pacman::Pacman(Gameplay& game) : Character (5, 1) {
    game.modifyMaze(5, 1, 'P');
}

void Pacman::handleUserMove(GLFWwindow* window, PacmanGraphics& pac, Gameplay& game) {
    
    //cout << row << " " << column << endl;
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && checkMoveUp(game)) {
        moveUp(game, pac);
        //pac.moveUp();
    }
    
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && checkMoveDown(game)) {
        moveDown(game, pac);
        //pac.moveDown();
    }
    
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && checkMoveRight(game)) {
        moveRight(game, pac);
        //pac.moveRight();
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && checkMoveLeft(game)) {
        moveLeft(game, pac);
        //pac.moveLeft();
    }
    
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        exit(1);
    
 
}

bool Pacman::checkMoveLeft(Gameplay& game) {
    if (row == 5 && column == 0)
        return true;
    
    else if (((game.getChar(row, column - 1) != '|') && (game.getChar(row, column - 1) != '-')))
        return true;
    
    return false;
}

bool Pacman::checkMoveRight(Gameplay& game) {
    if (row == 5 && column == 19)
        return true;
    
    else if (((game.getChar(row, column + 1) != '|') && (game.getChar(row, column + 1) != '-')))
        return true;
    
    return false;
}

bool Pacman::checkMoveUp(Gameplay& game) {
    if ((game.getChar(row - 1, column) != '|') && (game.getChar(row - 1, column) != '-'))
        return true;
    
    return false;
}

bool Pacman::checkMoveDown(Gameplay& game) {
    if ((game.getChar(row + 1, column) != '|') && (game.getChar(row + 1, column) != '-'))
        return true;
    
    return false;
}

void Pacman::moveLeft(Gameplay& game, PacmanGraphics& pac) {
    if (column == 0 && row == 5) {
        column = 19;
        
        pac.swapSides();
        
        if (game.getChar(row, column) == '*')
            game.increasePoints();
        
        game.modifyMaze(row, column, 'P');
        game.modifyMaze(row, 0, ' ');
    }
    
    else {
        column -= 1;
        
        if (game.getChar(row, column) == '*')
            game.increasePoints();
           
        game.modifyMaze(row, column, 'P');
        game.modifyMaze(row, column + 1, ' ');
        
        pac.moveLeft();
    }
}


void Pacman::moveRight(Gameplay& game, PacmanGraphics& pac) {
    if (column == 19 && row == 5) {
        column = 0;
        
        if (game.getChar(row, column) == '*')
            game.increasePoints();
        
        game.modifyMaze(row, column, 'P');
        game.modifyMaze(row, 19, ' ');
        
        pac.swapSides();
    }
    
    else {
        column += 1;
        
        if (game.getChar(row, column) == '*')
            game.increasePoints();
        
        game.modifyMaze(row, column, 'P');
        game.modifyMaze(row, column - 1, ' ');
        
        pac.moveRight();
    }
}

void Pacman::moveUp(Gameplay& game, PacmanGraphics& pac) {
    row -= 1;
    
    if (game.getChar(row, column) == '*') 
        game.increasePoints();
    
    game.modifyMaze(row, column, 'P');
    game.modifyMaze(row + 1, column, ' ');
    
    pac.moveUp();
    
}

void Pacman::moveDown(Gameplay& game, PacmanGraphics& pac) {
    row += 1;
    
    if (game.getChar(row, column) == '*')
        game.increasePoints();
    
    game.modifyMaze(row, column, 'P');
    game.modifyMaze(row - 1, column, ' ');
    
    pac.moveDown();
}

void Pacman::resetPacman(Gameplay& game) {
    game.modifyMaze(row, column, ' ');
    game.modifyMaze(5, 1, 'P');
    row = 5;
    column = 1;
}

Ghost::Ghost(Gameplay& game, int num, std::string difficulty) : Character() {
    ghostNum = num;
    
    if (ghostNum == 1) {
        row = 5;
        column = 8;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 2) {
        row = 5;
        column = 9;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 3) {
        row = 5;
        column = 10;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 4) {
        row = 5;
        column = 11;
        game.modifyMaze(row, column, 'G');
    }
    
    if (difficulty == "easy")
        speed = "slow";
    
    if (difficulty == "medium")
        speed = "medium";
    
    if (difficulty == "hard" || difficulty == "impossible")
        speed = "fast";
    
    
    prevChar = '*';
    moves = {"Up", "Down", "Right", "Left"};
    
}

bool Ghost::GhostPen(Gameplay& game, GhostGraphics& gg) {
    if (row == 5 && (column == 8 || column == 9 || column == 10 || column == 11)) {
        game.modifyMaze(row, column, prevChar);
        row--;
        game.modifyMaze(row, column, 'G');
        gg.moveUp();
        return false;
    }
    
    else if (row == 4 && (column == 8 || column == 9 || column == 10 || column == 11)) {
        game.modifyMaze(row, column, prevChar);
        row--;
        prevChar = game.getChar(row, column);
        game.modifyMaze(row, column, 'G');
        gg.moveUp();
        return false;
    }
    
    else if (row == 3 && (column > 6 && column < 13)) {
        if (ghostNum == 1 || ghostNum == 3) {
            game.modifyMaze(row, column, prevChar);
            column--;
            prevChar = game.getChar(row, column);
            game.modifyMaze(row, column, 'G');
            gg.moveLeft();
            return false;
        }
        
        else {
            game.modifyMaze(row, column, prevChar);
            column++;
            prevChar = game.getChar(row, column);
            game.modifyMaze(row, column, 'G');
            gg.moveRight();
            return false;
        }
    }
    
    else if (row == 3 && (column == 6 || column == 13)) {
            game.modifyMaze(row, column, prevChar);
            if (ghostNum == 1 || ghostNum == 3)
                row--;
            if (ghostNum == 2 || ghostNum == 4)
                row++;
            prevChar = game.getChar(row, column);
            game.modifyMaze(row, column, 'G');
            if (ghostNum == 1 || ghostNum == 3)
                gg.moveUp();
            if (ghostNum == 2 || ghostNum == 4)
                gg.moveDown();
            
            return false;
    }

    else if ((row == 2 || row == 4) && (column == 6 || column == 13)) {
            game.modifyMaze(row, column, prevChar);
            if (ghostNum == 1 || ghostNum == 3)
                row--;
            if (ghostNum == 2 || ghostNum == 4)
                row++;
            prevChar = game.getChar(row, column);
            game.modifyMaze(row, column, 'G');
            if (ghostNum == 1 || ghostNum == 3)
                gg.moveUp();
            if (ghostNum == 2 || ghostNum == 4)
                gg.moveDown();
            
            return false;
    }
    return true;
}

bool Ghost::checkGhostMove(Gameplay& game, int row, int column) {
    if (game.getChar(row, column) == '|' || game.getChar(row, column) == '-' || game.getChar(row, column) == 'G')
        return false;
    
    return true;
}


void Ghost::setGhostsSpeed(int level) {
    if (level == 1)
        speed = "slow";
    
    else if (level == 2)
        speed = "medium";
    
    else if (level == 3)
        speed = "fast";
    
    else if (level == 4)
        speed = "impossible";
}

std::string Ghost::getGhostsSpeed() const {
    return speed;
}

int Ghost::getGhostNum() const {
    return ghostNum;
}

void Ghost::moveGhost(Gameplay& game, Pacman& pac, GhostGraphics& gg) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
    std::vector<std::string>::iterator vIt = moves.begin();
    
    if (speed == "slow")
        moveGhostEasy(game, *vIt, gg);
    
    else if (speed == "medium") {
        moveGhostMedium(game, pac, gg, *vIt);
    }
    
    else
        moveGhostHard(game, pac, gg);
}

void Ghost::moveGhostEasy(Gameplay& game, std::string move, GhostGraphics& gg) {
    if (move == "Up" && checkGhostMove(game, row - 1, column)) {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row - 1, column);
        game.modifyMaze(row - 1, column, 'G');
        
        row--;
        gg.moveUp();
    }
    
    else if (move == "Down" && checkGhostMove(game, row + 1, column)) {
        if (row == 3 && (column > 7 && column < 12)) {
            if (ghostNum == 1 || ghostNum == 2) {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
                
                column--;
                gg.moveLeft();
            }
            else {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
                
                column++;
                gg.moveRight();
            }
        }
        
        else {
            game.modifyMaze(row, column, prevChar);
            prevChar = game.getChar(row + 1, column);
            game.modifyMaze(row + 1, column, 'G');
            
            row++;
            gg.moveDown();
        }
    }
        
    else if (move == "Right" && checkGhostMove(game, row, column + 1)) {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column + 1);
        game.modifyMaze(row, column + 1, 'G');
        
        column++;
        gg.moveRight();
    }
    
    else if (move == "Left" && checkGhostMove(game, row, column - 1)) {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column - 1);
        game.modifyMaze(row, column - 1, 'G');
        
        column--;
        gg.moveLeft();
    }
    
   
}

void Ghost::moveGhostMedium(Gameplay& game, Pacman& pac, GhostGraphics& gg, std::string move) {
    if (game.getChar(row - 1, column) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row - 1, column);
        game.modifyMaze(row - 1, column, 'G');
        row--;
        gg.moveUp();
    }
    
    else if (game.getChar(row + 1, column) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row + 1, column);
        game.modifyMaze(row + 1, column, 'G');
        row++;
        gg.moveDown();
    }
    
    else if (game.getChar(row, column - 1) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column - 1);
        game.modifyMaze(row, column - 1, 'G');
        column--;
        gg.moveLeft();
    }
    
    else if (game.getChar(row, column + 1) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column + 1);
        game.modifyMaze(row, column + 1, 'G');
        column++;
        gg.moveRight();
    }
    
    else if ((pac.getRow() - getRow() > 4 && pac.getColumn() - getColumn() > 4) || (pac.getRow() - getRow() > -4 && pac.getColumn() - getColumn() > -4)) {
        moveGhostEasy(game, move, gg);
    }
    
    else {
        if (pac.getColumn() < getColumn()) {
            if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar); prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
                
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
                
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row - 1, column)){
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
                
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
        }
        
        else if (pac.getColumn() > getColumn()) {
            if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
               
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row + 1, column)){
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
                
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
               
                column--;
                gg.moveLeft();
            }
        }
        
        else if (pac.getRow() < getRow()) { // if pacman is above ghost
            if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
                
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar); prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
                
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
              
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);    prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
               
                row++;
                gg.moveDown();
            }
        }
        
        else if (pac.getRow() > getRow()) { // if pacman is below ghost
            if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
         
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
              
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
               
                row--;
                gg.moveUp();
            }
        }
        
    }
}

void Ghost::moveGhostHard(Gameplay& game, Pacman& pac, GhostGraphics& gg) {
    if (game.getChar(row - 1, column) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row - 1, column);
        game.modifyMaze(row - 1, column, 'G');
        row--;
        gg.moveUp();
    }
    
    else if (game.getChar(row + 1, column) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row + 1, column);
        game.modifyMaze(row + 1, column, 'G');
        row++;
        gg.moveDown();
    }
    
    else if (game.getChar(row, column - 1) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column - 1);
        game.modifyMaze(row, column - 1, 'G');
        column--;
        gg.moveLeft();
    }
    
    else if (game.getChar(row, column + 1) == 'P') {
        game.modifyMaze(row, column, prevChar);
        prevChar = game.getChar(row, column + 1);
        game.modifyMaze(row, column + 1, 'G');
        column++;
        gg.moveRight();
    }
    
    else {
        if (pac.getColumn() < getColumn()) {
            if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar); prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
                
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
                
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row - 1, column)){
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
                
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
        }
        
        else if (pac.getColumn() > getColumn()) {
            if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
               
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row + 1, column)){
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
                
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar);
                prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
               
                column--;
                gg.moveLeft();
            }
        }
        
        else if (pac.getRow() < getRow()) { // if pacman is above ghost
            if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
                
                row--;
                gg.moveUp();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar); prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
                
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
              
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);    prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
               
                row++;
                gg.moveDown();
            }
        }
        
        else if (pac.getRow() > getRow()) { // if pacman is below ghost
            if (checkGhostMove(game, row + 1, column)) {
                game.modifyMaze(row, column, prevChar);  prevChar = game.getChar(row + 1, column);
                game.modifyMaze(row + 1, column, 'G');
         
                row++;
                gg.moveDown();
            }
            
            else if (checkGhostMove(game, row, column - 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column - 1);
                game.modifyMaze(row, column - 1, 'G');
              
                column--;
                gg.moveLeft();
            }
            
            else if (checkGhostMove(game, row, column + 1)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row, column + 1);
                game.modifyMaze(row, column + 1, 'G');
               
                column++;
                gg.moveRight();
            }
            
            else if (checkGhostMove(game, row - 1, column)) {
                game.modifyMaze(row, column, prevChar);   prevChar = game.getChar(row - 1, column);
                game.modifyMaze(row - 1, column, 'G');
               
                row--;
                gg.moveUp();
            }
        }
        
    }
    
}

void Ghost::resetGhost(Gameplay& game) {
    if (ghostNum == 1) {
        game.modifyMaze(row, column, prevChar);
        row = 5;
        column = 8;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 2) {
        game.modifyMaze(row, column, prevChar);
        row = 5;
        column = 9;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 3) {
        game.modifyMaze(row, column, prevChar);
        row = 5;
        column = 10;
        game.modifyMaze(row, column, 'G');
    }
    
    if (ghostNum == 4) {
        game.modifyMaze(row, column, prevChar);
        row = 5;
        column = 11;
        game.modifyMaze(row, column, 'G');
    }
    
    prevChar = ' ';
}

bool checkCollide(Pacman& pac, Ghost& ghost) {
    if (pac.row == ghost.getRow() && pac.column == ghost.getColumn())
        return true;
    
    return false;
}
