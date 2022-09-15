#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#include "util.h"
#include "renderwindow.h"
#include "board.h"
#include "player.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

int renderSize = 128;

RenderWindow window;

SDL_Texture* tiles;
SDL_Texture* dropShadow;
SDL_Texture* overlays;

Board board({5, 5}, {SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.75});
Player player({4, 4});

bool running = true;
bool gameRunning = true;

iVec2 mouse;
iVec2 screenCell;
iVec2 selectedCell;

iVec2 topLeft[3] = {{0,0},{renderSize/2,0},{0,renderSize/4}};
iVec2 topRight[3] = {{renderSize/2,0},{renderSize,0},{renderSize,renderSize/4}};
iVec2 bottomLeft[3] = {{0,renderSize/4},{0,renderSize/2},{renderSize/2,renderSize/2}};
iVec2 bottomRight[3] = {{renderSize/2,renderSize/2},{renderSize,renderSize/2},{renderSize,renderSize/4}};

// I think it should be just one Vec2 that contains autos but I cbf
fVec2 fIsoToScreen(fVec2 pos, float rts)
{
    fVec2 tmp = pos;

    tmp.x = (pos.x - pos.y) * rts / 2;
    tmp.y = (pos.x + pos.y) * rts / 4;
    
    return tmp; 
}
iVec2 iIsoToScreen(iVec2 pos, float rts)
{
    iVec2 tmp = pos;

    tmp.x = (pos.x - pos.y) * rts / 2;
    tmp.y = (pos.x + pos.y) * rts / 4;
    
    return tmp;
}

bool init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	window.create("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	srand((unsigned)time(0));

    tiles = window.loadTexture("res/tiles.png");
    dropShadow = window.loadTexture("res/dropshadow.png");
    overlays = window.loadTexture("res/overlays.png");

	return true;
}

bool load = init();

void draw()
{
        window.clear();

        // Gameplay loop
        if(gameRunning) {
            float offset = sinf(SDL_GetTicks() * 0.005);
            window.render(dropShadow, board.getPos().x-renderSize*2.5, board.getPos().y-renderSize*2-8+offset, renderSize*5, renderSize*5);
            // Draw Board
            for (float y = 0; y < board.m_size.y; y++) {
                for (float x = 0; x < board.m_size.x; x++) {
                    fVec2 isoPos = fIsoToScreen({x, y}, renderSize);
                    window.render(tiles, 32, 0, 32, 32, ((board.getPos().x-renderSize/2)+isoPos.x), (board.getPos().y-renderSize*1.25)+isoPos.y+offset, renderSize, renderSize);
                }
            }

            // Draw Moves
            for (int i = 0; i < player.m_legalMoves.size(); i++)
            {
                iVec2 isoMovePos = iIsoToScreen({player.getWorldPos().x + player.m_legalMoves[i].x, player.getWorldPos().y + player.m_legalMoves[i].y}, renderSize);
                window.render(overlays, 0, 0, 32, 32, isoMovePos.x + board.getPos().x - renderSize / 2, isoMovePos.y + board.getPos().y - renderSize * 1.25 + offset, renderSize, renderSize);
            }

            iVec2 isoPlayerPos = iIsoToScreen(player.getWorldPos(), renderSize);
            window.renderPoint(isoPlayerPos.x+board.getPos().x, isoPlayerPos.y+board.getPos().y-renderSize+offset, 0, 255, 0, 255);
            
            if(selectedCell.x >= 0 && selectedCell.x <= board.m_size.x-1 && selectedCell.y >= 0 && selectedCell.y <= board.m_size.y-1) {
                fVec2 boxPos = {(float)(selectedCell.y-selectedCell.x)/2+2, (float)(selectedCell.x+selectedCell.y)/2};
                window.render(overlays, 0, 0, 32, 32, boxPos.x*renderSize+board.getPos().x-renderSize*2.5, boxPos.y*(renderSize/2)+board.getPos().y-renderSize*1.25+offset, renderSize, renderSize);
            }
        }

        window.display();
}

float area(iVec2 p1, iVec2 p2, iVec2 p3)
{
   return abs((p1.x*(p2.y-p3.y)+p2.x*(p3.y-p1.y)+p3.x*(p1.y-p2.y))/2.0);
}
bool insideTri(iVec2 tri[], iVec2 mousePos)
{
    float a = area(tri[0], tri[1], tri[2]);
    float a1 = area (mousePos, tri[1], tri[2]);
    float a2 = area (tri[0], mousePos, tri[2]);
    float a3 = area (tri[0], tri[1], mousePos);

    return (a==a1+a2+a3);
}

void getInput()
{
    SDL_GetMouseState(&mouse.x, &mouse.y);
    screenCell = {(mouse.x-345)/renderSize, (mouse.y-180)/(renderSize/2)};
    if(mouse.x-345<0 || mouse.y-180<0) screenCell = {-1,-1};
    selectedCell = {screenCell.y-screenCell.x+2, screenCell.y+screenCell.x-2};
    iVec2 offset = {(mouse.x-345)%renderSize, (mouse.y-180)%(renderSize/2)};

    if (insideTri(topLeft, offset)) selectedCell.y -= 1;
    if (insideTri(topRight, offset)) selectedCell.x -= 1;
    if (insideTri(bottomLeft, offset)) selectedCell.x += 1;
    if (insideTri(bottomRight, offset)) selectedCell.y += 1;
}

void gameLoop()
{
	SDL_Event e;
 	while (SDL_PollEvent(&e)) 
 	{
    	switch (e.type) {
            case SDL_QUIT: 
            {
                running = false;
                break;
            }
        }
    }

    getInput();
    draw();
}

int main(int argc, char* args[])
{
    player.findLegalMoves(board.m_size);
    while (running) 
	{
    	gameLoop();
    	SDL_Delay(16);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}