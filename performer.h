#ifndef PERFORMER_H
#define PERFORMER_H

#ifndef RAND_PRECISION
#define RAND_PRECISION 1000
#endif

#include "basket.h"

#include <time.h>
#include <random>
#include <QString>

class Performer :  public QObject
{
    Q_OBJECT
    Q_PROPERTY(double twoBlueChance MEMBER m_twoBlueChance NOTIFY twoBlueChanceChanged)
    Q_PROPERTY(double twoRedChance MEMBER m_twoRedChance NOTIFY twoRedChanceChanged)
    Q_PROPERTY(double blueRedChance MEMBER m_blueRedChance NOTIFY blueRedChanceChanged)

public:
    Performer(Basket *basketX, Basket *basketY);

    Q_INVOKABLE QString shiftBall(Basket *basketFrom, Basket *basketTo);
    Q_INVOKABLE QString extractBall(Basket *basketX, Basket *basketY, int ballsToExtract);

    double calculateChance(int balls, int totalBalls);
    void calculateTwoBlueChance(Basket *basketX, Basket *basketY);
    void calculateTwoRedChance(Basket *basketX, Basket *basketY);
    void calculateBlueRedChance();

    Q_INVOKABLE double getTwoBlueChance();
    Q_INVOKABLE double getTwoRedChance();
    Q_INVOKABLE double getBlueRedChance();

signals:
    void twoBlueChanceChanged();
    void twoRedChanceChanged();
    void blueRedChanceChanged();

private:
    const double m_actionChance; // 3 options: 1 blue and 1 red || 2 blue || 2 red -> (1.0 / 3.0)
    double m_twoBlueChance;
    double m_twoRedChance;
    double m_blueRedChance;
    QString m_lastAction;
};

#endif // PERFORMER_H
