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

    void calculateChance(Basket *basket, double *blueChance, double *redChance); // last 2 args are output
    void calculateTwoBlueChance(Basket *basketX, Basket *basketY);
    void calculateTwoRedChance(Basket *basketX, Basket *basketY);
    void calculateBlueRedChance();

    Q_INVOKABLE double getBlueChanceX();
    Q_INVOKABLE double getRedChanceX();
    Q_INVOKABLE double getBlueChanceY();
    Q_INVOKABLE double getRedChanceY();
    Q_INVOKABLE double getTwoBlueChance();
    Q_INVOKABLE double getTwoRedChance();
    Q_INVOKABLE double getBlueRedChance();

signals:
    void twoBlueChanceChanged();
    void twoRedChanceChanged();
    void blueRedChanceChanged();

private:
    double m_blueChanceX;
    double m_redChanceX;
    double m_blueChanceY;
    double m_redChanceY;
    double m_basketChance; // 3 options: 1 blue and 1 red || 2 blue || 2 red -> (1.0 / 3.0)
    double m_twoBlueChance;
    double m_twoRedChance;
    double m_blueRedChance;
    QString m_lastAction;
};

#endif // PERFORMER_H
