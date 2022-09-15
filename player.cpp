#include "player.h"

Player::Player(iVec2 wp) 
{
    m_worldPos = wp;
}

iVec2 Player::getWorldPos() { return m_worldPos; }

void Player::setWorldPos(iVec2 pos) { m_worldPos = pos; }

bool Player::isMoveValid(iVec2 pos, iVec2 boardSize)
{
    if(pos.x >= 0 && pos.x <= boardSize.x-1 && pos.y >= 0 && pos.y <= boardSize.y-1) return true;

    return false;
}

void Player::findLegalMoves(iVec2 boardSize)
{
    if(isMoveValid({m_worldPos.x + 1, m_worldPos.y}, boardSize)) m_legalMoves.push_back({1, 0});
    if(isMoveValid({m_worldPos.x - 1, m_worldPos.y}, boardSize)) m_legalMoves.push_back({-1, 0});
    if(isMoveValid({m_worldPos.x, m_worldPos.y + 1}, boardSize)) m_legalMoves.push_back({0, 1});
    if(isMoveValid({m_worldPos.x, m_worldPos.y - 1}, boardSize)) m_legalMoves.push_back({0, -1});

    for (int i = 0; i < m_legalMoves.size(); i++)
    {
        std::cout << "x: " << m_legalMoves[i].x << " y: " << m_legalMoves[i].y << std::endl;
    }
}

void Player::update()
{

}