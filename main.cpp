#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "frameprocessor.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FrameProcessor>("com.frameprocessor", 1, 0, "FrameProcessor");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/BarcodeReader/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
