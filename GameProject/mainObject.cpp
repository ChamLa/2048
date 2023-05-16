#include "mainObject.h"
#include <iostream>


mainObject::mainObject() 
{
    this->setBoxValue(0, 0, 0, 0, {0, 0, 0});
    score = 0;
    distanceToMove = 0;
}

mainObject::mainObject(int _x, int _y, int _w, int _h, SDL_Color _color, int _score, int _distance = 0)
{
    this->setBoxValue(_x, _y, _w, _h, _color);
    score = _score;
    distanceToMove = _distance;
}

void mainObject::setValue(int _x, int _y, int _w, int _h, SDL_Color _color, int _score, int _distance = 0)
{
    this->setBoxValue(_x, _y, _w, _h, _color);
    score = _score;
    distanceToMove = _distance;
}

void mainObject :: resetValue()
{
    this->setValue(0, 0, 0, 0, {0, 0, 0}, 0, 0);
}

void mainObject :: setDistanceToMove(int _distance)     { this->distanceToMove = _distance; }
int mainObject :: getDistanceToMove()      { return this->distanceToMove; }

int mainObject :: getWidth()  { return this->getBoxWidth(); }

int mainObject :: getScore() { return this -> score; }
void mainObject :: setScore(int i, int j, int _score, SDL_Color _color)
{ 
    this->setValue(dx[j], dy[i], cellSize, cellSize, _color, _score, 0);
}

void mainObject :: renderMainObject(SDL_Renderer *renderer)
{
    this->renderBox( renderer );
}

void mainObject::moveLeftMain(bool isLastMove)
{
    if(distanceToMove == 0) return;
    int step = (distanceToMove * cellSize) / renderCount; 
    if( isLastMove == true ) step = distanceToMove * cellSize - (renderCount - 1) * step;
    this->moveLeft(step);
}

void mainObject::moveRightMain(bool isLastMove)
{
    if(distanceToMove == 0) return;
    int step = (distanceToMove * cellSize) / renderCount; 
    if( isLastMove == true ) step = distanceToMove * cellSize - (renderCount - 1) * step;
    this->moveRight(step);
}

void mainObject::moveDownMain(bool isLastMove)
{
    if(distanceToMove == 0) return;
    int step = (distanceToMove * cellSize) / renderCount; 
    if( isLastMove == true ) step = distanceToMove * cellSize - (renderCount - 1) * step;
    this->moveDown(step);
}

void mainObject::moveUpMain(bool isLastMove)
{
    if(distanceToMove == 0) return;
    int step = (distanceToMove * cellSize) / renderCount; 
    if( isLastMove == true ) step = distanceToMove * cellSize - (renderCount - 1) * step;
    this->moveUp(step);
}