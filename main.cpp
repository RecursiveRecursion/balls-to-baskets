#include "performer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    std::mt19937 rand(::time(0));
    Basket *basket1 = new Basket(rand() % 51, rand() % 51); // or set manually
    Basket *basket2 = new Basket(rand() % 51, rand() % 51);
    Performer *performer = new Performer(basket1, basket2);

    engine.rootContext()->setContextProperty("basket1", basket1);
    engine.rootContext()->setContextProperty("basket2", basket2);
    engine.rootContext()->setContextProperty("performer", performer);

    engine.load(url);

    int rc = app.exec();

    delete performer;
    delete basket1;
    delete basket2;
    return rc;
}
