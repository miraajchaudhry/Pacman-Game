//
//  Header.h
//  Pacman
//
//  Created by Miraaj Chaudhry on 12/10/23.
//

#ifndef PACMAN_h
#define PACMAN_h

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

class Graphics;
class GhostGraphics;
class PacmanGraphics;
class Gameplay;
class Character;
class Pacman;
class Ghost;
class Stats;

class Graphics {
public:
    Graphics();
    Graphics(float newX, float newY);
    virtual void moveUp();
    virtual void moveDown();
    virtual void moveRight();
    virtual void moveLeft();
    virtual void draw();
    void display(Gameplay& game, Graphics& pg, Graphics& g1, Graphics& g2, Graphics& g3, Graphics& g4);
    void drawMainSquare();
    void drawBorder();
    void drawLeftSideWalls();
    void drawMiddleWalls();
    void drawRightSideWalls();
    void drawTokens(Gameplay& game);
    void showScore(std::vector<int> score);
    void showLives(int livesLeft);
    void showStatistics(Gameplay& game);
protected:
    float centerX;
    float centerY;
};

class PacmanGraphics : public Graphics {
public:
    PacmanGraphics();
    void resetPacman();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void swapSides();
    void draw();
    float getAngle() const;
    float getRadius() const;
private:
    float radius;
    float startAngle;
    float endAngle;
};

class GhostGraphics : public Graphics {
public:
    GhostGraphics(Ghost& ghost);
    void resetGhost();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void draw();
    float getHalfLength() const;
private:
    float halfLength;
    int ghostNum;
};

class Stats {
public:
    Stats();
    Stats(int newPts, int numGhosts, int lvs);
    int getPoints() const;
    int getLives() const;
    void increasePoints();
    void decreaseLives();
    
    friend std::ostream& operator<<(std::ostream& out, const Stats& rtObj);
private:
    int points;
    int lives;
};


class Character {
public:
    Character();
    Character(int startingRow, int startingColumn);
    int getRow() const;
    int getColumn() const;
protected:
    int row;
    int column;
};


class Pacman : public Character {
public:
    Pacman(Gameplay& game);
    void handleUserMove(GLFWwindow* window, PacmanGraphics& pac, Gameplay& game);
    bool checkMoveLeft(Gameplay& game);
    bool checkMoveRight(Gameplay& game);
    bool checkMoveUp(Gameplay& game);
    bool checkMoveDown(Gameplay& game);
    void moveLeft(Gameplay& game, PacmanGraphics& pac);
    void moveRight(Gameplay& game, PacmanGraphics& pac);
    void moveUp(Gameplay& game, PacmanGraphics& pac);
    void moveDown(Gameplay& game, PacmanGraphics& pac);
    friend bool checkCollide(Pacman& pac, Ghost& ghost);
    void resetPacman(Gameplay& game);
private:
    
};

class Ghost : public Character {
public:
    Ghost(Gameplay& game, int num, std::string difficulty);
    void setGhostsSpeed(int level);
    std::string getGhostsSpeed() const;
    int getGhostNum() const;
    //void draw() override; // define in main.cpp
    //void updateDraw() override; // define in main.cpp
    void moveGhost(Gameplay& game, Pacman& pac, GhostGraphics& gg);
    void moveGhostEasy(Gameplay& game, std::string move, GhostGraphics& gg);
    void moveGhostMedium(Gameplay& game, Pacman& pac, GhostGraphics& gg, std::string move);
    void moveGhostHard(Gameplay& game, Pacman& pac, GhostGraphics& gg);
    bool GhostPen(Gameplay& game, GhostGraphics& gg); // returns true if ghost has left its pen, false if it hasn't
    bool checkGhostMove(Gameplay& game, int row, int column);
    
    void resetGhost(Gameplay& game);
private:
    char prevChar;
    std::string speed; // based on level of difficulty the player chose (easy = slow, medium = intermediate, challenging = fast)
    std::vector<std::string> moves; // vector to store the four possible moves a ghost can make: will be used to determine each ghost's move during easy and medium levels
    int ghostNum; // each ghost is given num value from 0-3 to help keep track of their movements
};
    

class Gameplay {
public:
    Gameplay(); // change into a default constructor
    void modifyMaze(int row, int column, char newChar); // change to value constructor??
    char getChar(int row, int column);
    void loss();
    void win();
    void increasePoints();
    bool livesLeft();
    bool tokensLeft();
    void collisionOccurs(Pacman& pac, Ghost& g1, Ghost& g2, Ghost& g3, Ghost& g4); //
    Stats getGameStats() const;
private:
    char maze[11][20];
    Stats gameStats;
};


bool checkCollide(Pacman& pac, Ghost& ghost);

#endif /* Header_h */
