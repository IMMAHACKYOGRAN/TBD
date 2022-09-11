#pragma once
#include <vector>
#include <iostream>
#include "util.h"

class Player
{
private:
    iVec2 m_worldPos;;
    std::vector<iVec2> legalMoves;
    bool isMoveValid(iVec2 pos, iVec2 boardSize);
public:
    Player(iVec2 wp);
    void update();
    void findLegalMoves(iVec2 boardSize);

/* Getters and setters  */
    iVec2 getWorldPos();
    void setWorldPos(iVec2 pos);
};