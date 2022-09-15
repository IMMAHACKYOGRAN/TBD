#include "board.h"

Board::Board(iVec2 size, fVec2 pos)
{
    m_size = size;
    m_pos = pos;
    std::vector<std::vector<int>> m_vBoardState(m_size.x, std::vector<int>(m_size.y, 0));
}

void Board::setPos(fVec2 pos) { m_pos = pos; }
fVec2 Board::getPos() { return m_pos; }

void Board::update()
{
    
}