#include "basket.h"

Basket::Basket(int blueBalls, int redBalls)
    : m_blueBalls(blueBalls),
      m_redBalls(redBalls),
      m_totalBalls(blueBalls + redBalls)
{

}

void Basket::addBlueBalls(int amount)
{
    m_blueBalls += amount;
    m_totalBalls += amount;
}

void Basket::addRedBalls(int amount)
{
    m_redBalls += amount;
    m_totalBalls += amount;
}

void Basket::takeBlueBalls(int amount)
{
    m_blueBalls -= amount;
    m_totalBalls -= amount;
}

void Basket::takeRedBalls(int amount)
{
    m_redBalls -= amount;
    m_totalBalls -= amount;
}

int Basket::getBlueBalls() { return m_blueBalls; }
void Basket::setBlueBalls(int value) { m_blueBalls = value; m_totalBalls = value + m_redBalls; }

int Basket::getRedBalls() { return m_redBalls; }
void Basket::setRedBalls(int value) { m_redBalls = value; m_totalBalls = value + m_blueBalls; }

int Basket::getTotalBalls() { return m_totalBalls; }
