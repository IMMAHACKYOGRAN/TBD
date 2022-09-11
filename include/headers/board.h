#include <SDL.h>
#include <SDL_image.h>
#include <util.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "util.h"

class Board
{
    public:
        Board(iVec2 size, fVec2 pos);
        iVec2 m_size;
        void setPos(fVec2 pos);
        fVec2 getPos();
        void update();
    private:
        fVec2 m_pos;
        void bob();
};