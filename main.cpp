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

    Basket *basket1 = new Basket(7, 3);  // set amount of balls for basket1 here
    Basket *basket2 = new Basket(9, 6);  // set amount of balls for basket2 here
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
