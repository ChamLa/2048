#include "game.h"

Game::Game(int _width, int _height, TTF_Font* _font)
{
    this -> width = _width;
    this -> height = _height;
    this -> Font = _font;
    score = 0;
    frame.setBoxValue(upperLeftX, upperLeftY, cellSize * nCell, cellSize * nCell, frameColor); 
    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
        isBoxExist[i][j] = 0;
}

void Game::initBoxColor()
{
    std :: vector < int > randNum;
    for(int i = 0; i < 32; i ++)
        randNum.push_back(i);
    for(int i = 0; i < 17; i ++)
    {
        int id = rand() % (int)randNum.size();
        boxColor[i] = randBoxColor[randNum[id]];
        randNum.erase( randNum.begin() + id);
    }
}

SDL_Texture *Game::loadTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    return newTexture;
}

bool Game::isInsideButtion(int _x, int _y, SDL_Rect rect)
{
    int min_x = rect.x, max_x = rect.x + rect.w;
    int min_y = rect.y, max_y = rect.y + rect.h; 
    if(min_x <= _x && _x <= max_x && min_y <= _y && _y <= max_y) return true;
    return false;
}

int Game::loadMenu(SDL_Texture *texture, SDL_Renderer *renderer, TTF_Font* font, int _x, int _y)
{
    int ans = notChoosen;
    SDL_RenderCopy ( renderer, texture, NULL, NULL );
    textObject playButton (260, 280, "play", menuColor, font);
    SDL_Rect rect = playButton.getRect();
    if(isInsideButtion( _x, _y, rect ))     
    {   
        playButton.setColor( choosenMenuColor );  
        ans = choosePlay; 
    }
    textObject exitButton (260, 390, "exit", menuColor, font);
    rect = exitButton.getRect();
    if(isInsideButtion( _x, _y, rect ))     
    {   
        exitButton.setColor( choosenMenuColor );
        ans = chooseExit;   
    } 

    playButton.renderText( renderer );
    exitButton.renderText( renderer );
    return ans;
}

void Game::windowRender(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor( renderer, windowColor.r, windowColor.g, windowColor.b, 255 );
    SDL_RenderClear( renderer );
    frame.renderBox( renderer ); 

    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
        if(mObject[i][j].getBoxWidth())
        {
            mObject[i][j].renderBox( renderer );
        }
    std :: ostringstream strNum;
    strNum << score;
    textObject Score(50, 90, "Score: " + strNum.str(), {255, 255, 255}, Font);
    Score.renderText ( renderer );
    SDL_RenderPresent( renderer );
}

void Game :: coutMainObject()
{
    for(int i = 0; i < nCell; i ++)
    {
        for(int j = 0; j < nCell; j ++)
            std :: cout << mObject[i][j].getScore() << ' ';
        std :: cout << '\n';
    }
}

bool Game :: isInsideFrame(int _x, int _y, int nCell)
{
    if(0 < _x && _x < nCell - 1 && 0 < _y && _y < nCell - 1) return true;
    return false;
}

void Game :: findEmpty()
{
    int nCell = 4;
    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
    { 
        if(isInsideFrame(i, j, nCell)) continue;
        if(mObject[i][j].getWidth()) continue;
        emptyIndex.push_back(i * nCell + j);
        // std :: cout << i * nCell + j << '\n';
    }
}

int Game :: randPositionToGenerate()
{
    return rand()%(int(emptyIndex.size()));
} 

bool Game::generateBox()
{
    findEmpty();
    int index = randPositionToGenerate();
    int _x = emptyIndex[index] / nCell;
    int _y = emptyIndex[index] % nCell; 
    if(emptyIndex.size() == 0) return false; 
    mObject[_x][_y].setValue(dx[_y], dy[_x], cellSize, cellSize, boxColor[1], 1, 0);
    emptyIndex.clear();
    return true;
}

void Game :: PremObject()
{
    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
        previousmObject[i][j] = mObject[i][j];
}

