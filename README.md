# Pacman-Game

## Description
Developed a Pacman game using C++ and object-oriented programming. Utilized the OpenGL library for real-time graphics and the GLFW3 library to handle user input.

## Features
- Allow the user to select one of four levels
- Each level is more difficult than the previous
- User can control Pacman via arrow keys
- Pacman can move around maze along as it has at least one life and tokens are available
- Four ghosts are programmed to chase Pacman
- Ghosts' speed and strategy differ per difficulty
- Ghosts on easy and intermediate levels use random movements to trap Pacman
- Ghosts on hard and impossible levels are programmed trap Pacman based on his location
- Pacman can teleport from one end of maze to other using entrances/exits
- User can keep track of score and lives remaining


## Tech Stack
- C++
- OpenGL
- GLFW3
- XCode

## Algorithms/Concepts
- Object-oriented programming
- Self-designed algorithm for ghost movement
- Self-designed algorithm to display score and lives

## Prerequisites
- C++ installed
  
## Installation

## Usage
1) Start program
2) Input difficulty level as instructed, press 'Enter'
3) Use arrows to move Pacman throughout maze; avoid ghosts and eat tokens
4) Lose a life if a ghost eats you
5) If you eat all tokens before three lives are up, you win
