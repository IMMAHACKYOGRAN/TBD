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
Player player({1, 0});

bool running = true;
bool gameRunning = true;

iVec2 mouse;
iVec2 isoMouse;

fVec2 fIsoToScreen(fVec2 pos, float rts) {
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

        }

        window.display();
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

    SDL_GetMouseState(&mouse.x, &mouse.y);
    isoMouse = iIsoToScreen(mouse, 1 / renderSize);
    std::cout << "x: " << isoMouse.x << " y: " << isoMouse.y << std::endl;

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