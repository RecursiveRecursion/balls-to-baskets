#ifndef RAND_PRECISION
#define RAND_PRECISION 1000
#endif
#ifndef PERFORMER_H
#define PERFORMER_H

#include "basket.h"

#include <time.h>
#include <random>

class Performer :  public QObject
{
    Q_OBJECT

public:
    Performer();

    Q_INVOKABLE void shiftBall(Basket *basketFrom, Basket *basketTo);
    void extractBalls(Basket *basketX, Basket *basketY);

private:
    double m_blueChance;
    double m_redChance;
    double m_twoBlueChance;
    double m_twoRedChance;
    double m_blueRedChance;
};

#endif // PERFORMER_H
