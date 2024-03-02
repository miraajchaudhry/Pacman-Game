#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

#include "Pacman.h"

// a function to display the graphics
void Graphics::display(Gameplay& game, Graphics& pg, Graphics& g1, Graphics& g2, Graphics& g3, Graphics& g4) {
    drawMainSquare(); // draws the main square in which the maze and game take place

    drawBorder(); // draws border/boundary for the maze

    drawLeftSideWalls(); // draws maze's left walls
    drawRightSideWalls(); // draws maze's right walls
    drawMiddleWalls(); // draws maze's middle walls (including the ghosts pen)

    pg.draw(); // draws the pacman
    
    drawTokens(game); // draws tokens
    
    //draw each of the four ghosts
    g1.draw();
    g2.draw();
    g3.draw();
    g4.draw();
    
    showStatistics(game); // shows the stats (points and lives remaining)
}

void delay(std::string difficultyLevel) {
    double delaySec; // holds how long each delay will be
    
    if (difficultyLevel == "easy")
        delaySec = 0.25;
    
    else if (difficultyLevel == "medium")
        delaySec = 0.25;
    
    else if (difficultyLevel == "hard")
        delaySec = 0.2;
    
    else
        delaySec = 0.15;
    
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    while (elapsed_seconds.count() < delaySec) {
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
    }
}

void play(std::string difficulty) {
    Gameplay gameplay;
    Pacman pacman(gameplay);
    Ghost ghost1(gameplay, 1, difficulty), ghost2(gameplay, 2, difficulty), ghost3(gameplay, 3, difficulty), ghost4(gameplay, 4, difficulty);
    Graphics gameboard;
    
    GLFWwindow* window;
    
    if (!glfwInit()) {
        std::cout << "Error. Exiting..." << std::endl;
        exit(1);
    }
    
    window = glfwCreateWindow(1200, 800, "THE PACMAN", nullptr, nullptr);
    
    if (!window) {
        std::cout << "Error: Unable to open Pacman window. Exiting..." << std::endl;
        glfwTerminate();
        exit(1);
    }
  
    glfwMakeContextCurrent(window);
    
    PacmanGraphics pg;
    GhostGraphics g1(ghost1), g2(ghost2), g3(ghost3), g4(ghost4);
    
    while(!glfwWindowShouldClose(window) && gameplay.livesLeft()) {
        if (checkCollide(pacman, ghost1) || checkCollide(pacman, ghost2) || checkCollide(pacman, ghost3) || checkCollide(pacman, ghost4)) {
                   gameplay.collisionOccurs(pacman, ghost1, ghost2, ghost3, ghost4);
                   pg.resetPacman();
                   g1.resetGhost();
                   g2.resetGhost();
                   g3.resetGhost();
                   g4.resetGhost();
        }
        
        if (ghost1.GhostPen(gameplay, g1))
            ghost1.moveGhost(gameplay, pacman, g1);
        
        if (ghost2.GhostPen(gameplay, g2))
            ghost2.moveGhost(gameplay, pacman, g2);
        
        if (ghost3.GhostPen(gameplay, g3))
            ghost3.moveGhost(gameplay, pacman, g3);
        
        if (ghost4.GhostPen(gameplay, g4))
            ghost4.moveGhost(gameplay, pacman, g4);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (checkCollide(pacman, ghost1) || checkCollide(pacman, ghost2) || checkCollide(pacman, ghost3) || checkCollide(pacman, ghost4)) {
                   gameplay.collisionOccurs(pacman, ghost1, ghost2, ghost3, ghost4);
                   pg.resetPacman();
                   g1.resetGhost();
                   g2.resetGhost();
                   g3.resetGhost();
                   g4.resetGhost();
        }
        
        pacman.handleUserMove(window, pg, gameplay); // handles player pressing any key
        
        gameboard.display(gameplay, pg, g1, g2, g3, g4);
        
        glfwSwapBuffers(window);
        
        delay(difficulty); // call to self-defined framerate limit function
        
        if (!gameplay.tokensLeft())
            break; // game over if no more tokens left to collect
        
        glfwPollEvents();
    }
    
    if (gameplay.livesLeft()) // if player won
        gameplay.win();
    
    else // if player loss
        gameplay.loss();
    
    glfwTerminate();
}

void options() {
    int level;
    std::string difficulty;
    
    std::cout << "Which level would you like to play (press number followed by 'return' to play level):" << std::endl << "\t1. Easy" << std::endl << "\t2. Medium" << std::endl << "\t3. Hard" << std::endl << "\t4. Impossible" << std::endl;
    std::cin >> level;
        
    if (level == 1)
        difficulty = "easy";
        
    else if (level == 2)
        difficulty = "medium";
        
    else if (level == 3)
        difficulty = "hard";
        
    else
        difficulty = "impossible";
        
    play(difficulty);
}

int main(int argc, char* argv[]) {
    std::cout << "Welcome to The Pacman Game!" << std::endl;
    
    options();

    char again;
    do {
        std::cout << "Would you like to play again?" << std::endl << "Press 'y' for yes, or 'n' for no: ";
        std::cin >> again;
        
        if (again == 'y')
            options();
        
        else
            std::cout << "Thanks for playing! Come back soon..." << std::endl;
    } while (again == 'y');
    
    return 0;
}




