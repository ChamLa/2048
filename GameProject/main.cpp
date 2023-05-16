#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "game.h"  


const int WIDTH = 600, HEIGHT = 600;
SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* Font;

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING ); 
    TTF_Init ();
    Font = TTF_OpenFont("Font\\Montserrat.ttf", 40);
    Game game(WIDTH, HEIGHT, Font);  

    // game.init( window, renderer ); 
    window = SDL_CreateWindow( "2048Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
    renderer = SDL_CreateRenderer(window, -1, 0); 
    game.initBoxColor();

    int isChoosen = game.loadMenu( game.loadTexture ("Image\\Menu6.png", renderer ), renderer , Font, 0, 0);


    SDL_Event Event;




    bool isInMenuPage = true;
    bool isFirstTime = true;
    bool isContinue = true;
    while ( isContinue )
    {
        // SDL_SetRenderDrawColor( renderer, windowColor.r, windowColor.g, windowColor.b, 255 );

        if(SDL_WaitEvent(&Event) == 0) continue;
        if(Event.type == SDL_QUIT) break;

        if(isInMenuPage == true)
        {
            if(Event.type == SDL_MOUSEMOTION)
            {
                isChoosen = game.loadMenu( game.loadTexture ("Image\\Menu6.png", renderer ), renderer , Font, Event.motion.x, Event.motion.y);
            }
            if(Event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(Event.button.button == SDL_BUTTON_LEFT)
                {
                    isChoosen = game.loadMenu( game.loadTexture ("Image\\Menu6.png", renderer ), renderer , Font, Event.motion.x, Event.motion.y);
                    switch ( isChoosen )
                    {
                    case choosePlay:
                        isInMenuPage = false;
                        break;
                    case chooseExit:
                        isContinue = false;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        }
        else 
        {
            if(isFirstTime == true)
            {
                game.generateBox();
                game.windowRender( renderer ); 
                SDL_RenderPresent( renderer );
                game.coutMainObject();
                isFirstTime = false;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                game.PremObject();
                switch (Event.key.keysym.sym)
                {
                case SDLK_ESCAPE: break;
                case SDLK_LEFT: game.moveLeft( renderer );
                                break;
                case SDLK_RIGHT: game.moveRight( renderer );
                                break;
                case SDLK_UP: game.moveUp( renderer );
                                break;
                case SDLK_DOWN: game.moveDown( renderer );
                                break;
                default:
                    break;
                }
                if(game.isMainObjectChange())
                {
                    game.generateBox();
                    game.windowRender( renderer );
                }
                else if(game.gameOver() == true)
                {
                    isContinue = false;
                    game.printGameOver( renderer );
                    SDL_Delay( 5000 );
                    continue;
                }
                game.coutMainObject();
                std :: cout << '\n';
            }
        }

    }
    SDL_DestroyRenderer ( renderer );
    SDL_DestroyWindow( window );
    TTF_Quit( );
    IMG_Quit( );
    SDL_Quit( );

    return EXIT_SUCCESS;
}


/*
box -> 

game 
{
    bdau
    {
        frame
        box: generate
        {
            findEmpty           -> push vao vector
            randPosition        -> rand id vector -> choose Pos -> clear vector
            generateBox
        }
    }

    choi
    {
        event: 
        {
            box: move               Time: 0.002s
            {
                getPos          ok
                newPos          
                {
                    idea: ben trai co bao nhieu box -> di chuyen xa nhat co the

                    sol: 
                    {
                        check(0, i - 1) -> getNewPos (su dung Box.w == 0)
                    }
                }
                moveBox
                {
                    sol:
                    moveDirection(int howfar)
                }
            }
            
            if(isEqual)        (can co bien value cho cac box)      Time: 0.001s
            {
                clearBox        (Box[i].w = new Box())
                changeValue(leftBox)        ChangeValueBox[newPos - 1]
            }
            sol:
            {
                for(row)
                {
                    i = 0;
                    while(i < nCell - 1)
                    {
                        if(isEqual(i, i + 1))
                        {
                            clearBox(i + 1);
                            changeValueBox(i);
                            i += 2;
                        }
                        else i ++;
                    }
                }
            }
        }
    }

}
*/