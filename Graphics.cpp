#define GL_SILENCE_DEPRECATION

#include <iostream>

#include "Pacman.h"

Graphics::Graphics() {
    centerX = 0;
    centerY = 0;
}

Graphics::Graphics(float newX, float newY) {
    centerX = newX;
    centerY = newY;
}

void Graphics::moveUp() {
    centerY += 0.1;
}

void Graphics::moveDown() {
    centerY -= 0.1;
}

void Graphics::moveRight() {
    centerX += 0.09;
}

void Graphics::moveLeft() {
    centerX -= 0.09;
}

void Graphics::draw() {
    std::cout << "Error...Exiting..." << std::endl;
    exit(1);
}

PacmanGraphics::PacmanGraphics() : Graphics(-0.765, 0), radius(0.04), startAngle(45), endAngle(315) {}

void PacmanGraphics::resetPacman() {
    centerX = -0.765;
    centerY = 0;
    radius = 0.04;
    startAngle = 45;
    endAngle = 315;
}

float PacmanGraphics::getAngle() const {
    return startAngle;
}

float PacmanGraphics::getRadius() const {
    return radius;
}

void PacmanGraphics::moveUp() {
    centerY += 0.1;
    startAngle = 135;
    endAngle = 405;
}

void PacmanGraphics::moveDown() {
    centerY -= 0.1;
    startAngle = -45;
    endAngle = 225;
}

void PacmanGraphics::moveRight() {
    if (centerX < 1.71)
        centerX += 0.09;
    startAngle = 45;
    endAngle = 315;
}

void PacmanGraphics::moveLeft() {
    if (centerX > -1.71)
        centerX -= 0.09;
    startAngle = 225;
    endAngle = 495;
}

void PacmanGraphics::swapSides() {
    float x = 0.855;
    
    if (centerX == x)
        centerX = x * -1;
    
    else
        centerX = x;
}

void PacmanGraphics::draw() {
    float tempX, tempY;
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.98f, 0.98f, 0.03f);
    glVertex2f(centerX, centerY);
    for (float i = startAngle; i <= endAngle; i++) {
        tempX = (cos((i * 3.14)/180) * radius) + centerX;
        tempY = (sin((i * 3.14)/180) * radius) + centerY;
        glVertex2f(tempX, tempY);
    }
    glEnd();
}

GhostGraphics::GhostGraphics(Ghost& ghost) : Graphics() {
    centerY = 0;
    halfLength = 0.02;
    
    if (ghost.getGhostNum() == 1) {
        centerX = -0.135;
        ghostNum = 1;
    }
    
    else if (ghost.getGhostNum() == 2) {
        centerX = -0.045;
        ghostNum = 2;
    }
    
    else if (ghost.getGhostNum() == 3) {
        centerX = 0.045;
        ghostNum = 3;
    }
    
    else if (ghost.getGhostNum() == 4) {
        centerX = 0.135;
        ghostNum = 4;
    }
}

void GhostGraphics::resetGhost() {
    centerY = 0;
    halfLength = 0.02;
    
    if (ghostNum == 1)
        centerX = -0.135;
    
    else if (ghostNum == 2)
        centerX = -0.045;
    
    else if (ghostNum == 3)
        centerX = 0.045;
    
    else if (ghostNum == 4)
        centerX = 0.135;
}

float GhostGraphics::getHalfLength() const {
    return halfLength;
}

void GhostGraphics::moveUp() {
    centerY += 0.1;
}

void GhostGraphics::moveDown() {
    centerY -= 0.1;
}

void GhostGraphics::moveRight() {
    centerX += 0.09;
}

void GhostGraphics::moveLeft() {
    centerX -= 0.09;
}

