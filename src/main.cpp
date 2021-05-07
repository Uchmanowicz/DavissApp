#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QIcon>

#include <QQmlContext>

#include <controllers/databasecontroller.h>
#include <controllers/depocontroller.h>
#include <controllers/settingscontroller.h>

#include <QDebug>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("qrc:/resources/logo/icon.ico"));


    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    DatabaseController dbController;
    SettingsController settingsController(dbController);

    engine.rootContext()->setContextProperty("dbController", &dbController);
    engine.rootContext()->setContextProperty("depoController", &dbController.depoController);
    engine.rootContext()->setContextProperty("treeViewModel", &dbController.depoController.treeViewModel);
    engine.rootContext()->setContextProperty("settingsController", &settingsController);

    bool OS_ANDROID, OS_WINDOWS = false;

#if defined(Q_OS_ANDROID)
    OS_ANDROID = true;
    OS_WINDOWS = false;
#elif defined(Q_OS_WINDOWS)
    OS_ANDROID = false;
    OS_WINDOWS = true;
#else
    OS_ANDROID = false;
    OS_WINDOWS = false;
#endif

    engine.rootContext()->setContextProperty("OS_ANDROID", QVariant(OS_ANDROID));
    engine.rootContext()->setContextProperty("OS_WINDOWS", QVariant(OS_WINDOWS));

    engine.load(url);

    return app.exec();
}
