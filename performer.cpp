#include "performer.h"

Performer::Performer(Basket *basketX, Basket *basketY)
    : m_basketChance(1.0 / 3.0), m_lastAction("")
{
    calculateChance(basketX, &m_blueChanceX, &m_redChanceX);
    calculateChance(basketY, &m_blueChanceY, &m_redChanceY);
    calculateTwoBlueChance(basketX, basketY);
    calculateTwoRedChance(basketX, basketY);
    calculateBlueRedChance();
}

void Performer::calculateChance(Basket *basket, double *blueChance, double *redChance)
{
    int blueBalls = basket->getBlueBalls();
    int totalBalls = basket->getTotalBalls();
    *blueChance = totalBalls > 0 ? double(blueBalls) / double(totalBalls) : 0;
    *redChance = totalBalls > 0 ? (1 - *blueChance) : 0;
}

void Performer::calculateTwoBlueChance(Basket *basketX, Basket *basketY)
{
    int blueBallsX = basketX->getBlueBalls();
    int blueBallsY = basketY->getBlueBalls();
    int totalBallsX = basketX->getTotalBalls();
    int totalBallsY = basketY->getTotalBalls();
    double blueChanceX = totalBallsX > 0 ? double(blueBallsX) / double(totalBallsX) : 0;
    double blueChanceY = totalBallsY > 0 ? double(blueBallsY) / double(totalBallsY) : 0;
    double newBlueChanceX = (totalBallsX - 1) > 0 ? double(blueBallsX - 1) / double(totalBallsX - 1) : 0;
    double newBlueChanceY = (totalBallsY - 1) > 0 ? double(blueBallsY - 1) / double(totalBallsY - 1) : 0;

    m_twoBlueChance = !totalBallsX ? 0 :
                                     (m_basketChance * blueChanceX * newBlueChanceX)
                                     + (m_basketChance * blueChanceY * newBlueChanceY)
                                     + (m_basketChance * blueChanceX * blueChanceY);
}

void Performer::calculateTwoRedChance(Basket *basketX, Basket *basketY)
{
    int redBallsX = basketX->getRedBalls();
    int redBallsY = basketY->getRedBalls();
    int totalBallsX = basketX->getTotalBalls();
    int totalBallsY = basketY->getTotalBalls();
    double redChanceX = totalBallsX > 0 ? double(redBallsX) / double(totalBallsX) : 0;
    double redChanceY = totalBallsY > 0 ? double(redBallsY) / double(totalBallsY) : 0;
    double newRedChanceX = (totalBallsX - 1) > 0 ? double(redBallsX - 1) / double(totalBallsX - 1) : 0;
    double newRedChanceY = (totalBallsY - 1) > 0 ? double(redBallsY - 1) / double(totalBallsY - 1) : 0;

    m_twoRedChance = !totalBallsX ? 0 :
                                    (m_basketChance * redChanceX * newRedChanceX)
                                    + (m_basketChance * redChanceY * newRedChanceY)
                                    + (m_basketChance * redChanceX * redChanceY);
}

void Performer::calculateBlueRedChance()
{
    m_blueRedChance = (!m_twoBlueChance && !m_twoRedChance) ? 0 :
                                                              1 - (m_twoBlueChance + m_twoRedChance);
}

QString Performer::shiftBall(Basket *basketFrom, Basket *basketTo)
{
    std::mt19937 rand(::time(0)); // initializing random generator
    double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);
    double blueChance;
    double redChance;
    QString action = "ничего не извлекли";

    calculateChance(basketFrom, &blueChance, &redChance);

    if (rndNumber <= blueChance && blueChance != 0) {
        basketFrom->takeBlueBalls(1);
        basketTo->addBlueBalls(1);
        action = "извлекли синий шар";
    }
    else if (redChance) {
        basketFrom->takeRedBalls(1);
        basketTo->addRedBalls(1);
        action = "извлекли красный шар";
    }

    calculateTwoBlueChance(basketFrom, basketTo);
    calculateTwoRedChance(basketFrom, basketTo);
    calculateBlueRedChance();
    return action;
}

QString Performer::extractBall(Basket *basketX, Basket *basketY, int ballsToExtract)
{
    std::mt19937 rand(::time(0)); // initializing random generator
    int extractedBlueBalls = 0;
    int extractedRedBalls = 0;
    int totalBalls = basketX->getTotalBalls() + basketY->getTotalBalls();
    QString action = "ничего не извлекли";

    if (totalBalls < ballsToExtract) {
        ballsToExtract = totalBalls;
    }

    while (ballsToExtract) {
        double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);
        int rndBasket = rand() % 2;
        if (rndBasket == 0) {
            calculateChance(basketX, &m_blueChanceX, &m_redChanceX);
            if (rndNumber <= m_blueChanceX && m_blueChanceX != 0) {
                basketX->takeBlueBalls(1);
                extractedBlueBalls++;
                ballsToExtract--;
            }
            else if (m_redChanceX) {
                basketX->takeRedBalls(1);
                extractedRedBalls++;
                ballsToExtract--;
            }
        }
        else {
            calculateChance(basketY, &m_blueChanceY, &m_redChanceY);
            if (rndNumber <= m_blueChanceY && m_blueChanceY != 0) {
                basketY->takeBlueBalls(1);
                extractedBlueBalls++;
                ballsToExtract--;
            }
            else if (m_redChanceY) {
                basketY->takeRedBalls(1);
                extractedRedBalls++;
                ballsToExtract--;
            }
        }

        calculateTwoBlueChance(basketX, basketY);
        calculateTwoRedChance(basketX, basketY);
        calculateBlueRedChance();
    }

    if (extractedBlueBalls) {
        if (extractedBlueBalls == 2) {
            action = "извлекли два синих шара";
        }
        else if (extractedBlueBalls == 1) {
            action = "извлекли один синий шар";
            if (extractedRedBalls) {
                action = "извлекли синий и красный шары";
            }
        }
    }
    else if (extractedRedBalls) {
        if (extractedRedBalls == 2) {
            action = "извлекли два красных шара";
        }
        else {
            action = "извлекли один красный шар";
        }
    }

    return action;
}

double Performer::getBlueChanceX() { return m_blueChanceX; }
double Performer::getRedChanceX() { return m_redChanceX; }
double Performer::getBlueChanceY() { return m_blueChanceY; }
double Performer::getRedChanceY() { return m_redChanceY; }
double Performer::getTwoBlueChance() { return m_twoBlueChance; }
double Performer::getTwoRedChance() { return m_twoRedChance; }
double Performer::getBlueRedChance() { return m_blueRedChance; }
