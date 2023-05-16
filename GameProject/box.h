#ifndef __BOX_H
#define __BOX_H

#include <SDL2/SDL.h>

const int cellSize = 80;
const double timeMove = 0.001;
const double deltaTime = 0.0001;
const int renderCount = timeMove / deltaTime; 
    
// void calculateDeltaTime();

class Box
{
    SDL_Rect rect;
    SDL_Color color;

    public:
    Box();
    ~Box();
    Box(int _x, int _y, int _width, int _height, SDL_Color _color);
    void setBoxValue(int _x, int _y, int _w, int _h, SDL_Color _color);
    int getBoxWidth();
    int getX();
    void setColor(SDL_Color _color);
    void setWidth(int _w);

    
    void generateBox();

    void renderBox(SDL_Renderer *renderer);
    
    void moveLeft(int step);
    void moveRight(int step);
    void moveDown(int step);
    void moveUp(int step);
};

#endif