void GhostGraphics::draw() {
    glBegin(GL_QUADS);
    glColor3f(0.88f, 0.86f, 0.79f);
    glVertex2f(centerX + halfLength, centerY + halfLength);
    glVertex2f(centerX + halfLength, centerY - halfLength);
    glVertex2f(centerX - halfLength, centerY - halfLength);
    glVertex2f(centerX - halfLength, centerY + halfLength);
    glEnd();
    
    float tempX;
    float tempY;
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY + halfLength);
    for (float topAngle = 0.0; topAngle <= 360.0; topAngle++) {
        tempX = (cos((topAngle * 3.14)/180) * halfLength) + centerX;
        tempY = (sin((topAngle * 3.14)/180) * halfLength) + centerY + halfLength;
        glVertex2f(tempX, tempY);
    }
    glEnd();
}

void Graphics::drawMainSquare() {
    glBegin(GL_QUADS);
    glColor3f(0.94f, 0.09f, 0.09f);
    glVertex2f(-0.9, -0.55);
    glVertex2f(0.9, -0.55);
    glVertex2f(0.9, 0.55);
    glVertex2f(-0.9, 0.55);
    glEnd();
}

void Graphics::drawBorder() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.2f, 0.46f);
    glVertex2f(-0.9, 0.55);
    glVertex2f(-0.9, 0.45);
    glVertex2f(0.9, 0.45);
    glVertex2f(0.9, 0.55);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.9, -0.55);
    glVertex2f(-0.9, -0.45);
    glVertex2f(0.9, -0.45);
    glVertex2f(0.9, -0.55);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.9, 0.55);
    glVertex2f(-0.81, 0.55);
    glVertex2f(-0.81, 0.05);
    glVertex2f(-0.9, 0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.9, -0.55);
    glVertex2f(-0.81, -0.55);
    glVertex2f(-0.81, -0.05);
    glVertex2f(-0.9, -0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.9, 0.55);
    glVertex2f(0.81, 0.55);
    glVertex2f(0.81, 0.05);
    glVertex2f(0.9, 0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.9, -0.55);
    glVertex2f(0.81, -0.55);
    glVertex2f(0.81, -0.05);
    glVertex2f(0.9, -0.05);
    glEnd();
}

void Graphics::drawLeftSideWalls() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.2f, 0.46f);
    glVertex2f(-0.72, -0.35);
    glVertex2f(-0.72, -0.25);
    glVertex2f(-0.36, -0.25);
    glVertex2f(-0.36, -0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.72, -0.25);
    glVertex2f(-0.72, -0.15);
    glVertex2f(-0.63, -0.15);
    glVertex2f(-0.63, -0.25);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.72, -0.05);
    glVertex2f(-0.72, 0.05);
    glVertex2f(-0.36, 0.05);
    glVertex2f(-0.36, -0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.45, -0.15);
    glVertex2f(-0.45, 0.15);
    glVertex2f(-0.36, 0.15);
    glVertex2f(-0.36, -0.15);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.72, 0.35);
    glVertex2f(-0.72, 0.25);
    glVertex2f(-0.36, 0.25);
    glVertex2f(-0.36, 0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.72, 0.25);
    glVertex2f(-0.72, 0.15);
    glVertex2f(-0.63, 0.15);
    glVertex2f(-0.63, 0.25);
    glEnd();
}

void Graphics::drawMiddleWalls() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.2f, 0.46f);
    glVertex2f(-0.27, 0.35);
    glVertex2f(-0.27, 0.25);
    glVertex2f(0.27, 0.25);
    glVertex2f(0.27, 0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.27, -0.35);
    glVertex2f(-0.27, -0.25);
    glVertex2f(0.27, -0.25);
    glVertex2f(0.27, -0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.27, -0.05);
    glVertex2f(-0.27, -0.15);
    glVertex2f(0.27, -0.15);
    glVertex2f(0.27, -0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.27, -0.15);
    glVertex2f(-0.27, 0.15);
    glVertex2f(-0.18, 0.15);
    glVertex2f(-0.18, -0.15);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.27, -0.15);
    glVertex2f(0.27, 0.15);
    glVertex2f(0.18, 0.15);
    glVertex2f(0.18, -0.15);
    glEnd();
}