bool Game :: isMainObjectChange()
{
    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
        if(mObject[i][j].getScore() != previousmObject[i][j].getScore())
            return true;
    return false;
}

/*
move
{
    findS
    {
        co bnhieu box o truoc no ?
        quang duong = (i - box - 1) * cellSize
    }
    move(S) 
    {
        step = quangduong / renderCount
    }
}
*/

void Game :: countDistanceToMoveLeft()
{
    for(int i = 0; i < nCell; i ++)
    {   
        int countPreviousBox = 0;
        for(int j = 0; j < nCell; j ++)
        {
            mObject[i][j].setDistanceToMove(0);
            if(mObject[i][j].getWidth() == 0) continue; 
            // std :: cout << i << ' ' << j << ' ' << countPreviousBox << ' ' << mObject[i][j].getDistanceToMove() << '\n';
            mObject[i][j].setDistanceToMove(j - countPreviousBox);
            countPreviousBox ++;
        } 
    }
}

void Game :: renderMoveLeft(SDL_Renderer *renderer)
{ 
    bool isLastMove = false;
    for(int count = 0; count < renderCount; count ++)
    { 
        if(count == renderCount - 1) isLastMove = true;
        for(int i = 0; i < nCell; i ++)
        for(int j = 0; j < nCell; j ++)
        {
            mObject[i][j].moveLeftMain( isLastMove );
            windowRender ( renderer );
        }
    }
}

void Game :: changeBoardObjectLeft()
{
    for(int i = 0; i < nCell; i ++)
    for(int j = 0; j < nCell; j ++)
    {
        if(mObject[i][j].getDistanceToMove() == 0) continue;
        int changeIndex = mObject[i][j].getDistanceToMove(); 
        mObject[i][j - changeIndex] = mObject[i][j];
        mObject[i][j].resetValue();
    }
}

int Game :: combineLeft()
{
    int res = 0;
    for(int i = 0; i < nCell; i ++)
    {
        int j = 0;
        while(j <= nCell - 1)
        { 
            if(mObject[i][j].getWidth() == 0) 
            {
                j ++; 
                continue;
            }
            if(j == nCell - 1)
            {
                for(int k = 0; k < j; k ++)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j ++; 
                continue;
            }
            if(mObject[i][j].getScore() == mObject[i][j + 1].getScore())
            {
                res += (1 << mObject[i][j].getScore()) * 2;
                int _score = mObject[i][j].getScore() + 1;
                mObject[i][j].setScore(i, j, _score, boxColor[_score]);
                mObject[i][j + 1].resetValue();
                for(int k = 0; k < j; k ++)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j += 2;
            }
            else 
            {
                for(int k = 0; k < j; k ++)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j ++;
            } 
        }
    }
    return res;
}

void Game::moveLeft(SDL_Renderer *renderer)
{
    countDistanceToMoveLeft();
    renderMoveLeft( renderer );
    changeBoardObjectLeft();

    coutMainObject();

    score += combineLeft(); 
    windowRender( renderer );
}

void Game :: countDistanceToMoveRight()
{
    for(int i = 0; i < nCell; i ++)
    {   
        int countPreviousBox = 0;
        for(int j = nCell - 1; j >= 0; j --)
        {
            mObject[i][j].setDistanceToMove(0);
            if(mObject[i][j].getWidth() == 0) continue; 
            // std :: cout << i << ' ' << j << ' ' << countPreviousBox << ' ' << mObject[i][j].getDistanceToMove() << '\n';
            mObject[i][j].setDistanceToMove(nCell - 1 - j - countPreviousBox);
            countPreviousBox ++;
        } 
    } 
}

void Game :: renderMoveRight(SDL_Renderer *renderer)
{
    bool isLastMove = false;
    for(int count = 0; count < renderCount; count ++)
    { 
        if(count == renderCount - 1) isLastMove = true;
        for(int i = 0; i < nCell; i ++)
        for(int j = 0; j < nCell; j ++)
        {
            mObject[i][j].moveRightMain( isLastMove ); 
            windowRender ( renderer );
        }
    }
}

