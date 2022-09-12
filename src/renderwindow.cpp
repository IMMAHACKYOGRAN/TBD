#include "renderwindow.h"

RenderWindow::RenderWindow() {}

void RenderWindow::create(const char* title, int w, int h)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL) std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL; 
	texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL) std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 36, 36, 36, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* tex, int sx, int sy, int sw, int sh, float dx, float dy, float dw, float dh)
{
    SDL_Rect src;
    src.x = sx;
    src.y = sy;
    src.w = sw;
    src.h = sh;

    SDL_Rect dst;
    dst.x = dx;
    dst.y = dy;
    dst.w = dw;
    dst.h = dh;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}

void RenderWindow::render(SDL_Texture* tex, float dx, float dy, float dw, float dh)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = dx;
    dst.y = dy;
    dst.w = dw;
    dst.h = dh;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}

void RenderWindow::renderPoint(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}