void Graphics::drawRightSideWalls(){
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.2f, 0.46f);
    glVertex2f(0.72, -0.35);
    glVertex2f(0.72, -0.25);
    glVertex2f(0.36, -0.25);
    glVertex2f(0.36, -0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.72, -0.25);
    glVertex2f(0.72, -0.15);
    glVertex2f(0.63, -0.15);
    glVertex2f(0.63, -0.25);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.72, -0.05);
    glVertex2f(0.72, 0.05);
    glVertex2f(0.36, 0.05);
    glVertex2f(0.36, -0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.45, -0.15);
    glVertex2f(0.45, 0.15);
    glVertex2f(0.36, 0.15);
    glVertex2f(0.36, -0.15);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.72, 0.35);
    glVertex2f(0.72, 0.25);
    glVertex2f(0.36, 0.25);
    glVertex2f(0.36, 0.35);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(0.72, 0.25);
    glVertex2f(0.72, 0.15);
    glVertex2f(0.63, 0.15);
    glVertex2f(0.63, 0.25);
    glEnd();
}

void Graphics::drawTokens(Gameplay& gameplay) {
    float tempX, tempY, tokenAngle;

    if (gameplay.getChar(5, 0) == '*') {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(-0.855, 0);
        for (tokenAngle = 0; tokenAngle < 360; tokenAngle++) {
            tempX = (cos(tokenAngle * (3.14/180)) * 0.01) - 0.855;
            tempY = (sin(tokenAngle * (3.14/180)) * 0.01);
            glVertex2f(tempX, tempY);
        }
        glEnd();
    }
    
    float x = -0.765;
    float y = 0.4;
    
    for (int rowIt = 1; rowIt < 11; rowIt++) {
        for (int columnIt = 1; columnIt < 20; columnIt++) {
            if (gameplay.getChar(rowIt, columnIt) == '*') {
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x, y);
                for (tokenAngle = 0; tokenAngle < 360; tokenAngle++) {
                    tempX = (cos(tokenAngle * (3.14/180)) * 0.01) + x;
                    tempY = (sin(tokenAngle * (3.14/180)) * 0.01) + y;
                    glVertex2f(tempX, tempY);
                }
                glEnd();
            }
            
            if (columnIt == 19)
                x = -0.765;
            else
                x = x + 0.09;
        }
        y = y - 0.1;
    }
}

