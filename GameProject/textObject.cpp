#include "textObject.h"

textObject::textObject()
{
}

textObject::textObject(int _x, int _y, std::string _text, SDL_Color _color, TTF_Font *_font)
{
    textStr = _text;
    textColor = _color;
    textFont = _font;
    TTF_SizeText(textFont, textStr.c_str(), &textRect.w, &textRect.h);
    textRect.x = _x;    textRect.y = _y;
}

textObject::~textObject()
{
}

void textObject::setTextStr(std::string _text)  { textStr = _text; }

void textObject::setColor(SDL_Color _color) {  textColor = _color; }

void textObject::setFont(TTF_Font *_font) { textFont = _font; }

void textObject::setRect(SDL_Rect _rect)  { textRect = _rect; } 

SDL_Rect textObject::getRect() { return this->textRect; }

void textObject::renderText( SDL_Renderer *renderer )
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( textFont, textStr.c_str(), textColor ); 
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface ( renderer, textSurface );
    SDL_FreeSurface ( textSurface );

    SDL_Rect srcRest;
    TTF_SizeText(textFont, textStr.c_str(), &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;  

    SDL_RenderCopy(renderer, textTexture, &srcRest, &this -> textRect); 
    SDL_RenderPresent(renderer);
}
