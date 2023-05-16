#ifndef __GAME_H
#define __GAME_H

#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mainObject.h"
#include "textObject.h"


// const char *windowTitle = "2048Project";
const SDL_Color windowColor = {206, 223, 255};
const SDL_Color frameColor = {251, 255, 242};
const SDL_Color menuColor = {255, 255, 255};
const SDL_Color choosenMenuColor = {128, 128, 128};

enum menuChoosen
{
    notChoosen = 0, 
    choosePlay = 1,
    chooseExit = 2
};

class Game
{
    int width, height;
    Box frame; 
    mainObject mObject[4][4];
    int score;
    mainObject previousmObject[4][4];
    bool isBoxExist[4][4];
    SDL_Color boxColor[17];
    std :: vector < int > emptyIndex;
    TTF_Font* Font;

    public:
    Game(int _width, int _height, TTF_Font* _font);
    ~Game();

    void initBoxColor();
    SDL_Texture* loadTexture( std:: string path, SDL_Renderer* renderer );
    bool isInsideButtion( int _x, int _y, SDL_Rect rect);
    int loadMenu( SDL_Texture* texture, SDL_Renderer* renderer, TTF_Font* font, int _x, int _y );
    textObject* isMouseInsideButton(int _x, int _y);
    void windowRender(SDL_Renderer *renderer); 

    void coutMainObject();

    bool isInsideFrame(int _x, int _y, int nCell);
    int getMainObjectWidth();
    void findEmpty();
    int randPositionToGenerate();  
    bool generateBox();

    void PremObject();
    bool isMainObjectChange();

    void countDistanceToMoveLeft();
    void countDistanceToMoveRight();
    void countDistanceToMoveUp();
    void countDistanceToMoveDown();

    void renderMoveLeft(SDL_Renderer *renderer);
    void renderMoveRight(SDL_Renderer *renderer);
    void renderMoveUp(SDL_Renderer *renderer);
    void renderMoveDown(SDL_Renderer *renderer);

    void changeBoardObjectLeft();
    void changeBoardObjectRight();
    void changeBoardObjectUp();
    void changeBoardObjectDown();

    int combineLeft();
    int combineRight();
    int combineUp();
    int combineDown();

    void moveLeft(SDL_Renderer *renderer);
    void moveRight(SDL_Renderer *renderer);
    void moveUp(SDL_Renderer *renderer);
    void moveDown(SDL_Renderer *renderer);

    bool gameOver();
    void printGameOver(SDL_Renderer *renderer);
};

#endif