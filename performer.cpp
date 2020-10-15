#include "performer.h"

Performer::Performer(Basket *basketX, Basket *basketY) : m_basketChance(1.0 / 3.0)
{
    std::mt19937 rand(::time(0)); // initializing random generator
    calculateChanceX(basketX);
    calculateChanceY(basketY);
    calculateTwoBlueChance(basketX, basketY);
    calculateTwoRedChance(basketX, basketY);
    calculateBlueRedChance();
}

void Performer::calculateChanceX(Basket *basket)
{
    int blueBallsX = basket->getBlueBalls();
    int totalBallsX = basket->getTotalBalls();
    m_blueChanceX = totalBallsX > 0 ? double(blueBallsX) / double(totalBallsX) : 0;
    m_redChanceX = 1 - m_blueChanceX;
}

void Performer::calculateChanceY(Basket *basket)
{
    int blueBallsY = basket->getBlueBalls();
    int totalBallsY = basket->getTotalBalls();
    m_blueChanceY = totalBallsY > 0 ? double(blueBallsY) / double(totalBallsY) : 0;
    m_redChanceY = 1 - m_blueChanceY;
}

void Performer::calculateTwoBlueChance(Basket *basketX, Basket *basketY)
{
    int blueBallsX = basketX->getBlueBalls();
    int totalBallsX = basketX->getTotalBalls();
    int blueBallsY = basketY->getBlueBalls();
    int totalBallsY = basketY->getTotalBalls();

    m_twoBlueChance = (m_basketChance
            * m_blueChanceX * double(blueBallsX - 1) / double(totalBallsX - 1))
            + (m_basketChance * m_blueChanceY * double(blueBallsY - 1) / double(totalBallsY - 1))
            + (m_basketChance * m_blueChanceX * m_blueChanceY);
}

void Performer::calculateTwoRedChance(Basket *basketX, Basket *basketY)
{
    int redBallsX = basketX->getRedBalls();
    int totalBallsX = basketX->getTotalBalls();
    int redBallsY = basketY->getRedBalls();
    int totalBallsY = basketY->getTotalBalls();

    m_twoRedChance = (m_basketChance
            * m_redChanceX * double(redBallsX - 1) / double(totalBallsX - 1))
            + (m_basketChance * m_redChanceY * double(redBallsY - 1) / double(totalBallsY - 1))
            + (m_basketChance * m_redChanceX * m_redChanceY);
}

void Performer::calculateBlueRedChance()
{
    m_blueRedChance = 1 - (m_twoBlueChance + m_twoRedChance);
}

void Performer::shiftBall(Basket *basketFrom, Basket *basketTo)
{
    double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);

    int blueBalls = basketFrom->getBlueBalls();
    int redBalls = basketFrom->getRedBalls();
    int totalBalls = basketFrom->getTotalBalls();
    double blueChance = totalBalls > 0 ? double(blueBalls) / double(totalBalls) : 0;

    if (rndNumber <= blueChance && blueChance != 0) {
        basketFrom->takeBlueBalls(1);
        basketTo->addBlueBalls(1);
    }
    else if (redBalls) {
        basketFrom->takeRedBalls(1);
        basketTo->addRedBalls(1);
    }

    calculateTwoBlueChance(basketFrom, basketTo);
    calculateTwoRedChance(basketFrom, basketTo);
    calculateBlueRedChance();
}

int Performer::extractBall(Basket *basketX, Basket *basketY, int ballsToExtract)
{
    if (ballsToExtract > 0) {
        double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);
        int rndBasket = rand() % 2;
        if (rndBasket == 0) {
            calculateChanceX(basketX);
            if (rndNumber <= m_blueChanceX && m_blueChanceX != 0) {
                basketX->takeBlueBalls(1);
                extractBall(basketX, basketY, ballsToExtract - 1);
            }
            else if (basketX->getRedBalls()) {
                basketX->takeRedBalls(1);
                extractBall(basketX, basketY, ballsToExtract - 1);
            }
        }
        else {
            calculateChanceY(basketY);
            if (rndNumber <= m_blueChanceY && m_blueChanceY != 0) {
                basketY->takeBlueBalls(1);
                extractBall(basketX, basketY, ballsToExtract - 1);
            }
            else if (basketY->getRedBalls()) {
                basketY->takeRedBalls(1);
                extractBall(basketX, basketY, ballsToExtract - 1);
            }
        }

        calculateTwoBlueChance(basketX, basketY);
        calculateTwoRedChance(basketX, basketY);
        calculateBlueRedChance();
    }
    return 0;
}

double Performer::getBlueChanceX() { return m_blueChanceX; }
double Performer::getRedChanceX() { return m_redChanceX; }
double Performer::getBlueChanceY() { return m_blueChanceY; }
double Performer::getRedChanceY() { return m_redChanceY; }
double Performer::getTwoBlueChance() { return m_twoBlueChance; }
double Performer::getTwoRedChance() { return m_twoRedChance; }
double Performer::getBlueRedChance() { return m_blueRedChance; }