void Graphics::showScore(std::vector<int> score) {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.98f, 0.98f, 0.03f);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.88, -0.6);
    glVertex2f(-0.9, -0.6);
    glVertex2f(-0.9, -0.62);
    glVertex2f(-0.88, -0.62);
    glVertex2f(-0.88, -0.64);
    glVertex2f(-0.9, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.84, -0.6);
    glVertex2f(-0.86, -0.6);
    glVertex2f(-0.86, -0.64);
    glVertex2f(-0.84, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.80, -0.6);
    glVertex2f(-0.82, -0.6);
    glVertex2f(-0.82, -0.64);
    glVertex2f(-0.80, -0.64);
    glVertex2f(-0.80, -0.6);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.78, -0.64);
    glVertex2f(-0.78, -0.6);
    glVertex2f(-0.76, -0.6);
    glVertex2f(-0.76, -0.62);
    glVertex2f(-0.78, -0.62);
    glVertex2f(-0.76, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.72, -0.6);
    glVertex2f(-0.74, -0.6);
    glVertex2f(-0.74, -0.62);
    glVertex2f(-0.72, -0.62);
    glVertex2f(-0.74, -0.62);
    glVertex2f(-0.74, -0.64);
    glVertex2f(-0.72, -0.64);
    glEnd();
    
    glBegin(GL_POINTS);
    glVertex2f(-0.7, -0.61);
    glVertex2f(-0.7, -0.63);
    glEnd();
    
    
    // draw out the score
    float x = -0.68;
    float y = -0.6;
    int i = 0;
    
    for (int num = 0; num < 3; num++) {
        glBegin(GL_LINE_STRIP);
        if (score[i] == 1 || score[i] == 4)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x, y);
        glVertex2f(x + 0.02, y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        if (score[i] == 5 || score[i] == 6)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x + 0.02, y);
        glVertex2f(x + 0.02, y - 0.02);
        glEnd();
        glBegin(GL_LINE_STRIP);
        if (score[i] == 2)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x + 0.02, y - 0.02);
        glVertex2f(x + 0.02, y - 0.04);
        glEnd();
        glBegin(GL_LINE_STRIP);
        if (score[i] == 1 || score[i] == 4 || score[i] == 7)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x + 0.02, y - 0.04);
        glVertex2f(x, y - 0.04);
        glEnd();
        glBegin(GL_LINE_STRIP);
        if (score[i] == 1 || score[i] == 3 || score[i] == 4 || score[i] == 5 || score[i] == 7 || score[i] == 9)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x, y - 0.04);
        glVertex2f(x, y - 0.02);
        glEnd();
        glBegin(GL_LINE_STRIP);
        if (score[i] == 1 || score[i] == 2 || score[i] == 3 || score[i] == 7)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x, y - 0.02);
        glVertex2f(x, y);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        if (score[i] == 0 || score[i] == 1 || score[i] == 7)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(0.98f, 0.98f, 0.03f);
        glVertex2f(x, y - 0.02);
        glVertex2f(x + 0.02, y - 0.02);
        glEnd();
        
        x += 0.04;
        i++;
    }
}

void Graphics::showLives(int livesLeft) {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.98f, 0.98f, 0.03f);
    glVertex2f(-0.44, -0.6);
    glVertex2f(-0.44, -0.64);
    glVertex2f(-0.42, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.4, -0.6);
    glVertex2f(-0.4, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.38, -0.6);
    glVertex2f(-0.37, -0.64);
    glVertex2f(-0.36, -0.6);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.32, -0.6);
    glVertex2f(-0.34, -0.6);
    glVertex2f(-0.34, -0.62);
    glVertex2f(-0.32, -0.62);
    glVertex2f(-0.34, -0.62);
    glVertex2f(-0.34, -0.64);
    glVertex2f(-0.32, -0.64);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.28, -0.6);
    glVertex2f(-0.3, -0.6);
    glVertex2f(-0.3, -0.62);
    glVertex2f(-0.28, -0.62);
    glVertex2f(-0.28, -0.64);
    glVertex2f(-0.3, -0.64);
    glEnd();
    
    glBegin(GL_POINTS);
    glVertex2f(-0.26, -0.61);
    glVertex2f(-0.26, -0.63);
    glEnd();
    
    if (livesLeft == 1) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.22, -0.6);
        glVertex2f(-0.22, -0.64);
        glEnd();
    }
    
    else if (livesLeft == 2) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.24, -0.6);
        glVertex2f(-0.22, -0.6);
        glVertex2f(-0.22, -0.62);
        glVertex2f(-0.24, -0.62);
        glVertex2f(-0.24, -0.64);
        glVertex2f(-0.22, -0.64);
        glEnd();
    }
    
    else {
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.2, -0.6);
        glVertex2f(-0.18, -0.6);
        glVertex2f(-0.18, -0.62);
        glVertex2f(-0.2, -0.62);
        glVertex2f(-0.18, -0.62);
        glVertex2f(-0.18, -0.64);
        glVertex2f(-0.2, -0.64);
        glEnd();
    }
}

void Graphics::showStatistics(Gameplay& game) {
    Stats stats = game.getGameStats();
    int points = stats.getPoints();
    int livesLeft = stats.getLives();
    
    std::vector<int> score;
    score.push_back(points / 100);
    score.push_back((points - (100 * score[0])) / 10);
    score.push_back(0);
    
    showScore(score);
    showLives(livesLeft);
}
