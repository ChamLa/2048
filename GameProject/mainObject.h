#ifndef __MAINOBJECT_H
#define __MAINOBJECT_H

#include "box.h"
#include <vector>

const int nCell = 4;
const int upperLeftX = 140;
const int upperLeftY = 220;
const int dx[4] = {upperLeftX, upperLeftX + cellSize, upperLeftX + cellSize*2, upperLeftX + cellSize*3};
const int dy[4] = {upperLeftY, upperLeftY + cellSize, upperLeftY + cellSize*2, upperLeftY + cellSize*3};
const SDL_Color randBoxColor[32] = {{255, 208, 208}, {255, 179, 179}, {255, 149, 149}, {255, 114, 114}, 
                                    {255, 201, 254}, {255, 151, 252}, {218, 199, 255}, {192, 161, 255}, 
                                    {168, 124, 255}, {196, 208, 255}, {165, 183, 255}, {132, 157, 255}, 
                                    {94, 126, 255}, {181, 233, 255}, {125, 217, 255}, {198, 255, 235},
                                    {198, 255, 235}, {155, 255, 219}, {200, 255, 193}, {152, 255, 141},
                                    {230, 255, 186}, {217, 255, 149}, {201, 255, 105}, {255, 255, 176}, 
                                    {255, 255, 124}, {255, 237, 175}, {255, 223, 117}, {255, 210, 158}, 
                                    {255, 186, 107}, {149, 184, 209}, {234, 196, 213}, {212, 175, 185}};


class mainObject : public Box
{
    int score;
    int distanceToMove;
public:
    mainObject();
    ~mainObject();
    mainObject(int _x, int _y, int _w, int _h, SDL_Color _color, int _score, int _distance);
    void setValue(int _x, int _y, int _w, int _h, SDL_Color _color, int _score, int _distance);
    void resetValue();
    void setDistanceToMove(int _distance);
    int getDistanceToMove();
    int getWidth();
    int getScore();
    void setScore(int i, int j, int _score, SDL_Color _color);

    void renderMainObject(SDL_Renderer *renderer);

    void moveLeftMain(bool isLastMove);
    void moveRightMain(bool isLastMove);
    void moveDownMain(bool isLastMove);
    void moveUpMain(bool isLastMove);
    
};

#endif