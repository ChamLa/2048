#include "box.h"
#include <iostream>

// void calculateDeltaTime()
// {
//     Uint64 NOW = SDL_GetPerformanceCounter();
//     Uint64 LAST = 0;
//     LAST = NOW;
//     NOW = SDL_GetPerformanceCounter();
//     deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
// }

Box::Box()
{
    this -> rect = {0, 0, 0, 0};
    this -> color = {255, 255, 255};
}

Box::Box(int _x, int _y, int _width, int _height, SDL_Color _color)
{
    this -> rect = {_x, _y, _width, _height};
    this -> color = _color;
}

void Box::setBoxValue(int _x, int _y, int _w, int _h, SDL_Color _color)
{
    this -> rect = {_x, _y, _w, _h};
    this -> color = _color;
}

int Box::getBoxWidth()    { return this -> rect.w; }
int Box::getX() { return this -> rect.x; }
void Box::setColor(SDL_Color _color) { this -> color = _color; }
void Box::setWidth(int _w)  { this -> rect.w = _w; this -> rect.h = _w; }

void Box::generateBox()
{
    
}


void Box::renderBox(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderFillRect(renderer, & this -> rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect( renderer, & this -> rect);
}

void Box::moveDown(int step)
{
    rect.y += step;
}

void Box::moveLeft(int step)
{ 
    rect.x -= step; 
}

void Box::moveRight(int step)
{
    rect.x += step;
}

void Box::moveUp(int step)
{
    rect.y -= step;
}