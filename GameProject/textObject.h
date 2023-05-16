#ifndef __TEXTOBJECT_H
#define __TEXTOBJECT_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class textObject
{
    std :: string textStr;
    SDL_Color textColor;
    TTF_Font* textFont; 
    SDL_Rect textRect;

    public:
    textObject();
    textObject(int _x, int _y, std :: string _text, SDL_Color _color, TTF_Font* _font);
    ~textObject();
    void setTextStr(std :: string _text);
    void setColor (SDL_Color _color);
    void setFont (TTF_Font* _font); 
    void setRect (SDL_Rect _rect); 
    SDL_Rect getRect();

    void renderText( SDL_Renderer* renderer );

};

#endif