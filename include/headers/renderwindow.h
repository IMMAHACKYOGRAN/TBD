#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class RenderWindow 
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	RenderWindow();
	void create(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* filePath);
	void clear();
	void render(SDL_Texture* tex, int sx, int sy, int sw, int sh, float dx, float dy, float dw, float dh);
    void render(SDL_Texture* tex, float dx, float dy, float dw, float dh);
    void renderPoint(int x, int y, int r, int g, int b, int a);
	void display();
	void cleanUp();
};