void Game :: changeBoardObjectRight()
{
    for(int i = 0; i < nCell; i ++)
    for(int j = nCell - 1; j >= 0; j --)
    {
        if(mObject[i][j].getDistanceToMove() == 0) continue;
        int changeIndex = mObject[i][j].getDistanceToMove(); 
        mObject[i][j + changeIndex] = mObject[i][j];
        mObject[i][j].resetValue();
    }
}

int Game :: combineRight()
{
    int res = 0;
    for(int i = 0; i < nCell; i ++)
    {
        int j = nCell - 1;
        while(j >= 0)
        {
            if(mObject[i][j].getWidth() == 0) 
            {
                j --;
                continue;
            }
            if(j == 0)
            {
                for(int k = nCell - 1; k > j; k --)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j --;
                continue;
            }
            if(mObject[i][j].getScore() == mObject[i][j - 1].getScore())
            {
                res += (1 << mObject[i][j].getScore()) * 2;
                int _score = mObject[i][j].getScore() + 1;
                mObject[i][j].setScore(i, j, _score, boxColor[_score]);
                mObject[i][j - 1].resetValue();
                for(int k = nCell - 1; k > j; k --)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j -= 2;
            }
            else 
            {
                for(int k = nCell - 1; k > j; k --)
                    if(mObject[i][k].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[i][k].setScore(i, k, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                j --;
            }
        }
    }
    return res;
}

void Game::moveRight(SDL_Renderer *renderer)
{
    countDistanceToMoveRight();
    renderMoveRight( renderer );
    changeBoardObjectRight();

    coutMainObject();

    score += combineRight(); 
    windowRender( renderer );
}

void Game :: countDistanceToMoveUp()
{
    for(int j = 0; j < nCell; j ++)
    {   
        int countPreviousBox = 0;
        for(int i = 0; i < nCell; i ++)
        {
            mObject[i][j].setDistanceToMove(0);
            if(mObject[i][j].getWidth() == 0) continue; 
            std :: cout << i << ' ' << j << ' ' << countPreviousBox << ' ' << mObject[i][j].getDistanceToMove() << '\n';
            mObject[i][j].setDistanceToMove(i - countPreviousBox);
            countPreviousBox ++;

        } 
    }
}

void Game :: renderMoveUp(SDL_Renderer *renderer)
{
    bool isLastMove = false;
    for(int count = 0; count < renderCount; count ++)
    { 
        if(count == renderCount - 1) isLastMove = true;
        for(int i = 0; i < nCell; i ++)
        for(int j = 0; j < nCell; j ++)
        {
            mObject[i][j].moveUpMain( isLastMove ); 
            windowRender ( renderer );
        }
    }
}

void Game :: changeBoardObjectUp()
{
    for(int j = 0; j < nCell; j ++)
    for(int i = 0; i < nCell; i ++) 
    {
        if(mObject[i][j].getDistanceToMove() == 0) continue;
        int changeIndex = mObject[i][j].getDistanceToMove(); 
        mObject[i - changeIndex][j] = mObject[i][j];
        mObject[i][j].resetValue();
    }
}

int Game :: combineUp()
{
    int res = 0;
    for(int j = 0; j < nCell; j ++)
    {
        int i = 0;
        while(i <= nCell - 1)
        {
            if(mObject[i][j].getWidth() == 0) 
            {
                i ++;
                continue;
            }
            if(i == nCell - 1)
            {
                for(int k = 0; k < i; k ++)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i ++;
                continue;
            }
            if(mObject[i][j].getScore() == mObject[i + 1][j].getScore())
            {
                res += (1 << mObject[i][j].getScore()) * 2;
                int _score = mObject[i][j].getScore() + 1;
                mObject[i][j].setScore(i, j, _score, boxColor[_score]);
                mObject[i + 1][j].resetValue();
                for(int k = 0; k < i; k ++)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i += 2;
            }
            else 
            {
                for(int k = 0; k < i; k ++)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i ++;
            }
        }
    }
    return res;
}

void Game::moveUp(SDL_Renderer *renderer)
{   
    countDistanceToMoveUp();
    renderMoveUp( renderer );
    changeBoardObjectUp();

    coutMainObject();

    score += combineUp(); 
    windowRender( renderer );
}

void Game :: countDistanceToMoveDown()
{
    for(int j = 0; j < nCell; j ++)
    {   
        int countPreviousBox = 0;
        for(int i = nCell - 1; i >= 0; i --)
        {
            mObject[i][j].setDistanceToMove(0);
            if(mObject[i][j].getWidth() == 0) continue; 
            // std :: cout << i << ' ' << j << ' ' << countPreviousBox << ' ' << mObject[i][j].getDistanceToMove() << '\n';
            mObject[i][j].setDistanceToMove(nCell - 1 - i - countPreviousBox);
            countPreviousBox ++;

        } 
    }
}

void Game :: renderMoveDown(SDL_Renderer *renderer)
{
    bool isLastMove = false;
    for(int count = 0; count < renderCount; count ++)
    { 
        if(count == renderCount - 1) isLastMove = true;
        for(int i = 0; i < nCell; i ++)
        for(int j = 0; j < nCell; j ++)
        {
            mObject[i][j].moveDownMain( isLastMove ); 
            windowRender ( renderer );
        }
    }
}

void Game :: changeBoardObjectDown()
{
    for(int j = 0; j < nCell; j ++)
    for(int i = nCell - 1; i >= 0; i --)
    {
        if(mObject[i][j].getDistanceToMove() == 0) continue;
        int changeIndex = mObject[i][j].getDistanceToMove(); 
        mObject[i + changeIndex][j] = mObject[i][j];
        mObject[i][j].resetValue();
    }
}

int Game :: combineDown()
{
    int res = 0;
    for(int j = 0; j < nCell; j ++)
    {
        int i = nCell - 1;
        while(i >= 0)
        {
            if(mObject[i][j].getWidth() == 0) 
            {
                i --;
                continue;
            }
            if(i == 0)
            {
                for(int k = nCell - 1; k > i; k --)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i --;
                continue;
            }
            if(mObject[i][j].getScore() == mObject[i - 1][j].getScore())
            {
                res += (1 << mObject[i][j].getScore()) * 2;
                int _score = mObject[i][j].getScore() + 1;
                mObject[i][j].setScore(i, j, _score, boxColor[_score]);
                mObject[i - 1][j].resetValue();
                for(int k = nCell - 1; k > i; k --)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i -= 2;
            }
            else 
            {
                for(int k = nCell - 1; k > i; k --)
                    if(mObject[k][j].getWidth() == 0)
                    {
                        int _score = mObject[i][j].getScore();
                        mObject[k][j].setScore(k, j, _score, boxColor[_score]);
                        mObject[i][j].resetValue();
                        break;
                    }
                i --;
            }
        }
    }
    return res;
}

void Game::moveDown(SDL_Renderer *renderer)
{
    countDistanceToMoveDown();
    renderMoveDown( renderer );
    changeBoardObjectDown();

    coutMainObject();

    score += combineDown();
    windowRender( renderer );
}

bool Game::gameOver()
{
    for(int i = 0; i < nCell - 1; i ++)
    for(int j = 0; j < nCell - 1; j ++)
    {
        int score1 = mObject[i][j].getScore();
        int score2 = mObject[i][j + 1].getScore();
        int score3 = mObject[i + 1][j].getScore();
        if(score1 == score2 || score1 == score3 || score1 == 0 || score2 == 0 || score3 == 0)
            return false;
    }
    return true;
}

void Game::printGameOver(SDL_Renderer *renderer)
{
    textObject over(190, 150, "Game Over!", {255, 255, 255}, Font);
    over.renderText( renderer );
    SDL_RenderPresent( renderer );
}
