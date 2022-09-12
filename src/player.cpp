#include "player.h"

Player::Player(iVec2 wp) 
{
    m_worldPos = wp;
}

iVec2 Player::getWorldPos() { return m_worldPos; }

void Player::setWorldPos(iVec2 pos) { m_worldPos = pos; }

bool Player::isMoveValid(iVec2 pos, iVec2 boardSize)
{
    if(pos.x && pos.x >= 0 && pos.x <= boardSize.x) return true;
    if(pos.y && pos.y >= 0 && pos.y <= boardSize.y) return true;
    return false;
}

void Player::findLegalMoves(iVec2 boardSize)
{
    if(isMoveValid({m_worldPos.x + 1, NULL}, boardSize)) legalMoves.push_back({m_worldPos.x + 1, NULL});
    if(isMoveValid({m_worldPos.x - 1, NULL}, boardSize)) legalMoves.push_back({m_worldPos.x - 1, NULL});
    if(isMoveValid({NULL, m_worldPos.y + 1}, boardSize)) legalMoves.push_back({NULL, m_worldPos.y + 1});
    if(isMoveValid({NULL, m_worldPos.y - 1}, boardSize)) legalMoves.push_back({NULL, m_worldPos.y - 1});
    for(int i = 0; i < 4; i++) {
        std::cout << legalMoves[i].x << " " << legalMoves[i].y << " " << i << std::endl;
    }
}

void Player::update()
{

}