#ifndef BASKET_H
#define BASKET_H

#include <QObject>

class Basket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int blueBalls MEMBER m_blueBalls NOTIFY blueBallsChanged)
    Q_PROPERTY(int redBalls MEMBER m_redBalls NOTIFY redBallsChanged)
    Q_PROPERTY(int totalBalls MEMBER m_totalBalls NOTIFY totalBallsChanged)

public:
    Basket(int blueBalls, int redBalls);

    void addBlueBalls(int amount);
    void addRedBalls(int amount);
    void takeBlueBalls(int amount);
    void takeRedBalls(int amount);

    int getBlueBalls();
    void setBlueBalls(int value);

    int getRedBalls();
    void setRedBalls(int value);

    int getTotalBalls();

signals:
    void blueBallsChanged();
    void redBallsChanged();
    void totalBallsChanged();

private:
    int m_blueBalls;
    int m_redBalls;
    int m_totalBalls;
};

#endif // BASKET_H
