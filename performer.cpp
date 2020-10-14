#include "performer.h"

Performer::Performer()
{

}

void Performer::shiftBall(Basket *basketFrom, Basket *basketTo)
{
    std::mt19937 rand(::time(0));
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
}

void Performer::extractBalls(Basket *basketX, Basket *basketY)
{
    std::mt19937 rand(::time(0));
    double rndNumber = double(rand() % RAND_PRECISION + 1) / double(RAND_PRECISION);

    double basketChance = 1.0 / 3.0;   // 3 options: 1 blue and 1 red || 2 blue || 2 red

    int blueBallsX = basketX->getBlueBalls();
    int redBallsX = basketX->getRedBalls();
    int totalBallsX = basketX->getTotalBalls();
    double blueChanceX = totalBallsX > 0 ? double(blueBallsX) / double(totalBallsX) : 0;
    double redChanceX = 1 - blueChanceX;

    int blueBallsY = basketY->getBlueBalls();
    int redBallsY = basketY->getRedBalls();
    int totalBallsY = basketY->getTotalBalls();
    double blueChanceY = totalBallsY > 0 ? double(blueBallsY) / double(totalBallsY) : 0;
    double redChanceY = 1 - blueChanceY;

    double get2BlueChance = (basketChance
            * blueChanceX * double(blueBallsX - 1) / double(totalBallsX - 1))
            + (basketChance * blueChanceY * double(blueBallsY - 1) / double(totalBallsY - 1))
            + (basketChance * blueChanceX * blueChanceY);

    double get2RedChance = (basketChance
            * redChanceX * double(redBallsX - 1) / double(totalBallsX - 1))
            + (basketChance * redChanceY * double(redBallsY - 1) / double(totalBallsY - 1))
            + (basketChance * redChanceX * redChanceY);

    double get1Blue1RedChance = 1 - (get2BlueChance + get2RedChance);

}
