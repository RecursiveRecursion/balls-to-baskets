#include "performer.h"

Performer::Performer(Basket *basketX, Basket *basketY) : m_actionChance(1.0 / 3.0)
{
    calculateTwoBlueChance(basketX, basketY);
    calculateTwoRedChance(basketX, basketY);
    calculateBlueRedChance();
}

double Performer::calculateChance(int balls, int totalBalls)
{
    return totalBalls > 0 ? double(balls) / double(totalBalls) : 0;
}

void Performer::calculateTwoBlueChance(Basket *basketX, Basket *basketY)
{
    int blueBallsX = basketX->getBlueBalls();
    int blueBallsY = basketY->getBlueBalls();
    int totalBallsX = basketX->getTotalBalls();
    int totalBallsY = basketY->getTotalBalls();
    double blueChanceX = calculateChance(blueBallsX, totalBallsX);
    double blueChanceY = calculateChance(blueBallsY, totalBallsY);
    double newBlueChanceX = calculateChance(blueBallsX - 1, totalBallsX - 1);
    double newBlueChanceY = calculateChance(blueBallsY - 1, totalBallsY - 1);

    m_twoBlueChance = !totalBallsX ? 0 :
                                     (m_actionChance * blueChanceX * newBlueChanceX)
                                     + (m_actionChance * blueChanceY * newBlueChanceY)
                                     + (m_actionChance * blueChanceX * blueChanceY);
}

void Performer::calculateTwoRedChance(Basket *basketX, Basket *basketY)
{
    int redBallsX = basketX->getRedBalls();
    int redBallsY = basketY->getRedBalls();
    int totalBallsX = basketX->getTotalBalls();
    int totalBallsY = basketY->getTotalBalls();
    double redChanceX = calculateChance(redBallsX, totalBallsX);
    double redChanceY = calculateChance(redBallsY, totalBallsY);
    double newRedChanceX = calculateChance(redBallsX - 1, totalBallsX - 1);
    double newRedChanceY = calculateChance(redBallsY - 1, totalBallsY - 1);

    m_twoRedChance = !totalBallsX ? 0 :
                                    (m_actionChance * redChanceX * newRedChanceX)
                                    + (m_actionChance * redChanceY * newRedChanceY)
                                    + (m_actionChance * redChanceX * redChanceY);
}

void Performer::calculateBlueRedChance()
{
    m_blueRedChance = (!m_twoBlueChance && !m_twoRedChance) ? 0 :
                                                              1 - (m_twoBlueChance + m_twoRedChance);
}

QString Performer::shiftBall(Basket *basketFrom, Basket *basketTo)
{
    std::mt19937 rand(::time(0));
    double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);
    double blueChance = calculateChance(basketFrom->getBlueBalls(), basketFrom->getTotalBalls());
    double redChance = calculateChance(basketFrom->getRedBalls(), basketFrom->getTotalBalls());
    QString action = "ничего не извлекли";

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
    std::mt19937 rand(::time(0));
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
        int blueBallsX = basketX->getBlueBalls();
        int blueBallsY = basketY->getBlueBalls();
        int redBallsX = basketX->getRedBalls();
        int redBallsY = basketY->getRedBalls();
        int totalBallsX = basketX->getTotalBalls();
        int totalBallsY = basketY->getTotalBalls();
        double blueChanceX = calculateChance(blueBallsX, totalBallsX);
        double blueChanceY = calculateChance(blueBallsY, totalBallsY);
        double redChanceX = calculateChance(redBallsX, totalBallsX);
        double redChanceY = calculateChance(redBallsY, totalBallsY);

        if (rndBasket == 0) {
            if (rndNumber <= blueChanceX && blueChanceX != 0) {
                basketX->takeBlueBalls(1);
                extractedBlueBalls++;
                ballsToExtract--;
            }
            else if (redChanceX) {
                basketX->takeRedBalls(1);
                extractedRedBalls++;
                ballsToExtract--;
            }
        }
        else {
            if (rndNumber <= blueChanceY && blueChanceY != 0) {
                basketY->takeBlueBalls(1);
                extractedBlueBalls++;
                ballsToExtract--;
            }
            else if (redChanceY) {
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

double Performer::getTwoBlueChance() { return m_twoBlueChance; }
double Performer::getTwoRedChance() { return m_twoRedChance; }
double Performer::getBlueRedChance() { return m_blueRedChance; }
